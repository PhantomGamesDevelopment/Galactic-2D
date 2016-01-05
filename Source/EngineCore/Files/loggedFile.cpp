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

		LoggedFile::LoggedVisitor::LoggedVisitor(Visitor &toWrap) : wrappedVisitor(toWrap) {

		}

		bool LoggedFile::LoggedVisitor::access(UTF16 path, bool isDir) {
			FILE_LOGWRITE("LoggedVisitor", "call access(%s, %d)", path, isDir);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedVisitor.access(path, isDir);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedVisitor", "access(%s, %d) done: return %d, exec. time %fms", path, isDir, result, timeSpent);
			return result;
		}

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

		bool LoggedFile::exists(UTF16 filePath) {
			FILE_LOGWRITE("LoggedFile", "call exists(%s)", filePath);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedFile->exists(filePath);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "exists(%s) done: return %d, exec. time %fms", filePath, result, timeSpent);
			return result;
		}

		S64 LoggedFile::fetchFileSize(UTF16 filePath) {
			FILE_LOGWRITE("LoggedFile", "call fetchFileSize(%s)", filePath);
			F64 start = PlatformTime::fetchSeconds();
			S64 result = wrappedFile->fetchFileSize(filePath);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "fetchFileSize(%s) done: return %lld, exec. time %fms", filePath, result, timeSpent);
			return result;
		}

		bool LoggedFile::moveFile(UTF16 currentPath, UTF16 desiredPath) {
			FILE_LOGWRITE("LoggedFile", "call moveFile(%s, %s)", currentPath, desiredPath);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedFile->moveFile(currentPath, desiredPath);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "moveFile(%s, %s) done: return %d, exec. time %fms", currentPath, desiredPath, result, timeSpent);
			return result;
		}

		bool LoggedFile::copyFile(UTF16 currentPath, UTF16 newLocation) {
			FILE_LOGWRITE("LoggedFile", "call copyFile(%s, %s)", currentPath, newLocation);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedFile->copyFile(currentPath, newLocation);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "copyFile(%s, %s) done: return %d, exec. time %fms", currentPath, newLocation, result, timeSpent);
			return result;
		}

		bool LoggedFile::isReadOnly(UTF16 filePath) {
			FILE_LOGWRITE("LoggedFile", "call isReadOnly(%s)", filePath);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedFile->isReadOnly(filePath);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "isReadOnly(%s) done: return %d, exec. time %fms", filePath, result, timeSpent);
			return result;
		}

		bool LoggedFile::setReadOnly(UTF16 filePath, bool newStatus) {
			FILE_LOGWRITE("LoggedFile", "call setReadOnly(%s, %d)", filePath, newStatus);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedFile->setReadOnly(filePath, newStatus);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "setReadOnly(%s, %d) done: return %d, exec. time %fms", filePath, newStatus, result, timeSpent);
			return result;
		}

		bool LoggedFile::deleteFile(UTF16 filePath) {
			FILE_LOGWRITE("LoggedFile", "call deleteFile(%s)", filePath);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedFile->deleteFile(filePath);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "deleteFile(%s) done: return %d, exec. time %fms", filePath, result, timeSpent);
			return result;
		}

		TimeVars LoggedFile::fetchFileAccessTimestamp(UTF16 filePath) {
			FILE_LOGWRITE("LoggedFile", "call fetchFileAccessTimestamp(%s)", filePath);
			F64 start = PlatformTime::fetchSeconds();
			TimeVars result = wrappedFile->fetchFileAccessTimestamp(filePath);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "fetchFileAccessTimestamp(%s) done: return %llx, exec. time %fms", filePath, result.fetchTickCount(), timeSpent);
			return result;
		}

		TimeVars LoggedFile::fetchFileLastEditTS(UTF16 filePath) {
			FILE_LOGWRITE("LoggedFile", "call fetchFileLastEditTS(%s)", filePath);
			F64 start = PlatformTime::fetchSeconds();
			TimeVars result = wrappedFile->fetchFileLastEditTS(filePath);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "fetchFileLastEditTS(%s) done: return %llx, exec. time %fms", filePath, result.fetchTickCount(), timeSpent);
			return result;
		}

		void LoggedFile::setFileLastEditTS(UTF16 filePath, TimeVars newTS) {
			FILE_LOGWRITE("LoggedFile", "call setFileLastEditTS(%s, %llx)", filePath, newTS.fetchTickCount());
			F64 start = PlatformTime::fetchSeconds();
			wrappedFile->setFileLastEditTS(filePath, newTS);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "setFileLastEditTS(%s, %llx) done: return %llx, exec. time %fms", filePath, newTS.fetchTickCount(), timeSpent);
		}

		bool LoggedFile::makeDir(UTF16 filePath) {
			FILE_LOGWRITE("LoggedFile", "call makeDir(%s)", filePath);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedFile->makeDir(filePath);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "makeDir(%s) done: return %d, exec. time %fms", filePath, result, timeSpent);
			return result;
		}

		bool LoggedFile::deleteDir(UTF16 filePath) {
			FILE_LOGWRITE("LoggedFile", "call deleteDir(%s)", filePath);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedFile->deleteDir(filePath);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "deleteDir(%s) done: return %d, exec. time %fms", filePath, result, timeSpent);
			return result;
		}

		bool LoggedFile::doesDirExist(UTF16 filePath) {
			FILE_LOGWRITE("LoggedFile", "call doesDirExist(%s)", filePath);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedFile->doesDirExist(filePath);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "doesDirExist(%s) done: return %d, exec. time %fms", filePath, result, timeSpent);
			return result;
		}

		bool LoggedFile::explore(UTF16 path, GenericFile::Visitor &accessCallback) {
			FILE_LOGWRITE("LoggedFile", "call explore(%s, VISITORINSTANCE)", path);
			F64 start = PlatformTime::fetchSeconds();
			LoggedVisitor v(accessCallback);
			bool result = wrappedFile->explore(path, v);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "explore(%s, VISITORINSTANCE) done: return %d, exec. time %fms", path, result, timeSpent);
			return result;
		}

		bool LoggedFile::exploreRecursive(UTF16 path, GenericFile::Visitor &accessCallback) {
			FILE_LOGWRITE("LoggedFile", "call exploreRecursive(%s, VISITORINSTANCE)", path);
			F64 start = PlatformTime::fetchSeconds();
			LoggedVisitor v(accessCallback);
			bool result = wrappedFile->exploreRecursive(path, v);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "exploreRecursive(%s, VISITORINSTANCE) done: return %d, exec. time %fms", path, result, timeSpent);
			return result;
		}

		bool LoggedFile::makeDirTree(UTF16 path) {
			FILE_LOGWRITE("LoggedFile", "call makeDirTree(%s)", path);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedFile->makeDirTree(path);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "makeDirTree(%s) done: return %d, exec. time %fms", path, result, timeSpent);
			return result;
		}

		bool LoggedFile::copyDirTree(UTF16 srcTree, UTF16 dstTree, bool overwriteExisting) {
			FILE_LOGWRITE("LoggedFile", "call copyDirTree(%s, %s, %d)", srcTree, dstTree, overwriteExisting);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedFile->copyDirTree(srcTree, dstTree, overwriteExisting);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "copyDirTree(%s, %d, %d) done: return %d, exec. time %fms", srcTree, dstTree, overwriteExisting, result, timeSpent);
			return result;
		}

		bool LoggedFile::purgeDir(UTF16 path) {
			FILE_LOGWRITE("LoggedFile", "call purgeDir(%s)", path);
			F64 start = PlatformTime::fetchSeconds();
			bool result = wrappedFile->purgeDir(path);
			F32 timeSpent = 1000.0f * (F32(PlatformTime::fetchSeconds() - start));
			FILE_LOGWRITE("LoggedFile", "purgeDir(%s) done: return %d, exec. time %fms", path, result, timeSpent);
			return result;
		}

		bool LoggedFile::useInstance(GenericFile *lowerLevel) const {
			return ProcessCommandLine::fetchInstance().hasParam("FileLoggingOn");
		}

	};

};