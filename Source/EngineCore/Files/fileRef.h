/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* fileRef.h
*
* Defines the fileRef class which defines a set of common properties used by the file object classes in this engine. This code file is based off of the 
* Torque Game Engine's FileSystem, some of the features are the same, however modifications and adjustments are used to suit the Galactic 2D Engine.
**/

#ifndef GALACTIC_INTERNAL_FILES_FILEREF
#define GALACTIC_INTERNAL_FILES_FILEREF

#include "../engineCore.h"
#include "fileBase.h"
#include "filePath.h"

namespace Galactic {

	namespace Core {
		
		namespace Files {

			/*
			FileRef: Defines a set of functions and attributes that are common to all of the File classes used by the Galactic Engine
			*/
			class FileRef : public FileBase {
				public:
					/* Public Class Properties */
					//FileStatus: Defines a list of common OS flags and statuses used by files
					enum FileStatus {
						//File is Open
						Open,			
						//File is Closed
						Closed,
						//Access has reached the end of the file
						EndOfFile,
						//The disk drive is full
						FileSystemFull,
						//This file is currently open in another process
						SharingViolation,
						//Specified file does not exist
						NoSuchFile,
						//Access to this file is denied, possible UAC / ReadOnly error
						AccessDenied,
						//Unsupported operation has been performed
						IllegalCall,
						//Unidentified / Unknown error occured
						UnknownError,
					};
					//FileMode forward dec.
					enum FileMode {
						//Standard File Detected
						File,
						//Directory Detected
						Directory,
						//System File Detected
						System,
						//This file has the Hidden Flag applied
						Hidden,
						//This file is Read Only
						ReadOnly,
						//This file is a compressed archive (.zip / .rar)
						Compressed,
						//This file is an encrypted / password protected archive
						Encrypted,
						//This file is a dynamically linked library file (.dll / .so / .app)
						DynamicLibrary,
						//This file is an executable file
						Executable,
					};
					//FileAttributes forward dec.
					struct FileAttributes {
						//Name of the file / directory
						String fName;
						//FileMode flags applied
						U32 fFlags;
						//Size of the file / directory
						U64 fSize;
						//Time of last modification
						TimeVars fLastModified;
						//Time of last access
						TimeVars fLastAccessed;
					};

					/* Public Class Methods */
					//Default Constructor
					FileRef();
					//Get the file / directory path
					virtual FilePath getFilePath() const = 0;
					//Get the last modified time.
					virtual TimeVars getLastModified();
					//Get the current file Checksum
					virtual U64 getChecksum();
					//Get the current status of this FileRef object
					virtual FileStatus getStatus() const = 0;
					//Get the file attributes
					virtual bool getAttributes(FileAttributes *attr) = 0;
					//Get the file size
					virtual U64 getSize();
				protected:
					//Calculate the current checksum value, return 0 (false) on failure.
					virtual U64 calcChecksum() = 0;

				private:
					//Value of calculated Checksum, this is converted to a Sys.Time value
					U64 checksum;
					//Last checksum calculated, stored in Time format for easy use
					TimeVars lastChecksum;

			};

			/* Typedef out Weak/Strong references to FileRef to be used by the other classes */
			//Weak Reference Pointer to FileRef
			typedef WeakReferencePtr<FileRef> FileRefPtr;
			//Strong Reference Pointer to FileRef
			typedef StrongReferencePtr<FileRef> FileRef_Ref;

		};

	};

};

#endif //GALACTIC_INTERNAL_FILES_FILEREF