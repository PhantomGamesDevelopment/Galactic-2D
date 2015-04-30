/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/window.h
* Standard platform window handler. Mainly templatized function decs for Galactic Supported Platforms
* (C) 2014-2015 Phantom Games Development - All Rights Reserved
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

#ifndef GALACTIC_PLATFORM_GENERIC_WINDOW
#define GALACTIC_PLATFORM_GENERIC_WINDOW

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		WindowMode: Defines a list of standard modes the window could be in
		*/
		enum WindowMode {
			//Fullscreen: The window is in Standard OS style Fullscreen mode (Contains Border)
			Fullscreen,
			//AllScreen: Non-Standard Fullscreen mode (No Outer Border)
			AllScreen,
			//Windowed: Standard OS style Windowed mode
			Windowed,
		};

		/*
		WindowProperties: Defines a list of parameters and settings used by a standard window instance
		*/
		class WindowProperties {
			public:
				/* Public Class Members */

		};

		/*
		Window: Defines a standard platform independant window wrapper class instance to be used by the engine.
		*/
		class Window {
			public:
				/* Public Class Methods */
		};

	};

};

#endif //GALACTIC_PLATFORM_GENERIC_WINDOW