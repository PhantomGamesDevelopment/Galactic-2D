/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* genericPlatform.cpp
*
* Defines methods and operations that are specific to platforms, in this case, these are templates to other platforms for easy declaration
**/

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/* GenericPlatformProcess Class */
		U32 GenericPlatformProcess::getProcID() {
			return 0;
		}

		const TCHAR *GenericPlatformProcess::getBaseDir() {
			//Not implemented in the generic platform...
		}

		const TCHAR *GenericPlatformProcess::getUserDir() {

		}

	};

};