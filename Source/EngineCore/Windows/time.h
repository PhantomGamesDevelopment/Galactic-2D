/**
* Galactic 2D
* Source/EngineCore/Windows/time.h
* Defines necessary time related classes for this class.
* (C) 2014-2015 Phantom Games Development - All Rights Reserved
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
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