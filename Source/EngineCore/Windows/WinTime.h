/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* WinTime.h
*
* Defines the PlatformTime class for windows platforms
*
* References: 
*  http://stackoverflow.com/questions/17432502/how-can-i-measure-cpu-time-and-wall-clock-time-on-both-linux-windows
**/

#ifdef GALACTIC_WINDOWS	

	#ifndef GALACTIC_PLATFORM_WINDOWS_PLATFORMTIME
	#define GALACTIC_PLATFORM_WINDOWS_PLATFORMTIME

	namespace Galactic {

		namespace Core {

			/*
			PlatformTime: Defines a list of methods and members for calculating system time parameters for Windows platforms.
			*/
			class PlatformTime : public GenericPlatformTime {
				public:
					/* Public Class Methods */
					//Initialize the class, fetch timePerCycle and return a numerical parameter for current time
					static F64 init();
					//Fetch the current seconds
					SFIN F64 fetchSeconds();
					//Fetch the amount of cycles that have passed
					SFIN U64 fetchCycles();
					//Fetch the system time
					static void sysTime(TimeVars &c);
					//Fetch the UTC time
					static void utcTime(TimeVars &c);
					//Return a CPUTimeInfo object
					static CPUTimeInfo getTimeInfo();
					//Update the CPU time information
					static bool updateCPUTimeInfo(F64 dT);

				protected:
					/* Protected Class Methods */
					//Convert a specified FILETIME to seconds...
					SFIN F64 convertFTToSeconds(const FILETIME &ft);
					/* Protected Class Members */
					//For windows, we only need the relatvie CPU processing for one core calculation to determine time.
					static F64 lastCPUCyclePerc_Relative;
			};

		};

	};

	#endif //GALACTIC_PLATFORM_WINDOWS_PLATFORMTIME

#endif GALACTIC_WINDOWS