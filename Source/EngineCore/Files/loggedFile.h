/**
* Galactic 2D
* Source/EngineCore/Files/loggedFile.h
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

#ifndef GALACTIC_INTERNAL_LOGGEDFILE
#define GALACTIC_INTERNAL_LOGGEDFILE

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		LoggedFile: A wrapped version of the File class that inserts logging calls in operations to allow for debugging of file operations.
		*/
		class LoggedFile : public GenericFile {
			public:
				/* Internal Structures */
				/*
				LoggedFile::LoggedVisitor: A basic tool class used to provide a basic set of internal-only functions for viewing files and naviagting through
				directories. This version of the Visitor class has built in Logging support overlayed on the inherited-wide access() function
				*/
				struct LoggedVisitor : public GenericFile::Visitor {
					/* Struct Methods */
					//Constructor
					LoggedVisitor(Visitor &toWrap);
					//Callback function to be triggered when navigating files or directories
					virtual bool access(UTF16 path, bool isDir);

					/* Struct Members */
					//Wrapped Visitor Instance
					Visitor &wrappedVisitor;
				};

				/* Public Class Methods */
				//Return the typename instance of this class, used by the GenericFileManager
				static UTF16 getTypeName();
				//Constructor
				LoggedFile();

				//Initialize this file instance
				virtual bool init(GenericFile *file);

				/* File I/O Class Operations */
				//Open a file for reading
				virtual FileHandle *openForRead(UTF16 filePath);
				//Open a file for writing
				virtual FileHandle *openForWrite(UTF16 filePath, bool append = false, bool canAlsoRead = false);

				/* File Operations */
				//Fetch the typename of this physical instance
				virtual UTF16 fetchPhysicalInstanceTypeName() const;
				//Fetch the PlatformFile object wrapped by this instance at the lower level
				virtual GenericFile *fetchWrappedInstance();
				//Does the specified file exist?
				virtual bool exists(UTF16 filePath);
				//Fetch the size of the target file
				virtual S64 fetchFileSize(UTF16 filePath);
				//Move the file to a new location
				virtual bool moveFile(UTF16 currentPath, UTF16 desiredPath);
				//Copy a file to a new location
				virtual bool copyFile(UTF16 currentPath, UTF16 newLocation);
				//Check if the file is set to read-only
				virtual bool isReadOnly(UTF16 filePath);
				//Attempt to set the read-only status of a file
				virtual bool setReadOnly(UTF16 filePath, bool newStatus);
				//Delete the file
				virtual bool deleteFile(UTF16 filePath);
				//Fetch the last access timestamp of a file
				virtual TimeVars fetchFileAccessTimestamp(UTF16 filePath);
				//Fetch the last modified timestamp of a file
				virtual TimeVars fetchFileLastEditTS(UTF16 filePath);
				//Set the last modified timestamp of a file
				virtual void setFileLastEditTS(UTF16 filePath, TimeVars newTS);

				/* Directory Operations */
				//Create a directory
				virtual bool makeDir(UTF16 path);
				//Delete a directory
				virtual bool deleteDir(UTF16 path);
				//Does this directory exist?
				virtual bool doesDirExist(UTF16 path);

				/* Utility Functions */
				//Explore the contents of a directory, do not visit subdirectories
				virtual bool explore(UTF16 path, GenericFile::Visitor &accessCallback);
				//Recursively explore the contents of a directory, thereby also exploring subdirectories
				virtual bool exploreRecursive(UTF16 path, GenericFile::Visitor &accessCallback);
				//Create a directory tree (allows you to do blah/blah/blah/ and create three directories for example)
				virtual bool makeDirTree(UTF16 path);
				//Copy a directory tree to a new location
				virtual bool copyDirTree(UTF16 srcTree, UTF16 dstTree, bool overwriteExisting);
				//Purge a directory (Delete all files and files contained in subdirectories, then wipe the main directory)
				virtual bool purgeDir(UTF16 path);
				//Should we use this specific file instance?
				virtual bool useInstance(GenericFile *lowerLevel) const;

			private:
				/* Private Class Members */
				//The wrapped GenericFile instance contained at the lower level
				GenericFile *wrappedFile;
		};

	};

};

#endif //GALACTIC_INTERNAL_LOGGEDFILE