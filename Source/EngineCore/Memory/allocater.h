/**
* Galactic 2D
* Source/EngineCore/Memory/allocater.h
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

#ifndef GALACTIC_CORE_MEMORY_MEMBASE
#define GALACTIC_CORE_MEMORY_MEMBASE

#include "engineMemory.h"

//Global pointer to the engine's active memory allocator class
extern class Galactic::Core::Allocater *_GAllocater;

namespace Galactic {

	namespace Core {

		//Forward declaration for memory statistics class. (ToDo: Look into potential load order adjustments)
		class MemoryStatistics;

		/*
		CAllocater: A specialized class that overloads common creation / deletion methods. Objects that need to be initialized under standard C/C++
		 memory allocation calls should overload this class instead of Allocater. Our Allocater class inherits this class, but overloads the defined
		 methods within. (We love shortcuts ;))
		*/
		class CAllocater {
			public:
				/* Public Class Methods */
				/* Operator Overloads */
				//new() operator
				any operator new(size_t size);
				//delete() operator
				void operator delete(any ptr);
				//new[]() operator
				any operator new[](size_t size);
				//delete[]() operator
				void operator delete[](any ptr);
		};

		/*
		Allocater: The engine's primary memory allocation class. Inherits CAllocater as a source of method name implements. This class serves as a primary
		 template for the engine's malloc classes, which are initialized by the specific platform as needed.
		*/
		class Allocater : public CAllocater {
			public:
				/* Public Class Methods */
				/* Primary Tools */
				//Perform a malloc() operation using cross-platform accepted functioning
				virtual any Malloc(SIZE_T size, U32 alignment = MEMORY_DEFEAULTALIGN) = 0;
				//Perform a realloc() operation using cross-platform accepted functioning
				virtual any Realloc(any ptr, SIZE_T size, U32 alignment = MEMORY_DEFEAULTALIGN) = 0;
				//Perform a free() operation using cross-platform accepted functioning
				virtual any Free(any ptr) = 0;
				
				/* Additional Tools */
				//Return the name of the malloc class
				virtual UTF16 getTypeName();
				//Validate the heap
				virtual bool validateHeap();
				//When classes and containers need to allocate a block of memory that is non-static, call this function to pre-detect the "actual" available
				// space for allocation under the specified memory alignment.
				virtual SIZE_T fetchRealSize(SIZE_T requested, U32 alignment = MEMORY_DEFEAULTALIGN);
				//Fetch the size of a memory block, if possible, return a boolean value to determine if operation successful or not.
				virtual bool fetchBlockSize(any ptr, SIZE_T &out);
				//Update the engine's memory statistics
				virtual void updateEngineMemoryStats();
				//Fetch the engine's memory statistics
				virtual void fetchEngineMemoryStats(MemoryStatistics &stats);
				//Is the implementation of this class thread safe?
				virtual bool isThreadSafe() const;

			protected:
				//Define class friendship to the singleton instance of memoryCommandCalls
				friend class memoryCommandCalls;

				/* Protected Class Methods */
				//Add a Malloc() call to the counter
				FINLINE void addMallocCall();
				//Add a Realloc() call to the counter
				FINLINE void addReallocCall();
				//Add a Free() call to the counter
				FINLINE void addFreeCall();

				/* Protected Class Members */
				//The number of times Malloc() was called
				static U32 mallocCalls;
				//The number of times Realloc() was called
				static U32 reallocCalls;
				//The number of times Free() was called
				static U32 freeCalls;

		};

	};

};

#endif //GALACTIC_CORE_MEMORY_MEMBASE