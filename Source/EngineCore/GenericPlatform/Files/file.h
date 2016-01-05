/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/Files/file.h
* Defines a generic class instance for working directly with file instances
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

#ifndef GALACTIC_INTERNAL_GENERICPLATFORM_FILE
#define GALACTIC_INTERNAL_GENERICPLATFORM_FILE

namespace Galactic {

	namespace Core {

		/*
		GenericFile: A Platform Independant File/Dir Manipulation Wrapper Object. When actually working with files, you should skip this and use the standard
		 PlatformFile class instead, this simply provides template methods and basic tools to support the Platform version of this class.
		*/
		class GenericFile {
			public:
				/* Internal Structures */
				/*
				GenericFile::Visitor: A basic tool class used to provide a basic set of internal-only functions for viewing files and naviagting through
				 directories
				*/
				struct Visitor {
					//Callback function to be triggered when navigating files or directories
					virtual bool access(UTF16 path, bool isDir) = 0;
				};

				/*
				GenericFile::CopyVisitor: Definition of the Visitor class that allows copying of files and directories
				*/
				struct CopyVisitor : public Visitor {
					/* Struct Members */
					//Root of the source directory
					UTF16 sourceRoot;
					//Root of the destination directory
					UTF16 destinationRoot;
					//Reference to the file instance
					GenericFile &fileInstance;
					//Overwrite existing files?
					bool shouldOverwrite;

					/* Struct Methods */
					//Constructor
					CopyVisitor(GenericFile &fRef, UTF16 src, UTF16 dst, bool overwrite) :
						fileInstance(fRef), sourceRoot(src), destinationRoot(dst), shouldOverwrite(overwrite) { }
					//Explore the file or directory path recusrively (explore subdirectories, if they exist)
					virtual bool access(UTF16 path, bool isDir);
				};

				/*
				GenericFile::PurgeVisitor: Definition of the Visitor class that allows recursive deletion of files and directories
				*/
				struct PurgeVisitor : public Visitor {
					/* Struct Members */
					//Reference to the file instance
					GenericFile &fileInstance;

					/* Struct Methods */
					//Constructor
					PurgeVisitor(GenericFile &fRef) : fileInstance(fRef) { }
					//Explore the file or directory path recusrively (explore subdirectories, if they exist)
					virtual bool access(UTF16 path, bool isDir);
				};

				/*
				GenericFile::RecursiveVisitor: Definition of the Visitor class that allows recursive exploring of files and directories
				*/
				struct RecursiveVisitor : public Visitor {
					/* Struct Members */
					//Reference to the file instance
					GenericFile &fileInstance;
					//Reference to the Visitor instance
					Visitor &visitorInstance;

					/* Struct Methods */
					//Constructor
					RecursiveVisitor(GenericFile &fRef, Visitor &vRef) : fileInstance(fRef), visitorInstance(vRef) { }
					//Explore the file or directory path recusrively (explore subdirectories, if they exist)
					virtual bool access(UTF16 path, bool isDir);
				};

				/* Public Class Methods */
				//Destructor
				virtual ~GenericFile() { }
				//Fetch the engine-wide instance of this class (overriden by PlatformFile)
				static GenericFile &fetchGlobalInstance();
				
				//Initialize this file instance
				virtual bool init(GenericFile *file) = 0;
				//Post-initialization method for additional functioning
				virtual void postInit() { }

				/* File I/O Class Operations */
				//Open a file for reading
				virtual FileHandle *openForRead(UTF16 filePath) = 0;
				//Open a file for writing
				virtual FileHandle *openForWrite(UTF16 filePath, bool append = false, bool canAlsoRead = false) = 0;

				/* File Operations */
				//Fetch the physical file system used by the platform, this is a direct access method to PlatformFile
				static GenericFile &fetchPhysicalInstance();
				//Fetch the typename of this physical instance
				virtual UTF16 fetchPhysicalInstanceTypeName() const;
				//Fetch the PlatformFile object wrapped by this instance at the lower level
				virtual GenericFile *fetchWrappedInstance() = 0;
				//Does the specified file exist?
				virtual bool exists(UTF16 filePath) = 0;
				//Fetch the size of the target file
				virtual S64 fetchFileSize(UTF16 filePath) = 0;
				//Move the file to a new location
				virtual bool moveFile(UTF16 currentPath, UTF16 desiredPath) = 0;
				//Copy a file to a new location
				virtual bool copyFile(UTF16 currentPath, UTF16 newLocation);
				//Check if the file is set to read-only
				virtual bool isReadOnly(UTF16 filePath) = 0;
				//Attempt to set the read-only status of a file
				virtual bool setReadOnly(UTF16 filePath, bool newStatus) = 0;
				//Delete the file
				virtual bool deleteFile(UTF16 filePath) = 0;
				//Fetch the last access timestamp of a file
				virtual TimeVars fetchFileAccessTimestamp(UTF16 filePath) = 0;
				//Fetch the last modified timestamp of a file
				virtual TimeVars fetchFileLastEditTS(UTF16 filePath) = 0;
				//Set the last modified timestamp of a file
				virtual void setFileLastEditTS(UTF16 filePath, TimeVars newTS) = 0;

				/* Directory Operations */
				//Create a directory
				virtual bool makeDir(UTF16 path) = 0;
				//Delete a directory
				virtual bool deleteDir(UTF16 path) = 0;
				//Does this directory exist?
				virtual bool doesDirExist(UTF16 path) = 0;

				/* Utility Functions */
				//Explore the contents of a directory, do not visit subdirectories
				virtual bool explore(UTF16 path, Visitor &accessCallback) = 0;
				//Recursively explore the contents of a directory, thereby also exploring subdirectories
				virtual bool exploreRecursive(UTF16 path, Visitor &accessCallback);
				//Create a directory tree (allows you to do blah/blah/blah/ and create three directories for example)
				virtual bool makeDirTree(UTF16 path);
				//Copy a directory tree to a new location
				virtual bool copyDirTree(UTF16 srcTree, UTF16 dstTree, bool overwriteExisting);
				//Purge a directory (Delete all files and files contained in subdirectories, then wipe the main directory)
				virtual bool purgeDir(UTF16 path);
				//Should we use this specific file instance?
				virtual bool useInstance(GenericFile *lowerLevel) const;
				//Convert a file path to an absolute file path, to be used for the createFileWriter()/createFileReader() methods
				virtual String makeAbsFP(UTF16 filePath);
		};

	};

};

#endif //GALACTIC_INTERNAL_GENERICPLATFORM_FILE