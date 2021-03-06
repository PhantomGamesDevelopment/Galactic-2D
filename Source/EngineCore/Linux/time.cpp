/**
* Galactic 2D
* Source/EngineCore/Linux/time.cpp
* Defines necessary time related classes for this class.
* (C) 2014-2015 Phantom Games Development - All Rights Reserved
*
* References:
*  http://stackoverflow.com/questions/17432502/how-can-i-measure-cpu-time-and-wall-clock-time-on-both-linux-windows
*  http://www.raspberry-projects.com/pi/programming-in-c/timing/clock_gettime-for-acurate-timing
*  http://rabbit.eng.miami.edu/info/functions/time.html
*  Staff Discussion on PGD for using clock()...
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

#include "../engineCore.h"

#ifdef GALACTIC_LINUX

	namespace Galactic {

		namespace Core {

			F64 PlatformTime::fetchSeconds() {
				struct timespec timeInfo;
				clock_gettime(CLOCK_MONOTONIC, &timeInfo);
				//Convert to F64...
				return F64(timeInfo.tv_sec) + (F64(timeInfo.tv_nsec) / F64(0.000000001));
			}

			U64 PlatformTime::fetchCycles() {
				struct timespec timeInfo;
				clock_gettime(CLOCK_MONOTONIC, &timeInfo);
				return (U64(timeInfo.tv_sec) * U64DEF(1000000)) + (U64(timeInfo.tv_nsec) / U64DEF(1000));
			}

			CPUTimeInfo PlatformTime::getTimeInfo() {
				//Recall, in WinTime.cpp that when we initialize the ticker delegate that we enforce a dT minima of 1.0f/4.0f due to OS restrictions. We want to keep
				// the engine's time classes in line with one another to ensure the sim runs with parallel time calculations so, we "fake" the same effect here.
				// Remember that Linux runs in nanoseconds... 1/4s = 0.25s = 250000000ns.
				const F64 minimumUpdateFreq = 250000000.0;
				//Now, we pull a page from the WinTime.cpp playbook in the updateCPUTimeInfo() method here.
				static F64 lastProcessTime = 0.0f, lastTotalTime = 0.0f;
				//Linux doesn't have FILETIME, so instead we make use of clock(), which has F64 variable types.
				static F64 currentCPUUtil = 0.0f, normalizedCCPUU = 0.0f;
				struct timespec timeInfo;
				if (clock_gettime(CLOCK_MONOTONIC, &timeInfo) == 0) {
					const F64 currentTimeInNanoSec = F64(timeInfo.tv_sec * 1000000000) + F64(timeInfo.tv_nsec);
					//If we're in the time constraints mentioned above, go ahead and update.
					if ((currentTimeInNanoSec - lastProcessTime) >= minimumUpdateFreq) {
						struct rusage cpuUsage;
						//We use getrusage to determine how 'active' the CPU has been since the last cycle...
						if (getrusage(RUSAGE_SELF, &cpuUsage) == 0) {
							//Fetch all of the usage into a time variable, then calculate how much of that was used by the CPU itself since the last call.
							const F64 allTime = toMicroseconds(cpuUsage.ru_stime) + toMicroseconds(cpuUsage.ru_utime);
							const F64 usageSincePriorCall = allTime - lastTotalTime;
							//The last thing we need to do is calculate the relative effect of one CPU versus all of the available ones, then re-apply values.
							F64 cpuUsagePercentage = usageSincePriorCall / ((currentTimeInNanoSec - lastProcessTime) / 1000.0) * 100.0;
							//Re-apply values.
							currentCPUUtil = (F64)cpuUsagePercentage;
							normalizedCCPUU = cpuUsagePercentage / (F64)PlatformOperations::numLogicalCores();
							lastProcessTime = allTime;
							lastTotalTime = currentTimeInNanoSec;
						}
					}
				}
				//Return a CPUTimeInfo object with the current usage and 1-core relative usage.
				return CPUTimeInfo(currentCPUUtil, normalizedCCPUU);
			}

			F64 PlatformTime::toMicroseconds(timeval &timeInfo) {
				return (F64(timeInfo.tv_sec * 1000000) + F64(timeInfo.tv_usec));
			}

		};

	};

#endif //GALACTIC_LINUX