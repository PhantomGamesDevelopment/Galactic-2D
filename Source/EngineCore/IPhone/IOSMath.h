/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* IOSMath.h
*
* Defines the PlatformMath class for IPhone platforms
**/

#ifdef GALACTIC_IPHONE

	#ifndef GALACTIC_PLATFORM_IOS_PLATFORMMATH
	#define GALACTIC_PLATFORM_IOS_PLATFORMMATH

	namespace Galactic {

		namespace Core {

			/*
			PlatformMath: Wrapper functions and methods to convert IPhone Math functions into a standardized list that the engine may use.
			*/
			class PlatformMath : public GenericPlatformMath {
				//Nothing special here folks!
			};

		};

	};

	#endif //GALACTIC_PLATFORM_IOS_PLATFORMMATH

#endif //GALACTIC_IPHONE