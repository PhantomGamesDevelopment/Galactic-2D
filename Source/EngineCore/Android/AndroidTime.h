/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* AndroidTime.h
*
* Defines the PlatformTime class for android platforms
**/

#ifdef GALACTIC_ANDROID

	#ifndef GALACTIC_PLATFORM_ANDROID_PLATFORMTIME
	#define GALACTIC_PLATFORM_ANDROID_PLATFORMTIME

	namespace Galactic {

		namespace Core {

			/*
			PlatformTime: Defines a list of methods and members for calculating system time parameters for Android platforms. For the time being, we should
			 be safe using SysTime for android, however, it's possible that not all android devices support it. Possible inspection topic for later...
			*/
			class PlatformTime : public GenericPlatformTime {

			};

		};

	};

	#endif //GALACTIC_PLATFORM_ANDROID_PLATFORMTIME

#endif //GALACTIC_ANDROID