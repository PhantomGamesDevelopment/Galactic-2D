/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* galacticMain.cpp
*
* Defines the Galactic Engine Main Functions
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