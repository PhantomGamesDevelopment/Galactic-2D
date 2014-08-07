/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* genericPlatformMath.h
*
* Defines mathematical methods and operations that are specific to individual platforms and require a cross-platform wrapper.
**/

#ifndef GALACTIC_PLATFORM_GENERIC_PLATFORMMATH
#define GALACTIC_PLATFORM_GENERIC_PLATFORMMATH

namespace Galactic {

	namespace Core {

		//This is the absolute highest value allowed (F32) before the compiler treats it as NaN.
		#define NaNLimitF32 0x7F800000
		//This is the location offset of the sign (+/-) stored on a F32. 
		#define SignBitF32 0x80000000

		/*
		GenericPlatformMath: Wrapper functions and methods to convert platform specific math functions to a cross-platform overlay. These are mainly templates
		*/
		class GenericPlatformMath {
			public:
				/* Public Class Methods */
				/* Basic Mathematical Operations */
				//Truncate a F32 to an integer with a preference towards zero.
				SFIN S32 TruncateToInteger(F32 value);
				//Truncate a F64 to an integer with a preferene towards zero.
				SFIN S32 TruncateToInteger(F64 value);
				//Apply the floor operation to a F32, then convert it to an S32.
				SFIN S32 FloorDownToInt(F32 value);
				//Apply the floor operation to a F64, then convert it to an S32.
				SFIN S32 FloorDownToInt(F64 value);
				//Directly floor the F32
				SFIN F32 Floor(F32 value);
				//Directly floor the F64
				SFIN F64 Floor(F64 value);
				//Apply the ceil operation to a F32, then convert it to an S32.
				SFIN S32 CeilUpToInt(F32 value);
				//Apply the ceil operation to a F64, then convert it to an S32.
				SFIN S32 CeilUpToInt(F64 value);
				//Directly ceil the F32
				SFIN F32 Ceil(F32 value);
				//Directly ceil the F64
				SFIN F64 Ceil(F64 value);
				//Round F32 to S32
				SFIN S32 RoundToInt(F32 value);
				//Rounf F64 to S32
				SFIN S32 RoundToInt(F64 value);
				//Round F32 to F32
				SFIN F32 RoundToF32(F32 value);
				//Round F64 to F64
				SFIN F64 RoundToF64(F64 value);

				/* Trigonometric Functions */
				//Calculate the Sine (in radians)
				SFIN F32 mSin(F32 value);
				//Calculate the Cosine (in radians)
				SFIN F32 mCos(F32 value);
				//Calculate the Tangent (in radians)
				SFIN F32 mTan(F32 value);
		};

	};

};

#endif //GALACTIC_PLATFORM_GENERIC_PLATFORMMATH