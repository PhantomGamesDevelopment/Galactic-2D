/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/time.h
* Defines necessary time related classes for this class.
* (C) 2014-2016 Phantom Games Development - All Rights Reserved
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

#ifndef GALACTIC_PLATFORM_GENERIC_PLATFORMTIME
#define GALACTIC_PLATFORM_GENERIC_PLATFORMTIME

#include "../engineCore.h"
#if GALACTIC_USE_SYS_TIME == 1
	#include <sys/time.h>
#endif

namespace Galactic {

	namespace Core {

		/*
		CPUTimeInfo: This struct contains methods and values needed to generate information similar to __rdtscp. We use two percentages
		 of CPU usage per cycles to ensure we can get the most reliable result compared to that of __rdtscp where cycles in the millions, etc, 
		 would be needed to ensure this same result. See StackOverflow article (http://stackoverflow.com/questions/275004/c-timer-function-to-provide-time-in-nano-seconds)
		 for more information...
		*/
		struct CPUTimeInfo {
			//Default Constructor
			CPUTimeInfo(F64 lastCPU, F64 lastCPUREL) {
				lastCPUCyclePerc = lastCPU;
				lastCPUCyclePerc_Relative = lastCPUREL;
			}

			//Accumulation operator
			CPUTimeInfo &operator+=(const CPUTimeInfo &c) {
				lastCPUCyclePerc += c.lastCPUCyclePerc;
				lastCPUCyclePerc_Relative += c.lastCPUCyclePerc_Relative;

				THISREF();
			}

			// How much CPU usage has occured since the last call to CPUTimeInfo?
			F64 lastCPUCyclePerc;
			// This is essentially the same as above, but the information is relative to one core. IE: If we had 2 cores, this number would be 2 * lastCPUCyclePerc
			F64 lastCPUCyclePerc_Relative;
		};

		/*
		TimeVars: Implements a basic structure to hold the return values of time variables and some methods for working with time
		*/
		struct TimeVars {
			/* Struct Methods */
			//Default Constructor
			TimeVars() {
				years = 0;
				months = 0;
				dayOfWeek = 0;
				dayNum = 0;
				hours = 0;
				minutes = 0;
				seconds = 0;
				miliseconds = 0;
			}

			//Apply Constructor
			TimeVars(S32 yrs, S32 mo, S32 dow, S32 day, S32 hr, S32 min, S32 sec, S32 ms) { 
				years = yrs;
				months = mo;
				dayOfWeek = dow;
				dayNum = day;
				hours = hr;
				minutes = min;
				seconds = sec;
				miliseconds = ms;
			}

			//Compare two time values and return a result similar to strcmp() where smaller == -1, equal == 0, and larger == 1
			S32 compare(const TimeVars &c) {
				S32 cYears = (years > c.years) ? 1000000 : (years == c.years ? 0 : -1000000);
				S32 cMonths = (months > c.months) ? 100000 : (months == c.months ? 0 : -100000);
				S32 cDayNumber = (dayNum > c.dayNum) ? 10000 : (dayNum == c.dayNum ? 0 : -10000);
				S32 cHours = (hours > c.hours) ? 1000 : (hours == c.hours ? 0 : -1000);
				S32 cMinutes = (minutes > c.minutes) ? 100 : (minutes == c.minutes ? 0 : -100);
				S32 cSeconds = (seconds > c.seconds) ? 10 : (seconds == c.seconds ? 0 : -10);
				S32 cMiliseconds = (miliseconds > c.miliseconds) ? 1 : (miliseconds == c.miliseconds ? 0 : -1);
				//Add everything up!
				S32 result = cYears + cMonths + cDayNumber + cHours + cMinutes + cSeconds + cMiliseconds;
				if (result > 0) {
					return 1;
				}
				else if (result < 0) {
					return -1;
				}
				return 0;
			}

			//Equality Check
			bool operator==(const TimeVars &t) {
				return FBOOL(compare(t) == 0);
			}

			//Inequality Check
			bool operator!=(const TimeVars &t) {
				return FBOOL(compare(t) != 0);
			}

			//Greater Than Check
			bool operator>(const TimeVars &t) {
				return FBOOL(compare(t) == 1);
			}

			//Greater Than or Equal To Check
			bool operator>=(const TimeVars &t) {
				//Note: Using FBOOL(x) triggers C4804, investigation needed.
				return compare(t) >= 0;
			}

			//Less Than Check
			bool operator<(const TimeVars &t) {
				//Note: Using FBOOL(compare(t) == -1) triggers C4806, investigation needed.
				return compare(t) == -1 ? true : false;
			}

			//Less Than or Equal To Check
			bool operator<=(const TimeVars &t) {
				//Note: Using FBOOL(x) triggers C4804, investigation needed.
				return compare(t) <= 0;
			}

			/* Struct Members */
			//Years
			S32 years;
			//Months
			S32 months;
			//Day of the week
			S32 dayOfWeek;
			//Day number
			S32 dayNum;
			//Hours
			S32 hours;
			//Minutes
			S32 minutes;
			//Seconds
			S32 seconds;
			//Miliseconds
			S32 miliseconds;
		};

		/*
		GenericPlatformTime: Implements operations and values for defining a cross-platform time system. This system has two methods of operation.
		 For non-windows platforms that have <sys/time.h>, we simply load up <sys/time.h> and use those time methods to acquire the time parameters, but
		 for windows, we take advantage of the CPU processing to determine the time.
		*/
		class GenericPlatformTime {
			public:
				/* Public Class Methods */
				//Return a CPUTimeInfo object
				static CPUTimeInfo getTimeInfo() {
					return CPUTimeInfo(0.0f, 0.0f);
				}
				//Fetch the amount of time per cycle
				static F64 fetchTPC() {
					return timePerCycle;
				}
				//Convert the specified number of cycles to seconds
				static F64 toSeconds(const U64 numCycles) {
					return F64(numCycles * timePerCycle);
				}
				//Convert the specified number of cycles to miliseconds
				static F64 toMS(const U64 numCycles) {
					return F64(numCycles * timePerCycle * 1000.0f);
				}
				//Update the CPU time information
				static bool updateCPUTimeInfo(F64 dT) {
					return true;
				}
				//Fetch the current timestamp
				static UTF16 fetchTimestamp();
				//Fetch the system time
				static void fetchSysTime(UTF8 dst);
				//Fetch a date string
				static void fetchDateString(UTF8 dst);

				/* If we have access to <sys/time.h>, define the time overlay */
				#if GALACTIC_USE_SYS_TIME == 1
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
				#endif

				/* Public Class Members */
				//Time Constants... (Common values used throughout the engine to compare time values)
				//How many ticks will pass for one milisecond
				static const U64 ticksPerMilisecond = U64DEF(10000);
				//How many ticks will pass for one second
				static const U64 ticksPerSecond = U64DEF(10000000);
				//How many ticks will pass for one minute
				static const U64 ticksPerMinute = U64DEF(600000000);
				//How many ticks will pass for one hour
				static const U64 ticksPerHour = U64DEF(36000000000);
				//How many ticks will pass for one day
				static const U64 ticksPerDay = U64DEF(864000000000);
				//How many ticks will pass for one week
				static const U64 ticksPerWeek = U64DEF(6048000000000);
				//Any number beyond this point is unreliable due to change in month day numbers & even # of days in a year. Individual application
				// developers can account for this information themselves, but for the applications of this engine, this is not necessary...

			protected:
				/* Protected Class Members */
				//This variable stores the amount of time (in seconds) that has passed since the last cycle
				static F64 timePerCycle;
		};
	};

};

#endif //GALACTIC_PLATFORM_GENERIC_PLATFORMTIME