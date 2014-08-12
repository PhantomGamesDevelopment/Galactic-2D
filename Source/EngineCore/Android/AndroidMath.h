/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* AndroidMath.h
*
* Defines the PlatformMath class for android platforms
**/

#ifdef GALACTIC_ANDROID

	#ifndef GALACTIC_PLATFORM_ANDROID_PLATFORMMATH
	#define GALACTIC_PLATFORM_ANDROID_PLATFORMMATH

	namespace Galactic {

		namespace Core {

			/*
			PlatformMath: Wrapper functions and methods to convert Android Math functions into a standardized list that the engine may use.
			*/
			class PlatformMath : public GenericPlatformMath {
				//Nothing special here folks!
			};

		};

	};

	#endif //GALACTIC_PLATFORM_ANDROID_PLATFORMMATH

#endif //GALACTIC_ANDROID