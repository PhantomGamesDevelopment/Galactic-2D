/**
* Galactic 2D
* Source/EngineCore/Files/fileManagerWrapper.h
* Defines a wrapper to the platform file management system
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

#ifndef GALACTIC_INTERNAL_FILEMANAGERWRAPPER
#define GALACTIC_INTERNAL_FILEMANAGERWRAPPER

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		FileManagerWrapper: Platform independant template class to the platform based file management classes. You shouldn't directly use this class instance,
		 however in the event of generic platform based operations this could be a source of generating a call log.
		*/
		class FileManagerWrapper {
			public:
				/* Public Class Methods */
				//Fetch the singleton instance of this object
				static FileManagerWrapper &fetchInstance();
				
				/* File IO Object Methods */
				//Create a file reading instance
				virtual Stream* createFileReader(UTF16 filePath, U32 flags = 0) = 0;
				//Create a file writing instance
				virtual Stream* createFileWriter(UTF16 filePath, U32 flags = 0) = 0;
				
				/* Basic File Operations */
				//Does the specified file exist?
				virtual bool fileExists(UTF16 filePath) = 0;
				//Fetch the size of the specified file
				virtual S64 fetchFileSize(UTF16 filePath) = 0;
				//Move a file to a new location
				virtual bool moveFile(UTF16 currentPath, UTF16 desiredPath, bool replaceExisting = true, bool moveIfReadOnly = false, bool atr = true, bool retryOnError = false) = 0;
				//Copy a file to another location
				virtual bool copyFile(UTF16 currentPath, UTF16 desiredPath, bool replaceExisting = true, bool copyIfReadOnly = false, bool atr = true, fileCopyProgress *prog = NULL) = 0;
				//Check if a file is read-only
				virtual bool isReadOnly(UTF16 filePath) = 0;
				//Delete a file
				virtual bool deleteFile(UTF16 filePath, bool mustExist = false, bool deleteIfReadOnly = false, bool quietDelete = false) = 0;
				//Fetch the age of a file (measured in seconds)
				virtual F64 fetchFileAge(UTF16 filePath) = 0;
				//Fetch the timestamp of a file
				virtual TimeVars fetchFileTimestamp(UTF16 filePath) = 0;
				//Fetch the last modified timestamp of a file
				virtual TimeVars fetchFileLastEditTS(UTF16 filePath) = 0;
				//Set the last modified timestamp of a file
				virtual bool setFileLastEditTS(UTF16 filePath, TimeVars newTS) = 0;

				/* Directory Operations */
				//Create a directory
				virtual bool makeDir(UTF16 path, bool tree = false) = 0;
				//Delete a directory
				virtual bool deleteDir(UTF16 path, bool mustExist = false, bool tree = false) = 0;
				//Does this directory exist?
				virtual bool doesDirExist(UTF16 path) = 0;
				 
				/* File Path Tools */
				//Convert a file path to a relative file path
				virtual String makeRelative(UTF16 filePath) = 0;
				//Convert a file path to an absolute file path, to be used for the createFileWriter()/createFileReader() methods
				virtual String makeAbsFP(UTF16 filePath) = 0;

				/* Finding Tools */
				//Locate Files & Directories
				virtual void find(UTF16 target, DynArray<String> &result, bool findFiles = true, bool findDirs = true) = 0;
				//Locate Files & Directories Recurviely
				virtual void findRecursive(UTF16 target, UTF16 startDir, DynArray<String> &result, bool findFiles = true, bool findDirs = true, bool clearNames = true) = 0;

			protected:
				/* Protected Class Methods */
				//Default Constructor, Protected for inheritance purposes
				FileManagerWrapper() { }
		};

	};

};

#endif //GALACTIC_INTERNAL_FILEMANAGERWRAPPER