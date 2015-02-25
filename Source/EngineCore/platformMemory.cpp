/**
* Galactic 2D
* Source/EngineCore/platformMemory.cpp
* Cross-Platform memory manipulation wrapper
* (C) 2014-2015 Phantom Games Development - All Rights Reserved
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
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