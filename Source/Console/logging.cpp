/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* logging.cpp
*
* Defines the log system for engine messages.
**/

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