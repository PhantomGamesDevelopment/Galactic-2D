/**
* Galactic 2D
* Source/Console/console.h
* Defines the connection point between the engine and the scripting language for the engine
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

#include "logging.h"

#ifndef GALACTIC_CONSOLE
#define GALACTIC_CONSOLE

/* Console Messaging Shortcuts */
//Print shortut
#define GC_Print(x, ...) ::Galactic::Console::print(x, __VA_ARGS__)
//Warn shortut
#define GC_Warn(x, ...) ::Galactic::Console::warn(x, __VA_ARGS__)
//Error shortut
#define GC_Error(x, ...) ::Galactic::Console::error(x, __VA_ARGS__)
//CError shortut
#define GC_CError(x, ...) ::Galactic::Console::cerr(x, __VA_ARGS__)

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