/**
* Galactic 2D
* GLCore.h
* The wrapper header which is initialized from the engine core to load in all of the correct OGL libs
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

#ifndef GALACTIC_OPENGL_GLCORE
#define GALACTIC_OPENGL_GLCORE

//Load Engine Dependancies
#include "../EngineCore/engineCore.h"

//Load Platform Specific Functioning
#if GALACTIC_ANDROID

#elif GALACTIC_IPHONE

#elif GALACTIC_LINUX

#elif GALACTIC_MAC

#elif GALACTIC_WINDOWS

#endif

namespace Galactic {

	namespace OpenGL {



	};

};

#endif //GALACTIC_OPENGL_GLCORE