/**
* Galactic 2D
* Source/EngineCore/Math/mLimits.h
* Definitions for the mathematical limits contained by the engine's variable types
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

#ifndef GALACTIC_INTERNAL_NUMLIMITS
#define GALACTIC_INTERNAL_NUMLIMITS

//The minimum value of S8: 0x80 or -128
#define MIN_S8 ((S8)0x80)
//The maximum value of S8: 0x7F or 127
#define MAX_S8 ((S8)0x7F)
//The minimum value of U8: 0x00 or 0
#define MIN_U8 ((U8)0x00)
//The maximum value of U8: 0xFF or 255
#define MAX_U8 ((U8)0xFF)
//The minimum value of S16: 0x8000 or -32768
#define MIN_S16 ((S16)0x8000)
//The maximum value of S16: 0x7FFF or 32767
#define MAX_S16 ((S16)0x7FFF)
//The minimum value of U16: 0x0000 or 0
#define MIN_U16 ((U16)0x0000)
//The maximum value of U16: 0xFFFF or 65535
#define MAX_U16 ((U16)0xFFFF)
//The minimum value of S32: 0x80000000 or -2147483648
#define MIN_S32 ((S32)0x80000000)
//The maximum value of S32: 0x7FFFFFFF or 2147483647
#define MAX_S32 ((S32)0x7FFFFFFF)
//The minimum value of U32: 0x00000000 or 0
#define MIN_U32 ((U32)0x00000000)
//The maximum value of U32: 0xFFFFFFFF or 4294967295
#define MAX_U32 ((U32)0xFFFFFFFF)
//The minimum value of F32: Defined Internally As 1.175494351e-38F
#define MIN_F32 ((F32)1.175494351e-38F)
//The maximum value of F32: Defined Internally As 3.402823466e+38F
#define MAX_F32 ((F32)3.402823466e+38F)
//The minimum value of S64: 0x8000000000000000 or -9223372036854775808
#define MIN_S64 ((S64)0x8000000000000000)
//The maximum value of S64: 0x7FFFFFFFFFFFFFFF or 9223372036854775807
#define MAX_S64 ((S64)0x7FFFFFFFFFFFFFFF)
//The minimum value of U64: 0x0000000000000000 or 0
#define MIN_U64 ((U64)0x0000000000000000)
//The maximum value of U64: 0xFFFFFFFFFFFFFFFF or 18446744073709551615
#define MAX_U64 ((U64)0xFFFFFFFFFFFFFFFF)
//The minimum value of F64: Defined Internally As 2.2250738585072014e-308
#define MIN_F64 ((F64)2.2250738585072014e-308)
//The maximum value of F64: Defined Internally As 3.1.7976931348623158e+308+38F
#define MAX_F64 ((F64)1.7976931348623158e+308)

#endif //GALACTIC_INTERNAL_NUMLIMITS