/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* loadWindows.h
*
* Load all of the platform windows classes and objects
**/

// Instance of our application
//extern "C" HINSTANCE hInstance;

// Settings and C++ libs that are windows specific.
#include <intrin.h>
#include <tchar.h>

//load Windows.h now
#include "safeWindowsH.h"

//Load the rest of our headers, notice how they match alongside genericPlatform includes.
#include "WinMemory.h"
#include "WinTime.h"
#include "WinCriticalSection.h"
#include "WinThread.h"
#include "WinAtomics.h"