/**
* Galactic 2D
* Source/EngineCore/Files/loggedFile.cpp
* Defines an implementation of the File instance with logging calls for debug purposes
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

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		UTF16 LoggedFile::getTypeName() {
			return "LoggedFile";
		}

		LoggedFile::LoggedFile() : wrappedFile(NULL) {

		}

		bool LoggedFile::init(GenericFile *file) {
			if (file == NULL) {
				GC_Error("LoggedFile::init(): Failed to initalize module, no File instance to wrap");
				return false;
			}
			wrappedFile = file;
			return FBOOL(wrappedFile);
		}

		FileHandle *LoggedFile::openForRead(UTF16 filePath) {
			FILE_LOGWRITE("LoggedFile", "call openForRead(%s)", filePath);
			F64 start = PlatformTime::fetchSeconds();
			FileHandle *result = wrappedFile->openForRead(filePath);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "openForRead(%s) done: return %llx, exec. time %fms", filePath, U64(result), timeSpent);
			return (result != NULL) ? (new LoggedFileHandle(result, filePath)) : NULL;
		}

		FileHandle *LoggedFile::openForWrite(UTF16 filePath, bool append, bool canAlsoRead) {
			FILE_LOGWRITE("LoggedFile", "call openForWrite(%s, %d, %d)", filePath, append, canAlsoRead);
			F64 start = PlatformTime::fetchSeconds();
			FileHandle *result = wrappedFile->openForWrite(filePath, append, canAlsoRead);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "openForWrite(%s, %d, %d) done: return %llx, exec. time %fms", filePath, append, canAlsoRead, U64(result), timeSpent);
			return (result != NULL) ? (new LoggedFileHandle(result, filePath)) : NULL;
		}

		UTF16 LoggedFile::fetchPhysicalInstanceTypeName() const {
			return LoggedFile::getTypeName();
		}

		GenericFile *LoggedFile::fetchWrappedInstance() {
			return wrappedFile;
		}

	};

};