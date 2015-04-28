/**
* Galactic 2D
* Source/EngineCore/engineCore.h
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

#ifndef GALACTIC_ENGINECORE
#define GALACTIC_ENGINECORE

//Load the engine settings first.
#include "galacticSettings.h"

//Load up the engine files now.
#include "platform.h"
#include "platformTypes.h"
#include "defines.h"

//Forward Decs for Generic Platform (ToDo: Find a better order of execution)
namespace Galactic {
	namespace Core {
		/* Forward Decs. (ToDo: Find a better order of execution) */
		class String;
		template <typename T> class DynArray;
	}
}

#include "platformInclude.h"

//Load up the tools
#include "Containers/multitypeVar.h"
#include "Tools/advTools.h"
#include "Tools/strTools.h"
#include "Tools/charTools.h"
#include "Containers/dynArray.h"
#include "Tools/string.h"
#include "Containers/mSingleton.h"
#include "Containers/map.h"
#include "Tools/filePath.h"

//Load everything else we need.
#include "Tools/commandLineParams.h"
#include "Delegates/engineDelegates.h"
#include "Thread/threadBase.h"
#include "Thread/singleThreadBase.h" 
#include "Thread/threadTasks.h"
#include "Containers/frameTicker.h"

//Give the user a using namespace override so they don't need to use ::Galactic::Core::X in all of their files.
using namespace Galactic::Core;

/*
 Extern Access: Give all of our global flags and tools access to the files.
*/
extern F64  gVolumeModifier;
extern bool gRunning;
extern bool gWantExit;
extern U32  gMainGameThreadID;
extern bool gMainThreadInitd;
extern U64  gFrameCount;
extern bool gInInitialLoad;
extern bool gSuspendRender;

#endif
