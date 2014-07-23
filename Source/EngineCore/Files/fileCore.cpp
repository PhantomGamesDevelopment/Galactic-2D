/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* fileCore.cpp
*
* Defines the FileCore class which serves as a gateway between the individual fileRef classes and the functionality desired by the calling
* methods.
**/

#include "fileCore.h"

namespace Galactic {

	namespace Core {

		namespace Files {

			/*
			NOTE: This really is just serving as a stub C++ file here, in the event the FileCore class is expanded upon in a way, we can simply
			add in the necessary changes to this file. For the individual functions that are used in this file and defined in a pure
			virtual sense, you'll need to see the individual edits made by the individual platforms definitions of platformFile.h/.cpp.
			*/

			FileCore::FileCore() {
				isReadOnly = false;
			}

			FileCore::~FileCore() {

			}

			bool FileCore::readOnly() {
				return isReadOnly;
			}

		};

	};

};