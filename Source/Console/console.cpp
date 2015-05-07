/**
* Galactic 2D
* Source/Console/console.cpp
* Defines the connection point between the engine and the scripting language for the engine
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

#include "../EngineCore/engineCore.h"

namespace Galactic {

	namespace Console {

		void init() {
			//Create a managed singleton of the console logging system
			managedSingleton<Logger>::createInstance();
			//Push a message to validate initialization
			print("Galactic 2D Engine: V.%i, By: Phantom Games Development", GALACTIC_VERSION_NUMBER);
			print("Galactic 2D: Console Subsystem Initialized...");
		}

		void destroy() {
			managedSingleton<Logger>::destroyInstance();
		}

		void print(UTF16 format, ...) {
			//Fetch the args
			va_list args;
			_crt_va_start(args, format);
			String result = String::ToStr(format, args);
			_crt_va_end(args);		
			//Fork off to Logger
			managedSingleton<Logger>::instance()->print(result.c_str());
		}

		void warn(UTF16 format, ...) {
			//Fetch the args
			va_list args;
			_crt_va_start(args, format);
			String result = String::ToStr(format, args);
			_crt_va_end(args);		
			//Fork off to Logger
			managedSingleton<Logger>::instance()->warn(result.c_str());
		}

		void error(UTF16 format, ...) {
			//Fetch the args
			va_list args;
			_crt_va_start(args, format);
			String result = String::ToStr(format, args);
			_crt_va_end(args);		
			//Fork off to Logger
			managedSingleton<Logger>::instance()->error(result.c_str());
		}

		void cerr(UTF16 format, ...) {
			//Fetch the args
			va_list args;
			_crt_va_start(args, format);
			String result = String::ToStr(format, args);
			_crt_va_end(args);		
			//Fork off to Logger
			managedSingleton<Logger>::instance()->cerr(result.c_str());
		}

	};

};