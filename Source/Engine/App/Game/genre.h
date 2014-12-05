/**
* Galactic 2D
* Source/Engine/App/Game/genre.h
* Defines settings and options for individual G2D/G3D Applications
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