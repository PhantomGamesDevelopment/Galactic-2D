/**
* Galactic 2D
* Source/EngineCore/Windows/platformOperations.h
* Additional platform functions that are kept outside of the function lib for compatibility on Windows platforms
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

#ifdef GALACTIC_WINDOWS

	#ifndef GALACTIC_PLATFORM_WINDOWS_PLATFORMOPERATIONS
	#define GALACTIC_PLATFORM_WINDOWS_PLATFORMOPERATIONS

	namespace Galactic {

		namespace Core {

			/*
			PlatformOperations: Declares a set of platform specific methods and operations. These are mainly used to gate each platform into the cross
			compatibility nature of the engine. This is the definition for Windows platforms
			*/
			class PlatformOperations : public GenericPlatformOperations {

			};

		};

	};

	#endif //GALACTIC_PLATFORM_WINDOWS_PLATFORMOPERATIONS

#endif //GALACTIC_WINDOWS