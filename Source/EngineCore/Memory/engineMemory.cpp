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
#include "malloc_threaded.h"

namespace Galactic {

	namespace Core {

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

	};

};