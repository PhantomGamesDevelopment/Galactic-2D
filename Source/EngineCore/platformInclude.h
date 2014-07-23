/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* platformInclude.h
*
* Loads in every single file we need.
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
#include "GenericPlatform/genericMemory.h"
#include "GenericPlatform/genericPlatformOperations.h"
#include "GenericPlatform/genericPlatformTime.h"
#include "GenericPlatform/genericPlatform.h"
#include "GenericPlatform/genericPlatformAtomics.h"

//Load Our Platform
#ifdef GALACTIC_WINDOWS
	#include "Windows/loadWindows.h"
#elif GALACTIC_ANDROID
	#include "Android/loadAndroid.h"
#elif GALACTIC_IPHONE
	#include "IPhone/loadIOS.h"
#elif GALACTIC_MAC
	#include "Mac/loadMac.h"
#elif GALACTIC_LINUX
	#include "Linux/loadLinux.h"
#endif

#endif //GALACTIC_PLATFORM_INCLUDE