/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* galacticMain.h
*
* Defines the Galactic Engine Main Functions
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