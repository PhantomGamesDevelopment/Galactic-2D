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

		UTF16 GenericPlatformProcess::getUserDir() {

		}

		U64 GenericPlatformProcess::fetchAffinityMask(UTF16 name) {
			return U64DEF(0xffffffffffffffff);
		}

	};

};