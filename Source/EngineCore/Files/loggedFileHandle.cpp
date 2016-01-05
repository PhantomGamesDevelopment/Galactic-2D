/**
* Galactic 2D
* Source/EngineCore/Files/loggedFileHandle.cpp
* Defines an implementation of the FileHandle instance with logging calls for debug purposes
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

		LoggedFileHandle::LoggedFileHandle(FileHandle *toWrap, UTF16 filePath) : wrappedHandle(toWrap), fileName(filePath) {
		
		}

		S64 LoggedFileHandle::fetchSize() {
			FILE_LOGWRITE("LoggedFileHandle", "call fetchSize()");
			F64 start = PlatformTime::fetchSeconds();
			S64 result = wrappedHandle->fetchSize();
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFileHandle", "fetchSize() done: return %lld, exec. time %fms", result, timeSpent);
			return result;
		}

		S64 LoggedFileHandle::tell() {
			FILE_LOGWRITE("LoggedFileHandle", "call tell()");
			F64 start = PlatformTime::fetchSeconds();
			S64 result = wrappedHandle->tell();
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFileHandle", "tell() done: return %lld, exec. time %fms", result, timeSpent);
			return result;
		}

		bool LoggedFileHandle::seek(S64 newPos, bool fromEnd) {
			FILE_LOGWRITE("LoggedFileHandle", "call seek(%lld, %d)", newPos, fromEnd);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedHandle->seek(newPos, fromEnd);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFileHandle", "seek(%lld, %b) done: return %d, exec. time %fms", newPos, fromEnd, result, timeSpent);
			return result;
		}

		bool LoggedFileHandle::write(const UTX8 src, S64 bitsToWrite) {
			FILE_LOGWRITE("LoggedFileHandle", "call write(%llx, %lld)", src, bitsToWrite);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedHandle->write(src, bitsToWrite);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFileHandle", "write(%llx, %lld) done: return %d, exec. time %fms", src, bitsToWrite, result, timeSpent);
			return result;
		}

		bool LoggedFileHandle::read(UTX8 dst, S64 bitsToRead) {
			FILE_LOGWRITE("LoggedFileHandle", "call read(%llx, %lld)", dst, bitsToRead);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedHandle->read(dst, bitsToRead);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFileHandle", "read(%llx, %lld) done: return %d, exec. time %fms", dst, bitsToRead, result, timeSpent);
			return result;
		}

	};

};