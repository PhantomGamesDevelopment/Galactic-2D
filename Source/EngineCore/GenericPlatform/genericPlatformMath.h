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

		//This is the maximum bit limit of the F32, anything higher will result in NaN.
		#define F32BitLimit 0x7FFFFFFF
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
				//Templated minimum functions
				template <class T> SFIN T mMin(const T A, const T B);
				//Templated maximum functions
				template <class T> SFIN T mMax(const T A, const T B);
				//Templated absolute value function
				template <class T> SFIN T mAbs(const T value);
				//F32 has access to fabsf via <math.h>, this will bypass the above definition for that
				template <> SFIN F32 mAbs(const F32 value);
				//F64 has access to abs via <math.h>, this will bypass the above definition for that
				template <> SFIN F64 mAbs(const F64 value);

				/* Trigonometric Functions */
				//Calculate the Sine (in radians)
				SFIN F32 mSin(F32 value);
				//Calculate the Sine (in radians)
				SFIN F64 mSin(F64 value);
				//Calculate the Cosine (in radians)
				SFIN F32 mCos(F32 value);
				//Calculate the Cosine (in radians)
				SFIN F64 mCos(F64 value);
				//Calculate the Tangent (in radians)
				SFIN F32 mTan(F32 value);
				//Calculate the Tangent (in radians)
				SFIN F64 mTan(F64 value);
				//Calculate the Arc-Sine (in radians)
				SFIN F32 mASin(F32 value);
				//Calculate the Arc-Sine (in radians)
				SFIN F64 mASin(F64 value);
				//Calculate the Arc-Cosine (in radians)
				SFIN F32 mACos(F32 value);
				//Calculate the Arc-Cosine (in radians)
				SFIN F64 mACos(F64 value);
				//Calculate the Arc-Tangent (in radians)
				SFIN F32 mATan(F32 value);
				//Calculate the Arc-Tangent (in radians)
				SFIN F64 mATan(F64 value);
				//Calculate the Arc-Tangent (in radians) using X & Y components
				SFIN F32 mATan2(F32 x, F32 y);
				//Calculate the Arc-Tangent (in radians) using X & Y components
				SFIN F64 mATan2(F64 x, F64 y);

				/* Logarithmic & Exponential Functions */
				//Calculate the numerical power of a value
				SFIN F32 mPow(F32 value, F32 power);
				//Calculate the numerical power of a value
				SFIN F64 mPow(F64 value, F64 power);
				//Calculate the square root of a value
				SFIN F32 mSqrt(F32 value);
				//Calculate the square root of a value
				SFIN F64 mSqrt(F64 value);
				//Calculate the inverse square root of a value
				SFIN F32 mInvSr(F32 value);
				//Calculate the inverse square root of a value
				SFIN F64 mInvSr(F64 value);
				//Calaculate the exponential power e^x of a number
				SFIN F32 mExp(F32 value);
				//Calaculate the exponential power e^x of a number
				SFIN F64 mExp(F64 value);
				//Calculate the natural logarithm of a value
				SFIN F32 mLn(F32 value);
				//Calculate the natural logarithm of a value
				SFIN F64 mLn(F64 value);
				//Calculate the logarithm of a value provided with a number and a base
				SFIN F32 mLog(F32 value, F32 base);
				//Calculate the logarithm of a value provided with a number and a base
				SFIN F64 mLog(F64 value, F64 base);

				/* Mathematical Library Checks (For F32) */
				//Is the floating point value negative?
				SFIN bool mIsNegativeF32(const F32 &value);
				//Is the number finite?
				SFIN bool mIsFinite(F32 value);
				//Is this number NaN by the definition of F32?
				SFIN bool mIsNaN(F32 value);

				/* Random Numbers */
				//Initialize the random number generate (seed)
				SFIN void mRandInit(S32 seed);
				//Generate a random number between 0 and RAND_MAX
				SFIN S32 mRand();
				//Generate a random floating point number between 0 and 1
				SFIN F32 mFRand();
		};

	};

};

#endif //GALACTIC_PLATFORM_GENERIC_PLATFORMMATH