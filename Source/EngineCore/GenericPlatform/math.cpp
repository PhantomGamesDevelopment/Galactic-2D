/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/math.cpp
* Defines the platform specific math class and functions
* (C) 2014-2015 Phantom Games Development - All Rights Reserved
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

namespace Galactic {

	namespace Core {
		
		S32 GenericPlatformMath::TruncateToInteger(F32 value) {
			return (S32)value;
		}

		S32 GenericPlatformMath::TruncateToInteger(F64 value) {
			return (S32)value;
		}

		S32 GenericPlatformMath::FloorDownToInt(F32 value) {
			return TruncateToInteger(floorf(value));
		}

		S32 GenericPlatformMath::FloorDownToInt(F64 value) {
			return TruncateToInteger(floor(value));
		}

		F32 GenericPlatformMath::Floor(F32 value) {
			return floorf(value);
		}

		F64 GenericPlatformMath::Floor(F64 value) {
			return floor(value);
		}

		S32 GenericPlatformMath::CeilUpToInt(F32 value) {
			return TruncateToInteger(ceilf(value));
		}

		S32 GenericPlatformMath::CeilUpToInt(F64 value) {
			return TruncateToInteger(ceil(value));
		}

		F32 GenericPlatformMath::Ceil(F32 value) {
			return ceilf(value);
		}

		F64 GenericPlatformMath::Ceil(F64 value) {
			return ceil(value);
		}

		S32 GenericPlatformMath::RoundToInt(F32 value) {
			return FloorDownToInt(value + 0.5f);
		}

		S32 GenericPlatformMath::RoundToInt(F64 value) {
			return FloorDownToInt(value + 0.5);
		}

		F32 GenericPlatformMath::RoundToF32(F32 value) {
			return Floor(value + 0.5f);
		}

		F64 GenericPlatformMath::RoundToF64(F64 value) {
			return Floor(value + 0.5);
		}

		template <class T> T GenericPlatformMath::mMin(const T A, const T B) {
			return (A <= B ? A : B);
		}

		template <class T> T GenericPlatformMath::mMax(const T A, const T B) {
			return (A >= B ? A : B);
		}

		template <class T> T GenericPlatformMath::mAbs(const T value) {
			return (value >= T(0) ? value : -value);
		}

		template <> F32 GenericPlatformMath::mAbs(const F32 value) {
			return fabsf(value);
		}

		template <> F64 GenericPlatformMath::mAbs(const F64 value) {
			return abs(value);
		}

		F32 GenericPlatformMath::mSin(F32 value) {
			return sinf(value);
		}

		F64 GenericPlatformMath::mSin(F64 value) {
			return sin(value);
		}

		F32 GenericPlatformMath::mCos(F32 value) {
			return cosf(value);
		}

		F64 GenericPlatformMath::mCos(F64 value) {
			return cos(value);
		}

		F32 GenericPlatformMath::mTan(F32 value) {
			return tanf(value);
		}

		F64 GenericPlatformMath::mTan(F64 value) {
			return tan(value);
		}

		F32 GenericPlatformMath::mASin(F32 value) {
			//asinf is only valid [-1.f, 1.f]
			return asinf((value < -1.f ? -1.f : (value < 1.f ? value : 1.f)));
		}

		F64 GenericPlatformMath::mASin(F64 value) {
			//asin is only valid [-1.0, 1.0]
			return asin((value < -1.0 ? -1.0 : (value < 1.0 ? value : 1.0)));
		}

		F32 GenericPlatformMath::mACos(F32 value) {
			//acosf is only valid [-1.f, 1.f]
			return acosf((value < -1.f ? -1.f : (value < 1.f ? value : 1.f)));
		}

		F64 GenericPlatformMath::mACos(F64 value) {
			//acos is only valid [-1.0, 1.0]
			return acos((value < -1.0 ? -1.0 : (value < 1.0 ? value : 1.0)));
		}

		F32 GenericPlatformMath::mATan(F32 value) {
			return atanf(value);
		}

		F64 GenericPlatformMath::mATan(F64 value) {
			return atan(value);
		}

		F32 GenericPlatformMath::mATan2(F32 x, F32 y) {
			return atan2f(x, y);
		}

		F64 GenericPlatformMath::mATan2(F64 x, F64 y) {
			return atan2(x, y);
		}

		F32 GenericPlatformMath::mPow(F32 value, F32 power) {
			return powf(value, power);
		}

		F64 GenericPlatformMath::mPow(F64 value, F64 power) {
			return pow(value, power);
		}

		F32 GenericPlatformMath::mSqrt(F32 value) {
			return sqrtf(value);
		}

		F64 GenericPlatformMath::mSqrt(F64 value) {
			return sqrt(value);
		}

		F32 GenericPlatformMath::mInvSr(F32 value) {
			return (1.0f / sqrtf(value));
		}

		F64 GenericPlatformMath::mInvSr(F64 value) {
			return (1.0 / sqrt(value));
		}

		F32 GenericPlatformMath::mExp(F32 value) {
			return expf(value);
		}

		F64 GenericPlatformMath::mExp(F64 value) {
			return exp(value);
		}

		F32 GenericPlatformMath::mLn(F32 value) {
			return logf(value);
		}

		F64 GenericPlatformMath::mLn(F64 value) {
			return log(value);
		}

		F32 GenericPlatformMath::mLog(F32 value, F32 base) {
			return (logf(value) / logf(base));
		}

		F64 GenericPlatformMath::mLog(F64 value, F64 base) {
			return (log(value) / log(base));
		}

		bool GenericPlatformMath::mIsNegativeF32(const F32 &value) {
			return ((*(U32 *)&value) >= (U32)SignBitF32);
		}

		bool GenericPlatformMath::mIsFinite(F32 value) {
			return ((*(U32 *)&value) & NaNLimitF32) != NaNLimitF32;
		}

		bool GenericPlatformMath::mIsNaN(F32 value) {
			return ((*(U32 *)&value) & F32BitLimit) > NaNLimitF32;
		}

		void GenericPlatformMath::mRandInit(S32 seed) {
			srand(seed);
		}

		S32 GenericPlatformMath::mRand() {
			return rand();
		}

		F32 GenericPlatformMath::mFRand() {
			return (rand() / (F32)RAND_MAX);
		}

	};

};
