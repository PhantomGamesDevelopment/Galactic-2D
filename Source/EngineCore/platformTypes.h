/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* platformTypes.h
*
* Loads up everything needed that is platform specific for Galactic 2D.
**/

#ifndef GALACTIC_PLATFORMTYPES
#define GALACTIC_PLATFORMTYPES

/*
Including the platform module first defines all of the engine's data types.
*/

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
typedef float F32;             //Floating Point Number
typedef double F64;            //Double 
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

namespace Galactic {

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

};

#endif //GALACTIC_PLATFORMTYPES