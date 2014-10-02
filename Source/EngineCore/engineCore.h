/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* engineCore.h
*
* Loads the core module of the engine.
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
#include "Tools/advTools.h"
#include "Tools/strTools.h"
#include "Tools/dynArray.h"
#include "Tools/string.h"
#include "Tools/mSingleton.h"
#include "Tools/map.h"
#include "Tools/filePath.h"

//Load everything else we need.
#include "Tools/commandLineParams.h"
#include "Delegates/easydelegate.hpp"
#include "Thread/threadBase.h"
#include "Thread/singleThreadBase.h" 
#include "Thread/threadTasks.h"
#include "Tools/frameTicker.h"

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