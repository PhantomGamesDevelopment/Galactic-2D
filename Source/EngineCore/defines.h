/**
* Galactic 2D
* Source/EngineCore/defines.h
* Engine macros and inline functions
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

#ifndef GALACTIC_DEFINES
#define GALACTIC_DEFINES

//Engine Defines

/* Yep, I just love being hilarious... :) */
//SendToHell(): Throw bad pointers and objects into the fire where they belong.
#define SendToHell(x) delete x; x = NULL;
//SendToPitsOfHell(): Throw bad pointers and objects into the deep pits of hell where they can rot, but not be eliminated.
#define SendToPitsOfHell(x) delete x;
//SendToHeaven(): Send pointers and objects to memory heaven, where their lives end and happiness commences.
#define SendToHeaven(x) free(x) x = NULL;
//SendToGatesOfHeaven(): Send pointers and objects to the gates of memory heaven, I guess they aren't quite... dead... yet.
#define SendToGatesOfHeaven(x) free(x);

/* Console Messaging Shortcuts */
//Print shortut
#define GC_Print(x, ...) ::Galactic::Console::print(x, __VA_ARGS__)
//Warn shortut
#define GC_Warn(x, ...) ::Galactic::Console::warn(x, __VA_ARGS__)
//Error shortut
#define GC_Error(x, ...) ::Galactic::Console::error(x, __VA_ARGS__)
//CError shortut
#define GC_CError(x, ...) ::Galactic::Console::cerr(x, __VA_ARGS__)

/* Type Forcing */
//Force result to boolean
#define FBOOL(x) !!x

/* Trickery Functions, Asset Tools */
//Create Level 1 64-Bit Mask
#define CreateLevel1Mask(v1) (1 << v1)
//Create Level 2 64-Bit Mask
#define CreateLevel2Mask(v1, v2) ((1 << v1) + (1 << v2))
//Create Level 3 64-Bit Mask
#define CreateLevel3Mask(v1, v2, v3) ((1 << v1) + (1 << v2) + (1 << v3))

/* Application based defines */
//Unknown bits are converted to this character to prevent crashing due to invalid string literals
#define BadLiteralConvert '?'

#endif //GALACTIC_DEFINES