/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* platform.h
*
* Loads up everything needed that is platform specific for Galactic 2D.
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
	#include "Windows/platformWindows.h"
#elif GALACTIC_ANDROID
	#include "Android/platformAndroid.h"
#elif GALACTIC_IPHONE
	#include "IPhone/platformIOS.h"
#elif GALACTIC_MAC
	#include "Mac/platformMac.h"
#elif GALACTIC_LINUX
	#include "Linux/platformLinux.h"
#else
	#error "Unknown platform detected, cancelling build"
#endif

#endif //GALACTIC_PLATFORM