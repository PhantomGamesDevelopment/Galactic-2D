/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* MacMath.h
*
* Defines the PlatformMath class for macintosh platforms
**/

#ifdef GALACTIC_MAC	

	#ifndef GALACTIC_PLATFORM_MAC_PLATFORMMATH
	#define GALACTIC_PLATFORM_MAC_PLATFORMMATH

	namespace Galactic {

		namespace Core {

			/*
			PlatformMath: Wrapper functions and methods to convert Macintosh Math functions into a standardized list that the engine may use.
			*/
			class PlatformMath : public GenericPlatformMath { 
				public:
					/* Public Class Methods */
					/* Basic Mathematical Operations */
					//Truncate a F32 to an integer with a preference towards zero.
					SFIN S32 TruncateToInteger(F32 value);
					//Apply the floor operation to a F32, then convert it to an S32.
					SFIN S32 FloorDownToInt(F32 value);
					//Directly floor the F32
					SFIN F32 Floor(F32 value);
					//Apply the ceil operation to a F32, then convert it to an S32.
					SFIN S32 CeilUpToInt(F32 value);
					//Directly ceil the F32
					SFIN F32 Ceil(F32 value);
					//Round F32 to S32
					SFIN S32 RoundToInt(F32 value);
					//Round F32 to F32
					SFIN F32 RoundToF32(F32 value);

					/* Mathematical Library Checks (For F32) */
					//Is the number finite?
					SFIN bool mIsFinite(F32 value);
					//Is this number NaN by the definition of F32?
					SFIN bool mIsNaN(F32 value);
			};

		};

	};

	#endif //GALACTIC_PLATFORM_MAC_PLATFORMMATH

#endif //GALACTIC_MAC