/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* fileSystem.h
*
* Defines the FileSystem class which combines the operations of the FileCore class into a direct operation parsing class. This class actually
* performs the file operations and it's virtual methods are overriden by the individual platforms to handle cross-platform file ops.
**/

#ifndef GALACTIC_INTERNAL_FILES_FILESYSTEM
#define GALACTIC_INTERNAL_FILES_FILESYSTEM

#include "file.h"
#include "directory.h"
#include "fileCore.h" 

namespace Galactic {

	namespace Core {

		namespace Files {

			/*
			FileSystem: A collection of functions and methods to handle file operations for the Engine.
			*/
			class FileSystem {
				public:
					/* Public Class Methods */
					//Destructor
					virtual ~FileSystem();
					//Set the current working directory
					bool setCWD(pathRef p);
					//Get the current working directory
					pathRef getCWD() const;
					//Detect if the given path is a File
					bool isFile(pathRef p);
					//Detect if the given path is a Directory
					bool isDir(pathRef p, FileCore_Ref fcRef = PointerModes::Null);
					//Detect if the file in question is read-only
					bool isReadOnly(pathRef p);
					//Fetch the number of entries in sysRef
					S32 getSysRefSize() const;
					//Get the root of the specified FCRef Object
					String getSysRefRoot(S32 index) const;
					//Get the path of the specified FCRef Object
					String getSysRefPath(S32 index) const;
					//Fetch the fileCore Object for the specified path
					FileCore_Ref getFileCore(pathRef p);
					//Fetch the fileRef object for the specified path
					FileRef_Ref getFileRef(pathRef p);
					//Fetch the file attributes for a specified path
					bool getAttributes(pathRef p, FileRef::FileAttributes *attr);
					//Add a FCRef to the sysRef list
					virtual bool addRef(String root, FileCore_Ref coreRef);
					//Redefinition, uses FilePath instead of FileCore_Ref
					virtual bool addRef(String root, pathRef p);
					//Remove a FCRef from the sysRef list
					virtual FileCore_Ref killRef(String root);
					//Redefinition, uses a FileCore_Ref to remove.
					virtual bool killRef(FileCore_Ref coreRef);
					//Create a file at the specified path
					File_Ref createFile(pathRef p);
					//Create a directory with the given path
					Directory_Ref createDirectory(pathRef p, FileCore_Ref fcRef = PointerModes::Null);
					//Create a generic path
					virtual bool createPath(pathRef p);
					//Open the specified file given an access mode
					File_Ref openFile(pathRef p, File::FileAccessMode mode);
					//Open the specified directory
					Directory_Ref openDir(pathRef p);
					//Rename a file
					bool rename(pathRef trgPath, pathRef newName);
					//Remove a file/directory
					bool remove(pathRef trgPath);

				protected:
					/* Protected Class Members */
					//FCRef: A reference used by FileSystem to store which FileCore owns which file.
					struct FCRef {
						//The root of the file being handled.
						String fRoot;
						//The path of the file being handled.
						String fPath;
						//The reference pointer to the individual object which stores this file/dir.
						FileCore_Ref coreRef;
					};

					//Dynamic Array of stored FCRef objects
					DynArray<FCRef> fileSysRef;
					//Current working directory
					FilePath cwd;

					/* Protected Class Methods */
					//Obtain the FCRef object from the given path, return NULL is not found
					virtual FileCore_Ref __fetchFromFCRef(pathRef p) const;
					//Remove an FCRef object from the DynArray based on it's root.
					virtual FileCore_Ref __removeFromFCRef(String r);
					//Adjust a file path based on the current working directory
					FilePath __adjustToCWD(pathRef p);
			};

		};

	};

};

#endif //GALACTIC_INTERNAL_FILES_FILESYSTEM