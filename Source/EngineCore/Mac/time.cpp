/**
* Galactic 2D
* Source/EngineCore/Mac/time.cpp
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

#include "../engineCore.h"

#ifdef GALACTIC_MAC

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

#endif //GALACTIC_MAC