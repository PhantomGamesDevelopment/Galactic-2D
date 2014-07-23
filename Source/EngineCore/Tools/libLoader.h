/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* libLoader.h
*
* Defines a platform specific library loading function. Allows you to load in .DLLs (WIN32), .SO (UNIX), and .app (MAC-OS) files
**/

#ifndef GALACTIC_INTERNAL_LIBLOADER
#define GALACTIC_INTERNAL_LIBLOADER

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		class LibLoader {
			public:
				LibLoader();
		
		};

	};

};

#endif //GALACTIC_INTERNAL_LIBLOADER