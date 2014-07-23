/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* fileBase.h
*
* This file contains the main portion of the File System in the Galactic Engine.
**/

#ifndef GALACTIC_INTERNAL_FILES_FILEBASE
#define GALACTIC_INTERNAL_FILES_FILEBASE

#include "../platform.h"
#include "../Tools/reference.h"
#include "../../Console/console.h"

namespace Galactic {

	namespace Core {

		namespace Files {

			/*
			FileBase: This is a strongly referenced class that is the center of the File I/O system in the Galactic Engine. Our other file classes base from 
			 this object here.
			*/
			class FileBase : public createStrongFromObj<FileBase> {
				public:
					virtual ~FileBase() { }
			};

		};

	};

};

#endif //GALACTIC_INTERNAL_FILES_FILEBASE