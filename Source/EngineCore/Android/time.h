/**
* Galactic 2D
* Source/EngineCore/Android/time.h
* Defines necessary time related classes for this class.
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

#ifdef GALACTIC_ANDROID

	#ifndef GALACTIC_PLATFORM_ANDROID_PLATFORMTIME
	#define GALACTIC_PLATFORM_ANDROID_PLATFORMTIME

	namespace Galactic {

		namespace Core {

			/*
			PlatformTime: Defines a list of methods and members for calculating system time parameters for Android platforms. For the time being, we should
			 be safe using SysTime for android, however, it's possible that not all android devices support it. Possible inspection topic for later...
			*/
			class PlatformTime : public GenericPlatformTime {

			};

		};

	};

	#endif //GALACTIC_PLATFORM_ANDROID_PLATFORMTIME

#endif //GALACTIC_ANDROID