/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* platformMemory.cpp
*
* Loads a generic platform independant memory system wrapper that uses the platform specific memory functions.
**/

#include "platformMemory.h"

namespace Galactic {

	namespace Core {

		bool createAllocater(UTF16 srcFunc) {
			if (!_GAllocater) {
				_GAllocater = PlatformMemory::Allocater();
				if (!_GAllocater) {
					GC_CError("[engineCore/platformMemory.cpp] createAllocater(%s) - Critical Error: Failed to initialize platform memory allocater.", srcFunc);
					return false;
				}
			}
			return true;
		}

		S32 Memory::gmemcmp(cAny ptr1, cAny ptr2, SIZE_T amount) {
			return PlatformMemory::gmemcmp(ptr1, ptr2, amount);
		}

		any Memory::gmemcpy(any dstPtr, cAny srcPtr, SIZE_T amount) {
			return PlatformMemory::gmemcpy(dstPtr, srcPtr, amount);
		}

		any Memory::gmemmove(any dstPtr, cAny srcPtr, SIZE_T amount) {
			return PlatformMemory::gmemmove(dstPtr, srcPtr, amount);
		}

		any Memory::gmemset(any dstPtr, S32 value, SIZE_T amount) {
			return PlatformMemory::gmemset(dstPtr, value, amount);
		}

		any Memory::gmalloc(SIZE_T amount, U32 memAlignment) {
			if (!createAllocater("malloc")) {
				return NULL;
			}
			return _GAllocater->gmalloc(amount, memAlignment);
		}

		any Memory::grealloc(any src, SIZE_T amount, U32 memAlignment) {
			if (!createAllocater("realloc")) {
				return NULL;
			}
			return _GAllocater->grealloc(src, amount, memAlignment);
		}

		void Memory::gfree(any trg) {
			if (!createAllocater("free")) {
				return;
			}
			_GAllocater->gfree(trg);
		}

	};

};