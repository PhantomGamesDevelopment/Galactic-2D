/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* directory.h
*
* Defines the Directory class which is the core class object instance for every directory Specific operation used in the Galactic Engine.
**/

#ifndef GALACTIC_INTERNAL_FILES_DIRECTORY
#define GALACTIC_INTERNAL_FILES_DIRECTORY

#include "fileRef.h"

namespace Galactic {

	namespace Core {

		namespace Files {

			/*
			Directory: Defines a set of methods and operations that can be used to work with Directories in the Galactic Engine.
			*/
			class Directory : public FileRef {
				public:
					/* Public Class Methods */
					//Default Constructor
					Directory();
					//Destructor, Virtual for platform overwrites
					virtual ~Directory();
					//Open a directory
					virtual bool openDirectory() = 0;
					//Close a directory
					virtual bool closeDirectory() = 0;
					//Read in a directory with the specified attributes
					virtual bool readDirectory(FileAttributes *attr) = 0;
			};

			/* Typedef out Weak/Strong references to File to be used by the other classes */
			//Weak Reference Pointer to File
			typedef WeakReferencePtr<Directory> DirectoryPtr;
			//Strong Reference Pointer to File
			typedef StrongReferencePtr<Directory> Directory_Ref;

		};

	};

};

#endif //GALACTIC_INTERNAL_FILES_DIRECTORY