/**
* Galactic 2D
* Source/Engine/App/Main/galacticMain.cpp
* Defines the GalacticMain class which is responsible for the engine loops
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

#include "galacticMain.h"

namespace Galactic {

	using namespace Core;
	
	namespace Engine {

		namespace Application {

			bool GalacticMain::parseCommandLine(String args) {
				/**
				bool safeToRun = true;
				UTF8 currentField, currentValue;
				//Run through all of the provided arguments.
				for(S32 i = 1; i < argc; i += 2) {
					currentField = argv[i];
					currentValue = argv[i+1];
					//List of options below.
					// -game <module>: Load up the game's module
					if(strcmp(currentField, "-game") == 0) {
						#if GALACTIC_INDIE_BUILD >= 1
							//Do a quick check to make sure we have a main.lua and a accompanying .dll with the game, If we don't have this stuff, 
							//then we can't launch the game, push an error.
							//safeToRun = false;
							game = strdup(currentValue);
						#else
							//Non-Indie builds will simply edit this engine code directly (unless you want to lib out your files?), therefore we only
						    //need to hunt down main.lua and get going.
						#endif
						//Add the game to the load queue, this will kick things off after the engine's core functioning loads up.
					}
					// -mod <modname>: Load up the game with a mod enabled.
					else if(strcmp(currentField, "-mod") == 0) {
						#if GALACTIC_ALLOW_MODS >=1
							//Add the mod to the load queue, if anything goes wrong, we'll push an error after the game initializes.
							mod = strdup(currentValue);
						#else
							//ToDo: Push an error stating that the -mod tag is disabled.
						#endif
					}
				}
				return safeToRun;
				**/
				return true;
			}

			//UNIX Build Init
			bool GalacticMain::init(S32 argc, UTF8 argv[]) {
				String arguments;
				for(S32 i = 0; i < argc; i++) {
					arguments += argv[i];
					if(i != argc-1) {
						arguments += "\t";
					}
				}
				return initialize(arguments);
			}

			//Windows Build Init
			bool GalacticMain::init(UTF8 argv) {
				return initialize(argv);
			}

			//Generic Initialize Functions
			bool GalacticMain::initialize(String args) {
				//The very first thing we need to do is to parse our command line arguments to ensure everything we need
				// is there, and is "correct".
				if(!parseCommandLine(args)) {
					//Push an error?
					return false;
				}
				//Once we get past this step, we can start initializing our game's core systems.
				//Load in the thread pool...
				if (PlatformProcess::isMultithreaded()) {
					G_ThreadPool = WorkPoolBase::createInstance();
					//How many threads do we want in there?
					S32 threadsToSpawn = PlatformOperations::numThreadsToSpawn();
					if (!G_ThreadPool->createWithAmount(threadsToSpawn)) {
						//Something went wrong, unfortunately, the console isn't initalized yet, so GC_Error can't be used here.
						// ToDo: Add some kind of pre-init buffer for the console to push init messages on to.
					}
				}
				//Load up the Genre Controller
				managedSingleton<Galactic::Engine::Game::Genre>::createInstance();
				//Load the Console and the Scripting Engine
				Galactic::Console::init();
				//Once the core is active, we can load in the Game's modules as needed.
				
				//Check for an internal project
				#ifdef GALACTIC_INTERNAL_PROJECT
					//As stated by the reference, if GALACTIC_INTERNAL_PROJECT is defined, then FINLINE void initInternalProject() must exist under Galactic {}
					::Galactic::initInternalProject();
				#endif

				//And lastly, if a -mod parameter is defined, lets load in the mod.

				//Engine's all loaded and we're ready to go!
				return true;
			}

			//Called prior to full shutdown to allow deallocation of script related stuffs.
			void GalacticMain::preShutdown() {
			
			}
			
			void GalacticMain::shutdown() {
				preShutdown();
			}

			bool GalacticMain::mainLoop() {
				while (!gWantExit) {
					//Do the main loop stuff in here...
				}
				return false;
			}

		};

	};

};