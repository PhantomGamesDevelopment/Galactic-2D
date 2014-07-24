/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* WinTime.cpp
*
* Defines the PlatformTime class for windows platforms
*
* References:
*  http://stackoverflow.com/questions/17432502/how-can-i-measure-cpu-time-and-wall-clock-time-on-both-linux-windows
**/

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		F32 PlatformTime::lastCPUCyclePerc_Relative = 0.0f;

		F64 PlatformTime::init() {
			LARGE_INTEGER tFreq;
			if (!QueryPerformanceFrequency(&tFreq)) {
				GC_Error("PlatformTime::init(): Failed to detect performance frequency on CPU.");
				return 0.0f;
			}
			timePerCycle = 1.0f / tFreq.QuadPart;
			//Queue up the core ticker, and add a timer instance for the platform
			FrameTicker::fetchMainTicker().addTickerInstance(GalacticFrameTickerDelegate::createGlobalMethodDelegate(&PlatformTime::updateCPUTimeInfo), (1.0f / 4.0f));
			//Return current time
			return fetchSeconds();
		}
		
		F64 PlatformTime::fetchSeconds() {
			LARGE_INTEGER tFreq;
			QueryPerformanceFrequency(&tFreq);
			//Note! This is prone to potential bugs when converting U64->F64, this may need to be looked into at some point...
			return (F64)(tFreq.QuadPart) * fetchTPC();
		}

		U64 PlatformTime::fetchCycles() {
			LARGE_INTEGER tFreq;
			QueryPerformanceFrequency(&tFreq);
			return tFreq.QuadPart;
		}

		void PlatformTime::sysTime(TimeVars &c) {
			SYSTEMTIME sysTime;
			GetLocalTime(&sysTime);

			c.years = (S32)sysTime.wYear;
			c.months = (S32)sysTime.wMonth;
			c.dayOfWeek = (S32)sysTime.wDayOfWeek;
			c.dayNum = (S32)sysTime.wDay;
			c.hours = (S32)sysTime.wHour;
			c.minutes = (S32)sysTime.wMinute;
			c.seconds = (S32)sysTime.wSecond;
			c.miliseconds = (S32)sysTime.wMilliseconds;
		}

		void PlatformTime::utcTime(TimeVars &c) {
			SYSTEMTIME sysTime;
			GetSystemTime(&sysTime);

			c.years = (S32)sysTime.wYear;
			c.months = (S32)sysTime.wMonth;
			c.dayOfWeek = (S32)sysTime.wDayOfWeek;
			c.dayNum = (S32)sysTime.wDay;
			c.hours = (S32)sysTime.wHour;
			c.minutes = (S32)sysTime.wMinute;
			c.seconds = (S32)sysTime.wSecond;
			c.miliseconds = (S32)sysTime.wMilliseconds;
		}

		CPUTimeInfo PlatformTime::getTimeInfo() {
			/*
			This calculation is briefly discussed in the SO article mentioned in genericPlatformTime.h. Essentially, you take a calculated value of a 
			 relative core's processing time and divide it by the number of "logical" or working cores for the process.
			*/
			return CPUTimeInfo((lastCPUCyclePerc_Relative / (F32)PlatformOperations::numLogicalCores()), lastCPUCyclePerc_Relative);
		}

		bool PlatformTime::updateCPUTimeInfo(F32 dT) {
			//This method is called by the CoreTicker each time around. Our job is to determine the relative cycles that were ran last time around in order
			// for the getTimeInfo() method to properly calculate the current time.
			static F64 lastProcessTime = 0.0f, lastTotalTime = 0.0f;
			//These next variables are discussed in the MSDN Documentation here (http://msdn.microsoft.com/en-us/library/windows/desktop/ms724284.aspx)
			FILETIME StartTime = { 0 }, CurrentTime = { 0 }, UserTime = { 0 }, CoreTime = { 0 }, ExitTime = { 0 };
			::GetProcessTimes(::GetCurrentProcess(), &StartTime, &ExitTime, &CoreTime, &UserTime);
			::GetSystemTimeAsFileTime(&CurrentTime);
			//Now we use some mathemagic to obtain a value relating the change in coreTime and userTime
			const F64 combUserAndCore = convertFTToSeconds(UserTime) + convertFTToSeconds(CoreTime);
			const F64 currentProcTime = convertFTToSeconds(CurrentTime) - convertFTToSeconds(StartTime);
			//Now using the values obtained from the prior run of this function, calculate the current CPU time info...
			const F64 differentialProcTime = currentProcTime - lastProcessTime;
			const F64 differentialUserAndCore = combUserAndCore - lastTotalTime;
			if (differentialUserAndCore > 0.0f) {
				//If the time has updated, update the CPU info...
				lastCPUCyclePerc_Relative = (differentialUserAndCore / (differentialProcTime * 100.0f));
				lastProcessTime = currentProcTime;
				lastTotalTime = combUserAndCore;
			}
			//Exit w/ success....
			return true;
		}

		F64 PlatformTime::convertFTToSeconds(const FILETIME &ft) {
			U64 lastTicks = ((U64(ft.dwHighDateTime) << 32) + ft.dwLowDateTime);
			return F64((lastTicks) / F64(ticksPerSecond));
		}

	};

};