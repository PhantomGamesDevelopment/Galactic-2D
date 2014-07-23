/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* console.cpp
*
* Defines the central Console unit for the Galactic 2D Engine.
**/

#include "console.h"
#include "logging.h"

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