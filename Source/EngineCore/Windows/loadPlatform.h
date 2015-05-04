/**
* Galactic 2D
* Source/EngineCore/Windows/loadPlatform.h
* Loads up all of the necessary platform headers and our files
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

// Instance of our application
extern "C" HINSTANCE hInstance;

// Settings and C++ libs that are windows specific.
#include <intrin.h>
#include <tchar.h>

//load Windows.h now
#include "loadWinH.h"

//Load the rest of our headers, notice how they match alongside genericPlatform includes.
#include "memory.h"
#include "math.h"
#include "time.h"
#include "platformFunctions.h"
#include "threadUtilityClasses.h"
#include "atomics.h"