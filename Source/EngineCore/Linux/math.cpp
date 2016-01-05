/**
* Galactic 2D
* Source/EngineCore/Linux/math.cpp
* Defines the platform specific math class and functions
* (C) 2014-2016 Phantom Games Development - All Rights Reserved
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

#ifdef GALACTIC_LINUX	

namespace Galactic {

	namespace Core {

			S32 PlatformMath::TruncateToInteger(F32 value) {
				return _mm_cvtt_ss2si(_mm_set_ss(value));
			}

			S32 PlatformMath::FloorDownToInt(F32 value) {
				//There's an issue with _mm_cvt_ss2si() when the decimal value sits exactly on 0.5 that couses this method to round down to the nearest
				// even number, even if you have like 2.5, you'll get 0.0. To fix this, we apply a little trick using a bit shift and forcing the method
				// to think we're actually sending 2(value) instead of value. See http://msdn.microsoft.com/en-us/library/ft91czdc.aspx
				F32 sendNum = (2 * value) - 0.5f;
				return _mm_cvt_ss2si(_mm_set_ss(sendNum)) >> 1;
			}

			F32 PlatformMath::Floor(F32 value) {
				return (F32)FloorDownToInt(value);
			}

			S32 PlatformMath::CeilUpToInt(F32 value) {
				//Read the notes for RoundToInt() and FloorDownToInt(). The approach with the Ceil method is slightly different. Instead, we approach this
				// as if we we're sending a decreased version of the number. The only problem here is by doing this, the value will now be negative instead
				// of positive, therefore we need to flip the final result. We use this method because performing it on values with a point less than 0.5 will
				// almost always end up with a number 1 less than what we expect. See http://msdn.microsoft.com/en-us/library/ft91czdc.aspx
				
				//Test: CeilUpToInt(2.9), Should get 3.0: 
				//F32 sendNum = (-0.5 - (5.8)) = -6.3
				//__mm_cvt_ss2si(_mm_set_ss(-6.3)) = -6.0
				// -6.0 >> 1 = -3.0
				// -1 * -3.0 = 3.0
				F32 sendNum = -0.5f - (2 * value);
				return -(_mm_cvt_ss2si(_mm_set_ss(sendNum)) >> 1);
			}

			F32 PlatformMath::Ceil(F32 value) {
				return (F32)CeilUpToInt(value);
			}

			S32 PlatformMath::RoundToInt(F32 value) {
				//There's an issue with _mm_cvt_ss2si() when the decimal value sits exactly on 0.5 that couses this method to round up to the nearest
				// even number, even if you have like 2.5, you'll get 4.0. To fix this, we apply a little trick using a bit shift and forcing the method
				// to think we're actually sending 2(value) instead of value. See http://msdn.microsoft.com/en-us/library/ft91czdc.aspx
				F32 sendNum = (2 * value) + 0.5f;
				return _mm_cvt_ss2si(_mm_set_ss(sendNum)) >> 1;
			}

			F32 PlatformMath::RoundToF32(F32 value) {
				return (F32)RoundToInt(value);
			}

			bool PlatformMath::mIsFinite(F32 value) {
				return FBOOL(isfinite(value) != 0);
			}

			bool PlatformMath::mIsNaN(F32 value) {
				return FBOOL(isnan(value) != 0);
			}

	};

};

#endif //GALACTIC_LINUX