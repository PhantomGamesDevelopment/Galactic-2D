/**
* Galactic 2D
* Source/EngineCore/Memory/memory.cpp
* Defines the base memory allocator instance and loads out calls to the generic memory classes
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
#include "memoryStatistics.h"

namespace Galactic {

	namespace Core {

		U32 Allocater::mallocCalls = 0;
		U32 Allocater::reallocCalls = 0;
		U32 Allocater::freeCalls = 0;

		/* CAllocater Class */

		any CAllocater::operator new(size_t size) {
			return Memory::C_malloc(size);
		}

		void CAllocater::operator delete(any ptr) {
			Memory::C_free(ptr);
		}

		any CAllocater::operator new[](size_t size) {
			return Memory::C_malloc(size);
		}

		void CAllocater::operator delete[](any ptr) {
			Memory::C_free(ptr);
		}

		/* Allocater Class */

		UTF16 Allocater::getTypeName() {
			//If the engine spits this out, you know there's something wrong...
			return "Undefined";
		}

		bool Allocater::validateHeap() {
			return true;
		}

		SIZE_T Allocater::fetchRealSize(SIZE_T requested, U32 alignment) {
			return requested;
		}

		bool Allocater::fetchBlockSize(any ptr, SIZE_T &out) {
			return false;
		}

		void Allocater::updateEngineMemoryStats() {
			memoryCommandCalls::fetchInstance().update();
		}

		void Allocater::fetchEngineMemoryStats(MemoryStatistics &stats) {
			memoryCommandCalls::fetchInstance().dumpStatistics(stats);
		}

		bool Allocater::isThreadSafe() const {
			return false;
		}

		void Allocater::addMallocCall() {
			PlatformAtomics::increment((volatile S32 *)&Allocater::mallocCalls);
		}

		void Allocater::addReallocCall() {
			PlatformAtomics::increment((volatile S32 *)&Allocater::reallocCalls);
		}

		void Allocater::addFreeCall() {
			PlatformAtomics::increment((volatile S32 *)&Allocater::freeCalls);
		}

	};

};