/**
* Galactic 2D
* Source/EngineCore/platformTypes.h
* Global engine typedefs and declarations
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

#ifndef GALACTIC_PLATFORMTYPES
#define GALACTIC_PLATFORMTYPES

/* Data Type Declaration */
template<typename T> struct type_name {
	static const char* tName() { return "UNDEFINED"; }
};

template<typename IT32, typename IT64, int sizeOfVoid> struct IntPointerType {
	// Template... Define Nothin!
};
template<typename IT32, typename IT64> struct IntPointerType <IT32, IT64, 4> {
	//Define the 32 bit as the target type.
	typedef IT32 TargetType;
};
template<typename IT32, typename IT64> struct IntPointerType <IT32, IT64, 8> {
	//Define the 64 bit as the target type.
	typedef IT64 TargetType;
};

typedef signed char S8;        //Signed Character
typedef unsigned char U8;      //Unsigned Character
typedef signed short S16;      //Signed Short
typedef unsigned short U16;    //Unsigned Short
typedef signed int S32;        //Signed Integer
typedef unsigned int U32;      //Unsigned Integer
typedef signed long long S64;  //Signed 64 bit Integer
typedef unsigned long long U64;//Unsigned 64 bit Integer

//Define Shorthand "const" numerical types, why you ask? 
// 1. I'm lazy :) 
// 2. Nobody else does this, so I know who is "using" my code.

typedef const S8 X8;
typedef const U8 Z8;
typedef const S16 X16;
typedef const U16 Z16;
typedef const S32 X32;
typedef const U32 Z32;
typedef const bool cbol;

//Define Standard C++ Types

typedef char C8;               //Character
typedef float F32;             //32-bit Floating Point Number
typedef double F64;            //64-bit Floating Point Number (Double) 
//typedef long double F128;      //128-Bit Floating Point Numer (To-Do: Putting this here for the future)
typedef char* UTF8;            //Character Pointer
typedef const char* UTF16;     //Constant Character Pointer	
//Define C-Style character types
typedef wchar_t WCHAR;
typedef WCHAR TCHAR;
//Define Additional Types
typedef U8* UTX8;              //Unsigned Character Pointer (Byte Pointer)
typedef const U8* UTX16;       //Constant Unsigned Character Pointer
//Define void types
typedef void* any;             //Pointer to any data type
typedef const void* cAny;      //Constant pointer to anything
typedef void *& anyRef;        //Pointer reference to any type
typedef const void *& cAnyRef; //Constant Pointer reference to any type

//Define integer target types
typedef IntPointerType<S32, S64, sizeof(any)>::TargetType IntPointer;         //Define platform pointer for S32/S64
typedef IntPointerType<U32, U64, sizeof(any)>::TargetType UnsingedIntPointer; //Define platform pointer for U32/U64

//Declare Standard Typenames to Console (This is primarily used for template classes)
DECL_TYPE_NAME(S8);
DECL_TYPE_NAME(U8);
DECL_TYPE_NAME(S16);
DECL_TYPE_NAME(U16);
DECL_TYPE_NAME(S32);
DECL_TYPE_NAME(U32);
DECL_TYPE_NAME(S64);
DECL_TYPE_NAME(U64);
DECL_TYPE_NAME(X8);
DECL_TYPE_NAME(Z8);
DECL_TYPE_NAME(X16);
DECL_TYPE_NAME(Z16);
DECL_TYPE_NAME(X32);
DECL_TYPE_NAME(Z32);
DECL_TYPE_NAME(cbol);
DECL_TYPE_NAME(C8);
DECL_TYPE_NAME(F32);
DECL_TYPE_NAME(F64);
DECL_TYPE_NAME(UTF8);
DECL_TYPE_NAME(UTF16);
DECL_TYPE_NAME(UTX8);
DECL_TYPE_NAME(UTX16);

namespace Galactic {

	/* NOTE: These are global min/max functions, for more specific ones, use PlatformMath::mMin() / PlatformMath::mMax() */

	FINLINE S8 gMin(S8 a, S8 b) { return a > b ? b : a; }
	FINLINE S8 gMax(S8 a, S8 b) { return a > b ? a : b; }
	FINLINE U8 gMin(U8 a, U8 b) { return a > b ? b : a; }
	FINLINE U8 gMax(U8 a, U8 b) { return a > b ? a : b; }
	FINLINE S16 gMin(S16 a, S16 b) { return a > b ? b : a; }
	FINLINE S16 gMax(S16 a, S16 b) { return a > b ? a : b; }
	FINLINE U16 gMin(U16 a, U16 b) { return a > b ? b : a; }
	FINLINE U16 gMax(U16 a, U16 b) { return a > b ? a : b; }
	FINLINE S32 gMin(S32 a, S32 b) { return a > b ? b : a; }
	FINLINE S32 gMax(S32 a, S32 b) { return a > b ? a : b; }
	FINLINE U32 gMin(U32 a, U32 b) { return a > b ? b : a; }
	FINLINE U32 gMax(U32 a, U32 b) { return a > b ? a : b; }
	FINLINE S64 gMin(S64 a, S64 b) { return a > b ? b : a; }
	FINLINE S64 gMax(S64 a, S64 b) { return a > b ? a : b; }
	FINLINE U64 gMin(U64 a, U64 b) { return a > b ? b : a; }
	FINLINE U64 gMax(U64 a, U64 b) { return a > b ? a : b; }

	template <typename T> FINLINE bool isFloatType(T v) {
		return (strcmp(type_name<T>::tName(), "float") == 0 || strcmp(type_name<T>::tName(), "double") == 0
			|| strcmp(type_name<T>::tName(), "F32") == 0 || strcmp(type_name<T>::tName(), "F64") == 0);
	}

};

#endif //GALACTIC_PLATFORMTYPES