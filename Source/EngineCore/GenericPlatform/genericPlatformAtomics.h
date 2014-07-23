/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* genericPlatformAtomics.h
*
* Defines a system for declaring atomic style functions, which are thread-safe locked functions
*
* References:
* http://www.cplusplus.com/reference/atomic/atomic/
**/

#ifndef GALACTIC_PLATFORM_GENERIC_ATOMICS
#define GALACTIC_PLATFORM_GENERIC_ATOMICS

namespace Galactic {

	namespace Core {

		/*
		S128: Internal representation of a 128-bit integer (IE: cross platform _int128), uses two S64's to accomplish this.
		 We force the alignment to 16-byte boundaries to meet requirements on most processers today
		*/
		struct VS_ALIGN(16) S128 {
			/* Struct Methods */
			//Default Constructor
			S128(S64 l, S64 h) : low(l), high(h) { }
			/* Struct Members */
			//The low part of the integer
			S64 low;
			//The high part of the integer
			S64 high;
		} GNU_ALIGN(16);

		/*
		GenericPlatformAtomics: Define a generic class for forcing functions to be "atomic", or completely thread safe, by locking a
		 cumulative counter variable.
		*/
		class GenericPlatformAtomics {
			protected:
				/* Protected Class Methods */
				//Checks if the target pointer is in alignment to be used with atomic functions
				SFIN bool aligned(const volatile any ptr, Z32 memAlignment = sizeof(any)) {
					return !((IntPointer(ptr)) & (memAlignment - 1));
				}
		};

	};

};

#endif //GALACTIC_PLATFORM_GENERIC_ATOMICS