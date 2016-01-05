/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/time.cpp
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

#include "../engineCore.h"
#if GALACTIC_USE_SYS_TIME == 1
	#include <sys/time.h>
	#include <sched.h>
#endif

namespace Galactic {

	namespace Core {

		F64 GenericPlatformTime::timePerCycle = 0.0f;

		UTF16 GenericPlatformTime::fetchTimestamp() {
			//Create a char array to store the result in.
			static C8 timestamp[1024];
			*timestamp = NULL;
			//Fetch the time info
			fetchDateString(timestamp);
			//Note: This line generates C4996, however, strcat_s is not cross-platform compatible, so we ignore it.
			#pragma warning( push )
			#pragma warning( disable : 4996 )
				strcat((UTF8)timestamp, " ");
			#pragma warning( pop )
			fetchSysTime(timestamp + strlen((UTF16)timestamp));
			return timestamp;
		}

		void GenericPlatformTime::fetchSysTime(UTF8 dst) {
			TimeVars t;
			String result;
			PlatformTime::sysTime(t);
			//Convert to String
			result = String::ToStr("%02d:%02d:%02d", t.hours, t.minutes, t.seconds);
			//Note: This line generates C4996, however, strcpy_s is not cross-platform compatible, so we ignore it.
			#pragma warning( push )
			#pragma warning( disable : 4996 )
				strcpy(dst, result.c_str());
			#pragma warning( pop )
		}

		void GenericPlatformTime::fetchDateString(UTF8 dst) {
			TimeVars t;
			String result;
			PlatformTime::sysTime(t);
			//Convert to String
			result = String::ToStr("%02d/%02d/%02d", t.months, t.dayNum, (t.years % 100));
			#pragma warning( push )
			#pragma warning( disable : 4996 )
				strcpy(dst, result.c_str());
			#pragma warning( pop )
		}

		#if GALACTIC_USE_SYS_TIME == 1

			F64 GenericPlatformTime::init() {
				//See __rtdscp info. We're essentially "faking" a CPU here to get the first value.
				timePerCycle = 1.0f / 1000000.0f;
				return PlatformTime::fetchSeconds();
			}

			F64 GenericPlatformTime::fetchSeconds() {
				timeval tv;
				gettimeofday(&tv, NULL);
				return ((F64)tv.tv_sec) + (((F64)tv.tv_usec) / 1000000.0);
			}

			U64 GenericPlatformTime::fetchCycles() {
				timeval tv;
				gettimeofday(&tv, NULL);
				return ((((U64)tv.tv_sec) * 1000000ULL) + ((U64)tv.tv_usec));			
			}

			void GenericPlatformTime::sysTime(TimeVars &c) {
				//fetch timeofday, then convert it to local
				timeval tv;
				gettimeofday(&tv, NULL);
				tm local;
				localtime_r(&tv.tv_sec, &local);
				//Pull out the time variables
				c.years = local.tm_year + 1900;
				c.months = local.tm_mon + 1;
				c.dayOfWeek = local.tm_wday;
				c.dayNum = local.tm_mday;
				c.hours = local.tm_hour;
				c.minutes = local.tm_min;
				c.seconds = local.tm_sec;
				c.miliseconds = tv.tv_usec / 1000;
			}

			void GenericPlatformTime::utcTime(TimeVars &c) {
				//fetch timeofday, then convert it to UTC
				timeval tv;
				gettimeofday(&tv, NULL);
				tm local;
				gmtime_r(&tv.tv_sec, &local);
				//Pull out the time variables
				c.years = local.tm_year + 1900;
				c.months = local.tm_mon + 1;
				c.dayOfWeek = local.tm_wday;
				c.dayNum = local.tm_mday;
				c.hours = local.tm_hour;
				c.minutes = local.tm_min;
				c.seconds = local.tm_sec;
				c.miliseconds = tv.tv_usec / 1000;
			}

		#endif

	}

}
