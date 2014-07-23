/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* console.h
*
* Defines the central Console unit for the Galactic 2D Engine.
**/

#ifndef GALACTIC_CONSOLE
#define GALACTIC_CONSOLE

#include "../EngineCore/engineCore.h"

namespace Galactic {

	/*
	Console Namespace: This is a special namespace in the engine. Console declares a lot of subsidary tools and assets that work similarly to that of the
	 internal namespace methods but with one key difference, they are directly accessible from inside the engine itself. This is also where the scripting
	 language API enters from and the engine's scripting system is all handled through this namespace.
	*/
	namespace Console {

		//init(): initializes the console system. This function is mainly used to enable all of the sub-systems stored inside the console.
		void init();
		//destroy(): disable the console system. This function is called at engine shutdown and is used for final operations and memory cleanup.
		void destroy();

		/* Logger Functions: These are forked off to the mSingleton instance of Console::Logger */
		//print
		void print(UTF16 format, ...);
		//warn
		void warn(UTF16 format, ...);
		//error
		void error(UTF16 format, ...);
		//cerr
		void cerr(UTF16 format, ...);

	};

};

#endif //GALACTIC_CONSOLE