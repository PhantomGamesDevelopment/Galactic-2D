/**
* Galactic 2D
* Source/EngineCore/engineCore.cpp
* Core module loading, settings, and header calls
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