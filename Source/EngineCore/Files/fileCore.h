/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* fileCore.h
*
* Defines the FileCore class which serves as a gateway between the individual fileRef classes and the functionality desired by the calling
* methods.
**/

#ifndef GALACTIC_INTERNAL_FILES_FILECORE
#define GALACTIC_INTERNAL_FILES_FILECORE

#include "fileRef.h" //< Including fileRef.h also includes FilePath & FileBase.

namespace Galactic {

	namespace Core {

		namespace Files {

			/*
			FileCore: A collection of FileBase objects (both direct and inherited) that are used to work directly with Files and Directories
			in the Galactic 2D engine. This is sort of a "Gateway" class between the engine's calls and the operations of files themselves.
			*/
			class FileCore : public FileBase {
				public:
					/* Public Class Properties */
					//MapMode: Used by the map function to declare if the path is to be mapped to or from.
					enum MapMode {
						//Map the path directly to the specified file / directory (absolute)
						MapPathTo,
						//Map the path from the specified file / directory (relative)
						MapPathFrom,
					};
					/* Public Class Methods */
					//Default Constructor
					FileCore();
					//Destructor, Virtual for platform access
					virtual ~FileCore();
					//Is the current path read only?
					bool readOnly();
					//Resolve a path to a File
					virtual FileRef_Ref resolvePath(pathRef p) = 0;
					//Create a file/directory, given the path and access mode specified.
					virtual FileRef_Ref createInstance(pathRef p, FileRef::FileMode m) = 0;
					//Map a file path to or from the specified path.
					virtual FilePath mapPath(pathRef p, MapMode map = MapPathTo) = 0;
					//Remove the specified file or directory.
					virtual bool remove(pathRef p) = 0;
					//Rename the specified file or directory to something else.
					virtual bool rename(pathRef trgPath, pathRef newName) = 0;

				protected:
					/* Protected Class Fields */
					//Is the accessed file a read only file?
					bool isReadOnly;
			};

			/* Typedef out Weak/Strong references to FileCore to be used by the other classes */
			//Weak Reference Pointer to FileCore
			typedef WeakReferencePtr<FileCore> FileCorePtr;
			//Strong Reference Pointer to FileCore
			typedef StrongReferencePtr<FileCore> FileCore_Ref;

		};

	};

};

#endif //GALACTIC_INTERNAL_FILES_FILECORE