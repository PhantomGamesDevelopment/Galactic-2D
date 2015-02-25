/**
* Galactic 2D
* Source/EngineCore/Linux/time.h
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

#ifdef GALACTIC_LINUX

	#ifndef GALACTIC_PLATFORM_LINUX_PLATFORMTIME
	#define GALACTIC_PLATFORM_LINUX_PLATFORMTIME

	#include <sys/resource.h>

	namespace Galactic {

		namespace Core {

			/*
			PlatformTime: Defines a list of methods and members for calculating system time parameters for Linux platforms.
			*/
			class PlatformTime : public GenericPlatformTime {
				/* Public Class Methods */
				//Fetch the current seconds
				SFIN F64 fetchSeconds();
				//Fetch the amount of cycles that have passed
				SFIN U64 fetchCycles();
				//Return a CPUTimeInfo object
				static CPUTimeInfo getTimeInfo();
				//Convert to microseconds
				static F64 toMicroseconds(timeval &timeInfo);
			};

		};

	};

	#endif //GALACTIC_PLATFORM_LINUX_PLATFORMTIME

#endif //GALACTIC_LINUX