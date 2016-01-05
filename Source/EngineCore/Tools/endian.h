/**
* Galactic 2D
* Source/EngineCore/endian.h
* Conversions between endian data types.
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

#ifndef GALACTIC_PLATFORM_ENDIAN
#define GALACTIC_PLATFORM_ENDIAN

namespace Galactic {

	namespace Core {

		/*
		The first half of this file handles conversion of the individual data types between the two endian types
		*/

		//U8 - No Conversion Needed
		FINLINE U8 convertEndian(Z8 in) {
			return in;
		}

		//C8 - No Conversion Needed
		FINLINE S8 convertEndian(X8 in) {
			return in;
		}

		//U16 - Swap & shift the bytes
		FINLINE U16 convertEndian(Z16 in) {
			return U16(((in >> 8) & 0x00ff) | ((in << 8) & 0xff00));
		}

		//S16 - Swap & shift the bytes
		FINLINE S16 convertEndian(X16 in) {
			return S16(convertEndian(U16(in)));
		}

		//U32 - Swap & shift the bytes
		FINLINE U32 convertEndian(Z32 in) {
			return U32(((in >> 24) & 0x000000ff) |
				((in >> 8) & 0x0000ff00) |
				((in << 8) & 0x00ff0000) |
				((in << 24) & 0xff000000));
		}

		//S32 - Swap & shift the bytes
		FINLINE S32 convertEndian(X32 in) {
			return S32(convertEndian(U32(in)));
		}

		//U64 - Swap & shift the bytes.... alot of them... x_X
		FINLINE U64 convertEndian(const U64 in) {
			//Yeah... x-x
			return U64(((in >> 56) & (U64(0x00000000000000ff))) |
				((in >> 40) & (U64(0x000000000000ff00))) |
				((in >> 24) & (U64(0x0000000000ff0000))) |
				((in >> 8) & (U64(0x00000000ff000000))) |
				((in << 8) & (U64(0x000000ff00000000))) |
				((in << 24) & (U64(0x0000ff0000000000))) |
				((in << 40) & (U64(0x00ff000000000000))) |
				((in << 56) & (U64(0xff00000000000000))));
		}

		//S64 - Swap & shift the bytes.... alot of them... x_X
		FINLINE S64 convertEndian(const S64 in) {
			return S64(convertEndian(U64(in)));
		}

		/*
		While I generally want to avoid all practices involving disabling or suppressing compiler warnings, not suppressing this one can
		 cause a lot of eye-rape in the warning counter. There is absolutely nothing wrong with typecasting F32 to U32 and F64 to U64 to perform
		 bitwise shifts and then converting back, no matter how much C++ wants to complain about signed versus unsigned, therefore I'm disabling
		 C4244 for this code block. ~ RCF (Phantom139)
		*/
		#pragma warning( push )
		#pragma warning( disable : 4244 )

		//F32 - Dereference to U32, then swap
		FINLINE F32 convertEndian(const F32 in) {
			F32 result = convertEndian(* ((U32 *) &in));
			return *((F32 *) &result);
		}

		//F64 - Dereference to U64, then swap
		FINLINE F64 convertEndian(const F64 in) {
			F64 result = convertEndian(* ((U64 *) &in));
			return *((F64 *) &result);
		}

		#pragma warning( pop )
		/*
		The second half of this file defines some usable functions that depend on if GALACTIC_USE_LENDIAN or GALACTIC_USE_BENDIAN
		is defined by the platform.h header file
		*/
		#ifdef GALACTIC_USE_LENDIAN

			/*
				GALACTIC_DECLARE_ENDIANCONVERT(): GALACTIC_USE_LENDIAN
				Convert instances of big endian to little endian and return little endian values without converting.
			*/
			#define GALACTIC_DECLARE_ENDIANCONVERT(data_type) \
				FINLINE data_type convertSrcToLittleEndian(data_type x) { return x; } \
				FINLINE data_type convertLittleEndianToSrc(data_type x) { return x; } \
				FINLINE data_type convertSrcToBigEndian(data_type x) { return convertEndian(x); } \
				FINLINE data_type convertBigEndianToSrc(data_type x) { return convertEndian(x); }

		#elif defined(GALACTIC_USE_BENDIAN)

			/*
				GALACTIC_DECLARE_ENDIANCONVERT(): GALACTIC_USE_BENDIAN
				Convert instances of little endian to big endian and return big endian values without converting.
			*/
			#define GALACTIC_DECLARE_ENDIANCONVERT(data_type) \
				FINLINE data_type convertSrcToLittleEndian(data_type x) { return convertEndian(x); } \
				FINLINE data_type convertLittleEndianToSrc(data_type x) { return convertEndian(x); } \
				FINLINE data_type convertSrcToBigEndian(data_type x) { return x; } \
				FINLINE data_type convertBigEndianToSrc(data_type x) { return x; } 

		#else
			#error "Galactic 2D: No Endian Type Specified, please validate platform.h and that you have a supported compile platform"
		#endif

		//Now, using the macro above, declare the endian convert functions we'll need in our engine for ALL of the data types.
		GALACTIC_DECLARE_ENDIANCONVERT(S8);
		GALACTIC_DECLARE_ENDIANCONVERT(U8);
		GALACTIC_DECLARE_ENDIANCONVERT(S16);
		GALACTIC_DECLARE_ENDIANCONVERT(U16);
		GALACTIC_DECLARE_ENDIANCONVERT(S32);
		GALACTIC_DECLARE_ENDIANCONVERT(U32);
		GALACTIC_DECLARE_ENDIANCONVERT(F32);
		GALACTIC_DECLARE_ENDIANCONVERT(S64);
		GALACTIC_DECLARE_ENDIANCONVERT(U64);
		GALACTIC_DECLARE_ENDIANCONVERT(F64);

	};

};

#endif //GALACTIC_PLATFORM_ENDIAN