/**
* Galactic 2D
* Source/EngineCore/Math/mRect.h
* Definitions for the TRectangle class and it's derived type definitions
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

#ifndef GALACTIC_INTERNAL_RECTANGLE
#define GALACTIC_INTERNAL_RECTANGLE

#include "../PlatformCore/platform.h"

namespace Galactic {

	namespace Core {

		/*
		TRectangle: A simple rectangle class instance to describe a rectangle, template. Derivations come from this class instance.
		*/
		template <typename positionType, typename valueType> class TRectangle {
			public:
				/* Public Class Methods */
				//Default (empty) constructor
				TRectangle() { }
				//Copy Constructor
				TRectangle(TRectangle &cRect) {
					point = cRect.point;
					extent = cRect.extent;
				}
				//Apply Constructor
				TRectangle(positionType iPoint, positionType iExtent) {
					point = iPoint;
					extent = iExtent;
				}
				//Apply from x1, y1, x2, y2
				TRectangle(valueType x1, valueType y1, valueType x2, valueType y2) {
					if (x2 < x1 || y2 < y1) {
						GC_Error("TRectangle::TRectangle(VALUES [%s]): Cannot create a rectangle instance where x2/y2 is < x1/y1", type_name<valueType>::tName());
						if (isFloatType(x1)) {
							point.set(0.0, 0.0);
							extent.set(0.0, 0.0);
							return;
						}
						point.set(0, 0);
						extent.set(0, 0);
						return;
					}
					point.set(x1, y1);
					extent.set((x2-x1), (y2-y1));
				}
				//Apply settings method (From Position2I)
				void set(positionType iPoint, positionType iExtent) {
					point = iPoint;
					extent = iExtent;
				}
				//Apply settings method (From 4 positions [x1, y1, x2, y2])
				void set(valueType x1, valueType y1, valueType x2, valueType y2) {
					if (x2 < x1 || y2 < y1) {
						GC_Error("TRectangle::set(VALUES [%s]): Cannot apply a rectangle instance where x2/y2 is < x1/y1", type_name<valueType>::tName());
						if (isFloatType(x1)) {
							point.set(0.0, 0.0);
							extent.set(0.0, 0.0);
							return;
						}
						point.set(0, 0);
						extent.set(0, 0);
						return;
					}
					point.set(x1, y1);
					extent.set((x2 - x1), (y2 - y1));
				}
				//Returns a character name of the valueType of this rectangle
				const char *whatIsTheVType() const {
					return type_name<valueType>::tName();
				}
				//Test if this is a valid RectangleI instance
				bool isValid() const {
					return FBOOL(extent.length() > 0);
				}
				//Area of rectangle
				valueType area() const {
					return (extent.fetchX() * extent.fetchY());
				}
				//Length of X
				valueType len_X() const {
					return extent.fetchX();
				}
				//Length of Y
				valueType len_Y() const {
					return extent.fetchY();
				}
				//Is the specified point inside this rectangle?
				bool isInside(const positionType &iPoint) const {
					return (iPoint.fetchX() >= point.fetchX() && iPoint.fetchX() < point.fetchX() + extent.fetchX()
						&& iPoint.fetchY() >= point.fetchY() && iPoint.fetchY() < point.fetchY() + extent.fetchY());
				}

				/* Public Class Members */
				positionType point;
				positionType extent;
		};
		
		typedef TRectangle<Position2I, S32> RectangleI;
		typedef TRectangle<Position2F, F32> RectangleF;

	};

};

#endif //GALACTIC_INTERNAL_RECTANGLE