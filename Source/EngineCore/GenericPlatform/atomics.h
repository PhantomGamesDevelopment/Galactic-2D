/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/atomics.h
* Defines the PlatformAtomics class for the engine
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

#ifndef GALACTIC_PLATFORM_GENERIC_ATOMICS
#define GALACTIC_PLATFORM_GENERIC_ATOMICS

namespace Galactic {

	namespace Core {

		/*
		S128: Internal representation of a 128-bit integer (IE: cross platform _int128), uses two S64's to accomplish this.
		 We force the alignment to 16-byte boundaries to meet requirements on most processers today
		*/
		struct VS_ALIGN(16) S128 {
			/* Struct Methods */
			//Default Constructor
			S128(S64 l, S64 h) : low(l), high(h) { }
			/* Struct Members */
			//The low part of the integer
			S64 low;
			//The high part of the integer
			S64 high;
		} GNU_ALIGN(16);

	};

};

#endif //GALACTIC_PLATFORM_GENERIC_ATOMICS