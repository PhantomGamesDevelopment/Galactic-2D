/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* files.h
*
* This is a loading file. Include this file in a source file to load up all of the Galactic::Internal::Files classes and methods
**/

#ifndef GALACTIC_INTERNAL_FILES_FILES
#define GALACTIC_INTERNAL_FILES_FILES

#include "crc.h"
#include "fileSystem.h"

//Open full access to the Files namespace
using namespace Galactic::Core::Files;

//Global FileSystem
static FileSystem _gFileSystem;

namespace Galactic {

	namespace Core {

		/*
		Files: This is the Files namespace, it creates a set of cross-platform file methods and declarations
		 to make it easy to perform your basic file I/O operations as well as a few extra definitions. This 
		 module however doesn't directly handle things that are platform specific such as creating the files
		 and directories themselves, you'll need to find the respective platformFile.h/.cpp in the 
		 Galactic::Platform namespace.
		*/
		namespace Files {
			/*
			These functions are granted as a direct part of the Files namespace and are opened up
			 by including this file. Basically it merges together all of the C++ files in this folder
			 and packs together the functioning into one easy to use module.
			*/

			//Create a file at the specified path
			File_Ref createFile(pathRef p) {
				_gFileSystem.createFile(p);
			}

			//Create a directory at the specified path
			Directory_Ref createDirectory(pathRef p) {
				_gFileSystem.createDirectory(p);
			}

			//Create a path to the specified location
			bool createPath(pathRef p) {
				return _gFileSystem.createPath(p);
			}

			//Check if the specified path points to a file
			bool isFile(pathRef p) {
				return _gFileSystem.isFile(p);
			}

			//Check if the specified path points to a directory
			bool isDir(pathRef p) {
				return _gFileSystem.isDir(p);
			}

			//Check if the specified path is read only
			bool isReadOnly(pathRef p) {
				return _gFileSystem.isReadOnly(p);
			}

			//Fetch the file core object for the given path
			FileCore_Ref GetFileCore(pathRef p) {
				return _gFileSystem.getFileCore(p);
			}

			//Fetch the fileRef object for the given path
			FileRef_Ref GetFileRef(pathRef p) {
				return _gFileSystem.getFileRef(p);
			}

			//Get the path to the given file core object
			bool getFileCorePath(pathRef in, FilePath &out) {
				FileCore_Ref fcRef = GetFileCore(in);
				if (!fcRef.null()) {
					out = fcRef->mapPath(in, FileCore::MapPathTo);
					return true;
				}
				return false;
			}

			//Open a file for other functioning
			File_Ref openFile(pathRef p, File::FileAccessMode mode) {
				return _gFileSystem.openFile(p, mode);
			}

			//Open a directory for other functioning
			Directory_Ref openDir(pathRef p) {
				return _gFileSystem.openDir(p);
			}

			//Read a file's contents into a buffer
			bool readFile(pathRef p, anyRef buffer, U32 &size, bool nullTerminated) {
				File_Ref f = openFile(p, File::Read);
				buffer = NULL;
				size = 0;
				//Check if the file opened.
				if (f.null()) {
					return false;
				}
				//Alright, proceed with the read in.
				size = (U32)f->getSize();
				if (size == 0) {
					return true;
				}
				//Read it in.
				U64 amountRead = 0;
				if (nullTerminated) {
					buffer = new C8[size + 1];
					amountRead = f->read(buffer, size);
					static_cast<UTF8>(buffer)[size] = '\0';
				}
				else {
					buffer = new C8[size];
					amountRead = f->read(buffer, size);
				}
				//Test for a read error...
				if (amountRead != size) {
					SendToPitsOfHell(static_cast<UTF8>(buffer));
					buffer = NULL;
					size = 0;
					return false;
				}
				//Done!
				return true;
			}

			//Rename a file
			bool rename(pathRef trgFile, pathRef newName) {
				return _gFileSystem.rename(trgFile, newName);
			}

			//Remove a file / dir
			bool remove(pathRef trg) {
				return _gFileSystem.remove(trg);
			}

			//Get the attributes of a file /dir
			bool getAttributes(pathRef p, FileRef::FileAttributes *attr) {
				return _gFileSystem.getAttributes(p, attr);
			}

			//Return the current working directory
			pathRef getCWD() {
				return _gFileSystem.getCWD();
			}

			//Set the current working directory
			bool setCWD(pathRef p) {
				return _gFileSystem.setCWD(p);
			}

			//Get the amount of FCRef objects stored in FileSystem
			S32 getSysRefSize() {
				return _gFileSystem.getSysRefSize();
			}

			//Fetch the root of the path stored in the FCRef at the given index.
			String getSysRefRoot(S32 index) {
				return _gFileSystem.getSysRefRoot(index);
			}

			//Fetch the path of the FCRef stored at the given index.
			String getSysRefPath(S32 index) {
				return _gFileSystem.getSysRefPath(index);
			}

			//Add a FCRef to the file system
			bool addRef(String root, FileCore_Ref coreRef) {
				return _gFileSystem.addRef(root, coreRef);
			}

			//Redefinition of the above, uses pathRef
			bool addRef(String root, pathRef p) {
				return _gFileSystem.addRef(root, p);
			}

			//Remove a FCRef from the file system
			FileCore_Ref killRef(String root) {
				return _gFileSystem.killRef(root);
			}

			//Redefinition of the above, uses the direct FC object.
			bool killRef(FileCore_Ref fcRef) {
				return _gFileSystem.killRef(fcRef);
			}

		};

	};

};

#endif //GALACTIC_INTERNAL_FILES_FILES