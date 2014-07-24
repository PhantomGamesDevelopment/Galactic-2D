/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* LinuxTime.h
*
* Defines the PlatformTime class for Linux Platforms
*
* References:
*  http://stackoverflow.com/questions/17432502/how-can-i-measure-cpu-time-and-wall-clock-time-on-both-linux-windows
*  http://www.raspberry-projects.com/pi/programming-in-c/timing/clock_gettime-for-acurate-timing
*  http://rabbit.eng.miami.edu/info/functions/time.html
*  Staff Discussion on PGD for using clock()...
**/

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