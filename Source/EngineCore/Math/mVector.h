/**
* Galactic 2D
* Source/EngineCore/Math/mVector.h
* Definitions for the Vector2F class
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

#ifndef GALACTIC_INTERNAL_VECTOR
#define GALACTIC_INTERNAL_VECTOR

#include "../platform.h"
#include "../../Console/console.h"

namespace Galactic {

	namespace Core {

		namespace Math {
	
			/*
			Vector2F: A basic class for manipulating and working with 2D-Cartesian Space Vectors.
			*/
			class Vector2F : public TwoVarCont<F64, F64> {
				public:
					//Set method
					void Vector2F::set(F64 x1, F64 x2) {
						x = x1;
						y = x2;
					}

					/* Operators */
					// Vector Addition Operator
					Vector2F &operator+(Vector2F &v) {		
						Vector2F v;
						v.set(x + v.x, y + v.y);
						return v;
					}
				
					//Vector Subtraction Operator
					Vector2F &operator-(Vector2F &v) {
						Vector2F v;
						v.set(x - v.x, y - v.y);
						return v;
					}

					//Vector Multiplication
					Vector2F &operator*(Vector2F &v) {
						Vector2F v;
						v.set(x * v.x, y * v.y);
						return v;
					}

					//Vector Scaling
					Vector2F &operator*(F64 s) {
						Vector2F v;
						v.set(x * s, y * s);
						return v;
					}

					/* Additional Functions */
					// Vector Normalize
					void normalize() {
						if(length() == 0) {
							GC_Error("Cannot Normalize a vector with 0 length");
							return;
						}
						x /= length();
						y /= length();
					}

					// Vector Length
					F64 length() const { return PlatformMath::mSqrt(PlatformMath::mPow(x, 2) + PlatformMath::mPow(y, 2)); }

					// Vector Dot Product
					F64 dot(Vector2F &v) const { return ((x * v.x) + (y * v.y)); }

					// Vector Cross Product (IE: 2D Determinant), 2D Vector Cross Product returns a Scalar
					F64 cross(Vector2F &v) const { return((x * v.y) - (y * v.x)); }
					F64 det(Vector2F &v) const { return cross(v); }

					//Angle Between
					F64 ang(Vector2F &v) const { return (PlatformMath::mATan2(v.y, v.x) - PlatformMath::mATan2(y, x)); }
			};
	
			//Position Typedef
			typedef Vector2F Position2;

		};
		
	};

};

#endif //GALACTIC_INTERNAL_VECTOR