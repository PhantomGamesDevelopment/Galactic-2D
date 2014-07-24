/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* IOSTime.h
*
* Defines the PlatformTime class for the IOS (IPhone) Platform
**/

#ifdef GALACTIC_IPHONE

	#ifndef GALACTIC_PLATFORM_IOS_PLATFORMTIME
	#define GALACTIC_PLATFORM_IOS_PLATFORMTIME

	namespace Galactic {

		namespace Core {

			/*
			PlatformTime: Defines a list of methods and members for calculating system time parameters for IPhone platforms.
			*/
			class PlatformTime : public GenericPlatformTime {
				public:
					/* Public Class Methods */
					//Initialize the class, fetch timePerCycle and return a numerical parameter for current time
					static F64 init();
					//Fetch the current seconds
					SFIN F64 fetchSeconds();
					//Fetch the amount of cycles that have passed
					SFIN U64 fetchCycles();
			};

		};

	};

	#endif //GALACTIC_PLATFORM_IOS_PLATFORMTIME

#endif //GALACTIC_IPHONE