/**
* Galactic 2D
* Source/EngineCore/Tools/color.h
* Defines engine color types
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

#ifndef GALACTIC_INTERNAL_COLOR
#define GALACTIC_INTERNAL_COLOR

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		//Forward Dec for ColorF
		class ColorF;
	
		//ColorI - Define a RGB Color
		class ColorI {
			public:
				U32 r; // Red Component
				U32 g; // Green Component
				U32 b; // Blue Component
				U32 a; // Alpha Component

				//Default Constructor.
				ColorI(U32 red = 255, U32 green = 255, U32 blue = 255, U32 alpha = 255) {
					r = red;
					g = green;
					b = blue;
					a = alpha;

					fix();
				}

				//Create from ColorF
				ColorI(ColorF in);

				//Fix the color to ColorI Ranges
				void fix() {
					if(r < 0) {
						r = 0;
					}
					if(r > 255) {
						r = 255;
					}

					if(g < 0) {
						g = 0;
					}
					if(g > 255) {
						g = 255;
					}

					if(b < 0) {
						b = 0;
					}
					if(b > 255) {
						b = 255;
					}

					if(a < 0) {
						a = 0;
					}
					if(a > 255) {
						a = 255;
					}
				}

				ColorF toColorF();
		};

		//ColorF - Define a RGBA Color With a range of 0.0 to 1.0
		class ColorF {
			public:
				F64 r; // Red Component
				F64 g; // Green Component
				F64 b; // Blue Component
				F64 a; // Alpha Component

				ColorF(F64 red = 1.0f, F64 green = 1.0f, F64 blue = 1.0f, F64 alpha = 1.0f) {
					r = red;
					g = green;
					b = blue;
					a = alpha;

					fix();
				}

				ColorF(ColorI in);

				//Fix the color to ColorF Ranges
				void fix() {
					if(r < 0.0f) {
						r = 0.0f;
					}
					if(r > 1.0f) {
						r = 1.0f;
					}

					if(g < 0.0f) {
						g = 0.0f;
					}
					if(g > 1.0f) {
						g = 1.0f;
					}

					if(b < 0.0f) {
						b = 0.0f;
					}
					if(b > 1.0f) {
						b = 1.0f;
					}

					if(a < 0.0f) {
						a = 0.0f;
					}
					if(a > 1.0f) {
						a = 1.0f;
					}
				}

				ColorI toColorI();
		};

		/* 
		Function Definitions 
		 Note: We need to use inline here otherwise the compiler will belive this to be a static instance and every class
		 in the engine that uses ColorI / ColorF will complain about redefinition
		*/

		FINLINE ColorI::ColorI(ColorF in) {
			r = U32(in.r * 255.0f + 0.5);
			g = U32(in.g * 255.0f + 0.5);
			b = U32(in.b * 255.0f + 0.5);
			a = U32(in.a * 255.0f + 0.5);

			fix();		
		}

		FINLINE ColorF ColorI::toColorF() {
			F64 convFactor = 1.0f / 255.0f;
			return ColorF(F64((r)* convFactor), F64((g)* convFactor), F64((b)* convFactor), F64((a)* convFactor));
		}

		FINLINE ColorF::ColorF(ColorI in) {
			F64 convFactor = 1.0f / 255.0f;

			r = (in.r) * convFactor;
			g = (in.g) * convFactor;
			b = (in.b) * convFactor;
			a = (in.a) * convFactor;

			fix();		
		}

		FINLINE ColorI ColorF::toColorI() {
			return ColorI(U32(r * 255.0f + 0.5), U32(g * 255.0f + 0.5), U32(b * 255.0f + 0.5), U32(a * 255.0f + 0.5));
		}

	};

};

#endif //GALACTIC_INTERNAL_COLOR