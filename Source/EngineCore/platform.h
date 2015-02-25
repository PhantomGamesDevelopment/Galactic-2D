/**
* Galactic 2D
* Source/EngineCore/platform.h
* Platform detection and initialization
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

#ifndef GALACTIC_PLATFORM
#define GALACTIC_PLATFORM

/* 
  Now we detect the platform we're using
*/
#if defined(_WIN64) || defined(_WIN32)
	#define GALACTIC_WINDOWS 1
#elif __ANDROID__
	//We need to pull in <stddef> in android for size_t
	#include <stddef.h> 
	#define GALACTIC_ANDROID 1
#elif __APPLE__
	#define GALACTIC_APPLE 1
	//Regardless of which apple we target, we need to pull in <stddef.h> for size_t
	#include <stddef.h> 
	#include <TargetConditionals.h>
	#if TARGET_OS_IPHONE
		#define GALACTIC_IPHONE 1
	#elif TARGET_OS_MAC
		#define GALACTIC_MAC 1
	#else
		#error "Unidentified Apple Platform Detected, Cannot Proceed..."
	#endif
#elif defined(__linux) || defined(__unix)
	#define GALACTIC_LINUX 1
#else
	#error "No platform detected."
#endif

/*
  Load in the platform header file
*/
#ifdef GALACTIC_WINDOWS
	#include "Windows/platformCore.h"
#elif GALACTIC_ANDROID
	#error "Android is currently unsupported on G2D, This is a planned RC2 update"
	#include "Android/platformCore.h"
#elif GALACTIC_IPHONE
	#error "IPhone is currently unsupported on G2D, This is a planned RC2 update"
	#include "IPhone/platformCore.h"
#elif GALACTIC_MAC
	#error "Mac is currently unsupported on G2D, This is a planned RC2 update"
	#include "Mac/platformCore.h"
#elif GALACTIC_LINUX
	#error "Linux is currently unsupported on G2D, This is a planned RC2 update"
	#include "Linux/platformCore.h"
#else
	#error "Unknown platform detected, cancelling build"
#endif

#endif //GALACTIC_PLATFORM