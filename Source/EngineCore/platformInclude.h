/**
* Galactic 2D
* Source/EngineCore/platformInclude.h
* Global header loading and platform load fork
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

#ifndef GALACTIC_PLATFORM_INCLUDE
#define GALACTIC_PLATFORM_INCLUDE

//Load in all of the libs we need in the engine
#include <new>
#include <wchar.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>
#include <string.h>

//Load Generic Template Classes
#include "platformMemory.h"

//Load The Generic Platform
#include "GenericPlatform/memory.h"
#include "GenericPlatform/platformOperations.h"
#include "GenericPlatform/math.h"
#include "GenericPlatform/time.h"
#include "GenericPlatform/platformFunctions.h"
#include "GenericPlatform/atomics.h"

//Load Our Platform
#ifdef GALACTIC_WINDOWS
	#include "Windows/loadPlatform.h"
#elif GALACTIC_ANDROID
	#include "Android/loadPlatform.h"
#elif GALACTIC_IPHONE
	#include "IPhone/loadPlatform.h"
#elif GALACTIC_MAC
	#include "Mac/loadPlatform.h"
#elif GALACTIC_LINUX
	#include "Linux/loadPlatform.h"
#endif

#endif //GALACTIC_PLATFORM_INCLUDE