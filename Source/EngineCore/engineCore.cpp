/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* engineCore.cpp
*
* Loads the core module of the engine.
**/

#include "engineCore.h"

/*
	This file mainly exists to declare some engine-wide flags that can be toggled throughout the code to handle important tasks
	within the engine itself.
*/

//Define Global Classes to NULL
Allocater *_GAllocater    = NULL;      //Define the global memory allocater

//Global Parameters
F64  gVolumeModifier      = 1.0f;      //gvolumeModifier: Declares the global audio modifier to levels of output, set to 0.0f to silence the app.
bool gRunning             = false;     //gRunning: Is execution in mainLoop() occuring?
bool gWantExit            = false;     //gWantExit: Has a quit() command or equivalent been sent?
U32  gMainGameThreadID    = 0;         //gMainGameThreadID: Set once the game thread object is initialized.
bool gMainThreadInitd     = false;     //gMainThreadIntd: Flag to determine if the main game thread has been created yet.
U64  gFrameCount          = 0;         //gFrameCount: The total amount of frames that have been rendered since init(); 
bool gInInitialLoad       = true;      //gInInitialLoad: Flag to check if the engine is still in the initial loading sequence (mainly to disable some stuff that shouldn't be done too early)
bool gSuspendRender       = false;     //gSuspendRender: This is a debug flag that can be enabled to block the next render call for tracing.