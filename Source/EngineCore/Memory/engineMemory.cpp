/**
* Galactic 2D
* Source/EngineCore/Memory/engineMemory.cpp
* Defines wrappers to platform specific memory functioning to be used as a global call source
* (C) 2014-2016 Phantom Games Development - All Rights Reserved
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

#include "../engineCore.h"
#include "allocaterThreadProxy.h"

namespace Galactic {

	namespace Core {

		//Method to be called on all class instances to ensure the allocater instance is created
		void createAllocater() {
			if (!_GAllocater) {
				_GAllocater = PlatformMemory::Allocater();
				//Do we need a Thread Proxy?
				if (!_GAllocater->isThreadSafe()) {
					//Create it.
				}
			}		
		}

		S32 Memory::Memcmp(cAny m1, cAny m2, SIZE_T count) {
			return PlatformMemory::Memcmp(m1, m2, count);
		}

		any Memory::Memcpy(any dst, cAny src, SIZE_T count) {
			return PlatformMemory::Memcpy(dst, src, count);
		}
		
		any Memory::Memmove(any dst, cAny src, SIZE_T count) {
			return PlatformMemory::Memmove(dst, src, count);
		}

		any Memory::Memset(any dst, U8 value, SIZE_T count) {
			return PlatformMemory::Memset(dst, value, count);
		}

		void Memory::Memswap(any m1, any m2, SIZE_T count) {
			return PlatformMemory::Memswap(m1, m2, count);
		}

		any Memory::C_malloc(SIZE_T size) {
			return ::malloc(size);
		}

		void Memory::C_free(any ptr) {
			::free(ptr);
		}

		any Memory::Malloc(SIZE_T size, U32 alignment) {
			GLOBALALLOCCHECK("Malloc");
			return _GAllocater->Malloc(size, alignment);
		}

		any Memory::Realloc(any ptr, SIZE_T size, U32 alignment) {
			GLOBALALLOCCHECK("Realloc");
			return _GAllocater->Realloc(ptr, size, alignment);
		}

		void Memory::Free(any ptr) {
			GLOBALALLOCCHECK("Free");
			_GAllocater->Free(ptr);
		}

		SIZE_T Memory::fetchRealSize(SIZE_T requested, U32 alignment) {
			GLOBALALLOCCHECK("fetchRealSize");
			_GAllocater->fetchRealSize(requested, alignment);
		}

		SIZE_T Memory::fetchBlockSize(any ptr) {
			GLOBALALLOCCHECK("fetchBlockSize");
			SIZE_T result = 0;
			return _GAllocater->fetchBlockSize(ptr, result) ? result : 0;
		}

		any Memory::zeroBlock(any dst, SIZE_T count) {
			return Memory::Memset(dst, NULL, count);
		}

		any Memory::Memcpy_block(any dst, cAny src, SIZE_T count) {
			return PlatformMemory::Memcpy_block(dst, src, count);
		}

		any Memory::Memcpy_streamed(any dst, cAny src, SIZE_T count) {
			return PlatformMemory::Memcpy_streamed(dst, src, count);
		}

	};

};