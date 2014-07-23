/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* genre.h
*
* Sort of a Semi-Control file in which a ton of mathematical properties base from. There is nothing "specific" stored
*  in this file, this is mainly a engine flag class that is used in many many different engine locations to do things.
**/

#ifndef GALACTIC_ENGINE_GAME_GENRE
#define GALACTIC_ENGINE_GAME_GENRE

#include "../../../EngineCore/engineCore.h"

namespace Galactic {

	namespace Engine {
	
		namespace Game {
		
			class Genre {
				public:
					enum Types {
						/* Define Top-Down specifics, This assumes a coordinate plane where X = West & East, Y = North & South */
						TOPDOWN = 0,
						/* Define Side-Scroller specifics, This assumes a coordinate plane where X = Left & Right, Y = Up & Down */
						SIDESCROLLER = 1,
						/* Define Isometric specifics, This basically works like Side-Scroller, with a adjusted camera angle to "fake" 3D effects */
						ISOMETRIC = 2,
					};

					Genre() : gameGenre(TOPDOWN) { }

					void setGenre(U32 Type) { 
						gameGenre = Type;
					}

					U32 getGenre() const { return gameGenre; }

					static UTF16 getInstanceName() {
						return "Genre";
					}

				private:
					U32 gameGenre;

			};
		
		};
	
	};

};

#endif //GALACTIC_ENGINE_GAME_GENRE