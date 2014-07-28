/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* mVector.h
*
* Defines a mathematical 2D vector class
**/

#ifndef GALACTIC_INTERNAL_VECTOR
#define GALACTIC_INTERNAL_VECTOR

#include "../platform.h"
#include "../../Console/console.h"

namespace Galactic {

	namespace Core {

		namespace Math {
	
			class Vector2F {
				public:
					F64 x; // x-component
					F64 y; // y-component

					Vector2F::Vector2F(F64 iX = 0.0f, F64 iY = 0.0f) {
						x = iX;
						y = iY;
					}
					/* Operators */
					// Vector Addition Operator
					Vector2F operator+(Vector2F &v) {
						return Vector2F(x + v.x, y + v.y);
					}
				
					//Vector Subtraction Operator
					Vector2F operator-(Vector2F &v) {
						return Vector2F(x - v.x, y - v.y);
					}

					//Vector Multiplication
					Vector2F operator*(Vector2F &v) {
						return Vector2F(x * v.x, y * v.y);
					}

					//Vector Scaling
					Vector2F operator*(F64 s) {
						return Vector2F(x * s, y * s);
					}

					//Copy
					Vector2F operator=(Vector2F &v) {
						return Vector2F(v.x, v.y);
					}

					//Equality
					bool operator==(Vector2F &v) {
						return (x == v.x && y == v.y);
					}

					//Inequality
					bool operator!=(Vector2F &v) {
						return (x != v.x || y != v.y);
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
					F64 length() const { return sqrt(pow(x, 2) + pow(y, 2)); }

					// Vector Dot Product
					F64 dot(Vector2F &v) const { return ((x * v.x) + (y * v.y)); }

					// Vector Cross Product (IE: 2D Determinant), 2D Vector Cross Product returns a Scalar
					F64 cross(Vector2F &v) const { return((x * v.y) - (y * v.x)); }
					F64 det(Vector2F &v) const { return cross(v); }

					//Angle Between
					F64 ang(Vector2F &v) const { return (atan2(v.y, v.x) - atan2(y, x)); }
			};
	
			//Position Typedef
			typedef Vector2F Position2;
		};

	};

};

#endif //GALACTIC_INTERNAL_VECTOR