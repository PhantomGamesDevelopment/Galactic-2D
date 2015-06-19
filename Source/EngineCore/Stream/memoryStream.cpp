/**
* Galactic 2D
* Source/EngineCore/Stream/memoryStream.cpp
* Definitions for the memory stream read and write classes
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

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		MemoryStream Definitions
		*/

		S64 MemoryStream::tell() {
			return cOffset;
		}

		void MemoryStream::seek(S64 inPos) {
			cOffset = inPos;
		}

		/*
		MemoryWriter Definitions
		*/

		MemoryWriter::MemoryWriter(DynArray<U8> &refMem, bool isPersistent = false, bool setOffset = false) :
			MemoryStream(), memory(refMem) {
			strIsSaving = true;
			shouldSaveToPersistent = isPersistent;
			if (setOffset) {
				cOffset = memory.size();
			}
		}

		void MemoryWriter::pack(any dataPtr, S64 len) {
			const S64 bytes = cOffset + len - memory.size();
			if (bytes > 0) {
				const S64 newSize = memory.size() + bytes;
				if (newSize > MAX_S32) {
					GC_Error("MemoryWriter::pack(): Cannot pack memory to the stream that exceeds 2GB.");
					return;
				}
				memory.reserve((U32)newSize);
			}
			//Validate the sizes...
			if ((cOffset + len) > memory.size()) {
				GC_CError("MemoryWriter::pack(): Attempting to pack memory outside the bounds of the stream. breaking.");
				return;
			}
			//Write it.
			if (len > 0) {
				Memory::gmemcpy(&memory[cOffset], dataPtr, len);
				cOffset += len;
			}
		}

		S64 MemoryWriter::fetchSize() {
			return memory.size();
		}

		/*
		MemoryReader Definitions
		*/

		MemoryReader::MemoryReader(DynArray<U8> &refMem, bool isPersistent = false) :
			MemoryStream(), memory(refMem) {
			strIsLoading = true;
			shouldSaveToPersistent = isPersistent;
		}

		void MemoryReader::pack(any dataPtr, S64 len) {
			if (!hasError && len > 0) {
				//Validate the offset ad available space
				if (cOffset + len <= memory.size()) {
					Memory::gmemcpy(dataPtr, &memory[cOffset], len);
					cOffset += len;
				}
				else {
					//Nope.
					hasError = true;
				}
			}
		}

		void MemoryReader::seek(S64 inPos) {
			if (inPos > memory.size()) {
				GC_Error("MemoryReader::seek(): Cannot seek outside of stream bounds.");
				return;
			}
			MemoryStream::seek(inPos);
		}

		S64 MemoryReader::fetchSize() {
			return memory.size();
		}

	};

};