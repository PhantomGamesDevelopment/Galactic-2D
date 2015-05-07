/**
* Galactic 2D
* Source/Console/logging.h
* Defines the engine's data logging system
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

#ifndef GALACTIC_CONSOLE_LOGGING
#define GALACTIC_CONSOLE_LOGGING

namespace Galactic {

	namespace Console {

		/*
		LogEntry: Defines a sub-class containing a storage space for a String and a S32 value. This is used by the Console Logger as a method to 
		 store messages to the console.
		*/
		class LogEntry {
			public:
				UTF16 message;
				S32 level;

				LogEntry() : message(NULL), level(0) { }
				LogEntry(UTF16 m, S32 l) {
					message = m;
					level = l;
				}
		};

		/*
		Logger: Defines a class for taking down messages and storing them to a application based String buffer. These messages may be displayed
		 by an in-game GUI or be written to a file for referencing on in-engine messages.
		*/
		class Logger {
			public:
				//Default Constructor
				Logger();
				//Default Destructor
				~Logger();

				//Standard print(), uses Normal logging level
				void print(UTF16 s);
				//Standard warn(), uses Warning logging level
				void warn(UTF16 s);
				//Standard error(), uses Error logging level
				void error(UTF16 s);
				//Standard cerr(), uses Critial logging level
				void cerr(UTF16 s);
				//dumpToFile(): places all console output in a file.
				void dumpToFile(::Galactic::Core::String path);
		
			private:
				//Forward Dec. For logLevel
				enum logLevel;

				/* Private Class Functions */
				//Generic Add Method (Add a message to the buffer)
				void addMessage(S32 l, UTF16 message);

				/* Private Class Members */
				//Defines a level the message is stored in
				enum logLevel {
					//0 - Normal Printed Message, Used for basic methods such as print()
					Normal = 0,
					//1 - Console Warning, Used for non-critical errors or function warns
					Warning = 1,
					//2 - Console Error, Used to alert the user of errors
					Error = 2,
					//3 - Critical Error, Used to alert the user of potential AV Crashes due to read/write errors
					Critical = 3,
				};

				//The buffer of messages in the console
				::Galactic::Core::DynArray<LogEntry> consoleMB;
		};

	};

};

#endif //GALACTIC_CONSOLE_LOGGING