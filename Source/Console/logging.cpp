/**
* Galactic 2D
* Source/Console/logging.cpp
* Defines the engine's data logging system
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

#include "../EngineCore/engineCore.h"
#include "logging.h"

namespace Galactic {

	namespace Console {

		Logger::Logger() {
		
		}

		Logger::~Logger() {
		
		}

		void Logger::print(UTF16 s) {
			addMessage(Normal, s);
		}

		void Logger::warn(UTF16 s) {
			addMessage(Warning, s);
		}

		void Logger::error(UTF16 s) {
			addMessage(Error, s);
		}

		void Logger::cerr(UTF16 s) {
			addMessage(Critical, s);
		}

		void Logger::dumpToFile(::Galactic::Core::String path) {
			//Stub.. Insert Code Later.
		}

		void Logger::addMessage(S32 l, UTF16 message) {
			LogEntry entry(message, l);

			consoleMB.pushToBack(entry);
		}

	};

};