/**
* Galactic 2D
* Source/EngineCore/engineCore.h
* Core module loading, settings, and header calls
* (C) 2014-2016 Phantom Games Development - All Rights Reserved
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
#include "PlatformCore/defines.h"
//Load in the standard platform
#include "PlatformCore/platform.h"
#include "PlatformCore/platformTypes.h"

//Forward Decs for Generic Platform (ToDo: Find a better order of execution)
namespace Galactic {
	namespace Core {
		/* Forward Decs. (ToDo: Find a better order of execution) */
		class String;
		template <typename T> class Vector;
	};
};

//Load up the console.
#include "../Console/console.h"

#include "PlatformCore/platformInclude.h"

//Load up the tools
#include "GenericPlatform/Files/fileManager.h"
#include "Files/fileLogging.h"
#include "Containers/conditionalBlock.h"
#include "Containers/multitypeVar.h"
#include "Tools/endian.h"
#include "Tools/advTools.h"
#include "Tools/charTools.h"
#include "Tools/strTools.h"
#include "Containers/vector.h"
#include "Tools/string.h"
#include "Containers/mSingleton.h"
#include "Containers/map.h"
#include "Files/filePath.h"

//-----------------------------------------------
//Forward Declarations for the EngineCore Toolset
//-----------------------------------------------
namespace Galactic {
	namespace Core {
		class Stream;
		class galacticGUID;
		class Allocater;
	};
};

//-----------------------------------------------
//The EngineCore Toolset
//-----------------------------------------------

#include "Files/flags.h"
#include "Files/fileTools.h"
#include "Files/fileManagerWrapper.h"
#include "Tools/commandLineParams.h"
#include "Stream/stream.h"
#include "Containers/scopedPtr.h"
#include "Containers/autoPtr.h"
#include "Tools/reference.h"
#include "Delegates/engineDelegates.h"
#include "Thread/threadBase.h"
#include "Thread/singleThreadBase.h" 
#include "Thread/threadTasks.h"
#include "Tools/guid.h"
#include "Math/math.h"
#include "Stream/memoryStream.h"
#include "Containers/frameTicker.h"
#include "GenericPlatform/window.h"
#include "GenericPlatform/application.h"
#include "GenericPlatform/Input/cursor.h"

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
extern bool gIgnoreFileLogCalls;

#endif
