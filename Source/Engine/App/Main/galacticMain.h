/**
* Galactic 2D
* Source/Engine/App/Main/galacticMain.h
* Defines the GalacticMain class which is responsible for the engine loops
* (C) 2014 Phantom Games Development - All Rights Reserved
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

#include "../../../EngineCore/engineCore.h"

//Include... everything..
#include "../Game/genre.h"

#ifndef GALACTIC_ENGINE_APP_MAIN_ENGINEMAIN
#define GALACTIC_ENGINE_APP_MAIN_ENGINEMAIN

namespace Galactic {
	
	namespace Engine {

		namespace Application {

			class GalacticMain {
				public:
					//Different init defs based on compiler build params.
					static bool init(S32 argc, UTF8 argv[]);
					static bool init(UTF8 argv);

					static bool initialize(String args);
					static bool parseCommandLine(String args);
					static bool mainLoop();
					static void shutdown();

				private:
					static void preShutdown();

					static UTF16 game;
					static UTF16 mod;
			};

		};

	};

};

#endif //GALACTIC_ENGINE_APP_MAIN_ENGINEMAIN