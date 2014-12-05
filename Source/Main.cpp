/**
* Galactic 2D
* Source/Main.cpp
* The primary entry point of the engine software
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

#include "EngineCore/engineCore.h"
#include "Engine/App/Main/galacticMain.h"

using namespace Galactic::Engine::Application;

#ifdef WIN32

	//Forward Dec Start Codes
	S32 galactic_init(UTF8 argv);
	S32 galactic_engine_tick();
	S32 galactic_shutdown();

	//Main: Entry Point of the Engine.
	S32 __stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCommandShow ) {
		// Galactic 2D Entry Point
		if(!galactic_init(lpszCmdLine)) {
			return 1;
		}

		while(galactic_engine_tick()) {}

		galactic_shutdown();
		return 0;
	}

	//Engine startup
	S32 galactic_init(UTF8 argv) {
		//Load up the loadup render window
	
		//Load the engine's systems up and go.
		return GalacticMain::init(argv);
	}

	//Engine Loop
	S32 galactic_engine_tick() {
		//Run the engine loop code, return 0 if a quit() command was sent.
		return GalacticMain::mainLoop();
	}

	//Engine Shutdown
	S32 galactic_shutdown() {
		//Deallocate all used memory & shutdown engine systems
		GalacticMain::shutdown();
		//return 1 for proper shutdown. That's all folks!
		return 1;
	}

#elif defined(__MACOSX__) || defined(__linux__)

	//Forward Dec Start Codes
	S32 galactic_init(S32 argc, UTF8 argv[]);
	S32 galactic_engine_tick();
	S32 galactic_shutdown();

	S32 main(S32 argc, UTF8 argv[]) {
		// Galactic 2D Entry Point
		if(!galactic_init(argc, argv)) {
			return 1;
		}

		while(galactic_engine_tick()) {}

		galactic_shutdown();
		return 0;	
	}

	//Engine startup
	S32 galactic_init(S32 argc, UTF8 argv) {
		//Load up the loadup render window
	
		//Load the engine's systems up and go.
		return GalacticMain::init(argc, argv);
	}

	//Engine Loop
	S32 galactic_engine_tick() {
		//Run the engine loop code, return 0 if a quit() command was sent.
		return GalacticMain::mainLoop();
	}

	//Engine Shutdown
	S32 galactic_shutdown() {
		//Deallocate all used memory & shutdown engine systems
		GalacticMain::shutdown();
		//return 1 for proper shutdown. That's all folks!
		return 1;
	}

#else

	//Something went terribly wrong, stop the build
	#error "Cannot locate a OS Flag to compile against, please check your C++ compiler or affirm you are using a supported platform."

#endif