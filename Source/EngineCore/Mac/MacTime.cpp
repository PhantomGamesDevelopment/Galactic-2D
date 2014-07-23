/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* MacTime.cpp
*
* Defines the PlatformTime class for the Macintosh Platforms
**/

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		F64 PlatformTime::init() {
			//Info on Absolute Time Here: http://stackoverflow.com/questions/1450737/what-is-mach-absolute-time-based-on-on-iphone
			mach_timebase_info_data_t absTimeInfo;
			if (mach_timebase_info(&absTimeInfo) != 0) {
				//Something went wrong...
				GC_Error("PlatformTime::init(): Failed to initialize timebase information...");
				return 0;
			}
			timePerCycle = (0.000000001) * (F64)absTimeInfo.numer / (F64)absTimeInfo.denom;
			return PlatformTime::fetchSeconds();
		}

		F64 PlatformTime::fetchSeconds() {
			//We want to start by calculating the absolute time (or number of CPU cycles), then multiply by timePerCycle.
			U64 absTime = mach_absolute_time();
			return F64(absTime * timePerCycle);
		}

		U64 PlatformTime::fetchCycles() {
			return mach_absolute_time();
		}

	};

};