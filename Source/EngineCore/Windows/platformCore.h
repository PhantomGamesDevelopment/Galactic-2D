/**
* Galactic 2D
* Source/EngineCore/Windows/platformCore.h
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

#ifndef PLATFORM_WINDOWS
#define PLATFORM_WINDOWS

	//Test for LLVM/CLang
	#define GALACTIC_USING_LLVM defined(__clang__)

	//Windows already defines CDECL, so undef it first.
	#undef CDECL

	// Define types.
	#ifdef _WIN64
		#define GALACTIC_64BIT_SUPPORT 1
		typedef unsigned __int64 SIZE_T;
	#else
		#undef GALACTIC_64BIT_SUPPORT 
		typedef unsigned long SIZE_T;
	#endif

	//typedef unsigned int DWORD;

	#ifndef NULL
		#define NULL 0
	#endif

	/* Define Standard Platform Flags used throughout the engine */
	//Windows platforms use Little Endian
	#define GALACTIC_USE_LENDIAN 1
	//Windows platforms do not use PThread
	#define GALACTIC_USE_PTHREAD 0
	//Declare the engine to run in desktop mode
	#define GALACTIC_DESKTOP_MODE 1
	//Grant the engine access to microsoft's libcmt functions
	#define GALACTIC_PLATFORM_USELIBCMT 1 
	//Windows does not use <sys/time.h>
	#define GALACTIC_USE_SYS_TIME 0
	//Check is we have access to 128 bit atomics
	#define GALACTIC_128_BIT_ATOMICS (GALACTIC_64BIT_SUPPORT == 1)

	/* Some common C++ calls and replacements go here. */
	//FINLINE: Force a function to be inline regardless of compiler commands, be careful when using this.
	#define FINLINE __forceinline
	//SFIN: Declare a starting point for a function with: static FINLINE, or static __forceinline
	#define SFIN static FINLINE
	//CDECL: Standard C Function (Calling Convention)
	#define CDECL __cdecl
	//STDCALL: Standard Calling Convention
	#define STDCALL __stdcall
	#if GALACTIC_USING_LLVM
		//VS_ALIGN: Byte alignment property for MSVS
		#define VS_ALIGN(x) 
		//GNU_ALIGN: Byte alignment property for GNU GCC
		#define GNU_ALIGN(x) __attribute__((aligned(n)))
	#else
		//VS_ALIGN: Byte alignment property for MSVS
		#define VS_ALIGN(x) __declspec(align(x))
		//GNU_ALIGN: Byte alignment property for GNU GCC
		#define GNU_ALIGN(x)
	#endif
	//U64DEF: Macro for properly declaring and formatting 64-bit numerics
	#define U64DEF(x) x

	#define GALACTIC_DLL_IMPORT __declspec(dllimport)
	#define GALACTIC_DLL_EXPORT __declspec(dllexport)

#endif //PLATFORM_WINDOWS