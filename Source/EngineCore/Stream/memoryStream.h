/**
* Galactic 2D
* Source/EngineCore/Stream/memoryStream.h
* Definitions for the memory stream read and write classes
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

#ifndef GALACTIC_INTERNAL_MEMORYSTREAM
#define GALACTIC_INTERNAL_MEMORYSTREAM

namespace Galactic {

	namespace Core {

		/*
		MemoryStream: Default template class used to define the read and write classes
		*/
		class MemoryStream : public Stream {
			public:
				/* Public Class Methods */
				//Tell the current position of the stream operation
				S64 tell();
				//Move the stream operation to the specified position
				void seek(S64 inPos);

			protected:
				/* Protected Class Methods */
				//Default (Empty) Constructor, placed in protected to prevent direct creation of this instance
				MemoryStream() : Stream(), cOffset(0) { }

				/* Protected Class Members */
				//The current offset position of the stream read or write operation
				S64 cOffset;
		};

		/*
		MemoryWriter: A specialized instance of the MemoryStream built to write memory
		*/
		class MemoryWriter : public MemoryStream {
			public:
				/* Public Class Methods */
				//Constructor
				MemoryWriter(DynArray<U8> &refMem, bool isPersistent = false, bool setOffset = false);
				//Pack data to the stream
				void pack(any dataPtr, S64 len);
				//Fetch the current size used by the stream
				S64 fetchSize();

			protected:
				/* Protected Class Members */
				//The memory stored on this stream
				DynArray<U8> &memory;
		};

		/*
		MemoryReader: A specialized instance of the MemoryStream built to read memory
		*/
		class MemoryReader : public MemoryStream {
			public:
				/* Public Class Methods */
				//Constructor
				MemoryReader(DynArray<U8> &refMem, bool isPersistent = false);
				//Pack data from the stream
				void pack(any dataPtr, S64 len);
				//Move the stream operation to the specified position
				void seek(S64 inPos);
				//Fetch the current size used by the stream
				S64 fetchSize();

			protected:
				/* Protected Class Members */
				//The memory stored on this stream
				DynArray<U8> &memory;
		};

	};

};

#endif //GALACTIC_INTERNAL_MEMORYSTREAM