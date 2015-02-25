/**
* Galactic 2D
* Source/EngineCore/IPhone/platformCore.h
* Settings and typedefs for this platform
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

#ifndef PLATFORM_IOS
#define PLATFORM_IOS

	// Define types.
	#ifdef __LP64__
		#define GALACTIC_64BIT_SUPPORT 1
	#else
		#undef GALACTIC_64BIT_SUPPORT
	#endif
	typedef size_t SIZE_T;
	typedef unsigned int DWORD;

	#ifndef NULL
		#define NULL 0
	#endif

	/* Define Standard Platform Flags used throughout the engine */
	//IOS platforms use Little Endian
	#define GALACTIC_USE_LENDIAN 1
	//IOS platforms use PThread
	#define GALACTIC_USE_PTHREAD 1
	//IOS cannot use desktop mode
	#define GALACTIC_DESKTOP_MODE 0
	//IOS does not have libcmt access
	#define GALACTIC_PLATFORM_USELIBCMT 0 
	//IOS has access to <sys/time.h>
	#define GALACTIC_USE_SYS_TIME 1
	//IOS does not have 128-bit atomics
	#define GALACTIC_128_BIT_ATOMICS 0

	/* Some common C++ calls and replacements go here. */
	//FINLINE: Force a function to be inline regardless of compiler commands, be careful when using this.
	#define FINLINE inline __attribute__ ((always_inline))
	//SFIN: Declare a starting point for a function with: static FINLINE, or static __forceinline
	#define SFIN static FINLINE
	//CDECL: Standard C Function (Calling Convention)
	#define CDECL 
	//STDCALL: Standard Calling Convention
	#define STDCALL 
	//VS_ALIGN: Byte alignment property for MSVS
	#define VS_ALIGN(x)
	//GNU_ALIGN: Byte alignment property for GNU GCC
	#define GNU_ALIGN(x) __attribute__((aligned(x)))
	//U64DEF: Macro for properly declaring and formatting 64-bit numerics
	#define U64DEF(x) x##ULL

	#define GALACTIC_DLL_IMPORT 
	#define GALACTIC_DLL_EXPORT

#endif //PLATFORM_IOS