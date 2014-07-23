/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* file.h
*
* Defines the File class which is the core class object instance for every File Specific operation used in the Galactic Engine.
**/

#ifndef GALACTIC_INTERNAL_FILES_FILE
#define GALACTIC_INTERNAL_FILES_FILE

#include "fileRef.h"

namespace Galactic {

	namespace Core {

		namespace Files {

			/*
			File: Defines a set of methods and operations that can be used to create, modify, and perform operations on individual files.
			*/
			class File : public FileRef {
				public:
					/* Public Class Properties */
					//FilePosition: Defines a list of read/write positions relative to the current position.
					enum FilePosition {
						//Relative to the beginning of the file.
						Begin,
						//Relative to the current position in the file.
						Current,
						//Relative to the end of the file.
						End,
					};
					//FileAccessMode: Defines a list of different modes of file access.
					enum FileAccessMode {
						//Read: Class can only perform read operations on the file.
						Read,
						//Write: Class can only perform write operations on the file.
						Write,
						//ReadWrite: Class may perform both read and write operations.
						ReadWrite,
						//Append: Class may only perform write operations on the file, but only from the end of the file.
						Append,
					};

					/* Public Class Methods */
					//Default Constructor
					File();
					//Destructor, Virtual for platform overwrites
					virtual ~File();
					//Read from a file
					virtual U64 read(any dstBuff, U64 size) = 0;
					//Write to a file
					virtual U64 write(cAny srcBuff, U64 size) = 0;
					//Get the current file position
					virtual U64 getPosition() = 0;
					//Set the current file position
					virtual U64 setPosition(U64 pos, FilePosition p) = 0;
					//Open a file
					virtual bool openFile(FileAccessMode acc) = 0;
					//Close a file
					virtual bool closeFile() = 0;
			};

			/* Typedef out Weak/Strong references to File to be used by the other classes */
			//Weak Reference Pointer to File
			typedef WeakReferencePtr<File> FilePtr;
			//Strong Reference Pointer to File
			typedef StrongReferencePtr<File> File_Ref;

		};

	};

};

#endif //GALACTIC_INTERNAL_FILES_FILE