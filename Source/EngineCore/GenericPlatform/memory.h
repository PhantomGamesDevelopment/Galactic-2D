/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/memory.h
* Defines the platform specific memory class and functions
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

#ifndef GALACTIC_PLATFORM_GENERIC_PLATFORMMEMORY
#define GALACTIC_PLATFORM_GENERIC_PLATFORMMEMORY

namespace Galactic {

	namespace Core {
		/* 
		We start with a few important definitions...
		*/
		#if GALACTIC_PLATFORM_USELIBCMT == 1
			#define ALLOCFUNC _alloca
		#else
			#define ALLOCFUNC alloca
		#endif
		#define GALACTIC_ALLOC(x) ((x == 0) ? 0 : (any)(((IntPointer)ALLOCFUNC(x + 16) + 16) & ~16))

		/*
		MemoryConstants: Holds a list of values associated with standard memory constant values. Used to store memory usage throghout the running of the engine.
		*/
		struct MemoryConstants {
			/* Struct Members */
			//physicalMem: The amount of available physical memory
			SIZE_T physicalMem;
			//virtualMem: The amount of available virtual memory
			SIZE_T virtualMem;
			//memInGB: The approximate available memory in GB value
			U32 memInGB;

			/* Struct Methods */
			//Default Constructor
			MemoryConstants() : physicalMem(0), virtualMem(0), memInGB(1) { }
			//Copy Constructor
			MemoryConstants(const MemoryConstants &trg) : physicalMem(trg.physicalMem), virtualMem(trg.virtualMem), memInGB(trg.memInGB) { }
		};

		/*
		MemoryStatistics: Stores values used by the memory manager such as how much memory has been used and is still remaining.
		*/
		struct MemoryStatistics : public MemoryConstants {
			/* Struct Members */
			//physicalAvail: How much physical memory is available
			SIZE_T physicalAvail;
			//virtualAvail: How much virtual memory is available
			SIZE_T virtualAvail;
			//physicalUsed: How much physical memory has been used
			SIZE_T physicalUsed;
			//virtualUsed: How much virtual memory has been used
			SIZE_T virtualUsed;

			/* Struct Methods */
			//Default Constructor
			MemoryStatistics() : physicalAvail(0), virtualAvail(0), physicalUsed(0), virtualUsed(0) { }
		};

		/*
		GenericPlatformMemory: Serves as a gateway wrapper between the generic Memory class and the platform specific PlatformMemory classes.
		*/
		class GenericPlatformMemory {
			public:
				/* Public Class Members */
				//Memory Counter
				enum MemCounter {
					//Mem_Physical: Physical memory (main system memory)
					Mem_Physical,
					//Mem_GPU: GPU RAM (Memory available on graphics card)
					Mem_GPU,
					//Mem_GPUAccessed: Physical memory that is being used by the GPU
					Mem_GPUAccessed,
					//Mem_Invalid: Target is not memory
					Mem_Invalid,
					//Mem_Maximum: The maximum memory available to PlatformMemory
					Mem_Maximum,
				};

				//MemDecs
				enum MemDecs {
					//Read: Declares the memory operation to read. (Standard)
					Read = (1 << 1),
					//Write: Declares the memory operation to write. (Standard)
					Write = (1 << 2),
				};

				/* Public Class Methods */
				//initialize the module
				static void init();
				//create the memory pools
				static void initPools();
				//obtain the instance of the Allocater class
				static class Allocater *Allocater();
				//Alloc method for windows
				static any Alloc(SIZE_T amount);
				//Free method for windows
				static void Free(any ptr);
				//Returns the amount of physical memory in GB approximation
				static U32 fetchGBMem();
				//Operation to be called when the allocater is out of memory
				static void onOutOfMem(U64 requestedAmt, U32 memAlignment);
				//Fetch the current memory statistics
				static MemoryStatistics fetchStats();
				//Update the memory statistics
				static void updateStats();
				//Generic platform memcmp function
				SFIN S32 Memcmp(cAny ptr1, cAny ptr2, SIZE_T amount);
				//Generic platform memcpy function
				SFIN any Memcpy(any dstPtr, cAny srcPtr, SIZE_T amount);
				//Generic platform memmove function
				SFIN any Memmove(any dstPtr, cAny srcPtr, SIZE_T amount);
				//Generic platform memset function
				SFIN any Memset(any dstPtr, S32 value, SIZE_T amount);
				//Generic platform memswap function
				SFIN void Memswap(any m1, any m2, SIZE_T count);
				//Alternate version of memcpy that is optimized for large blocks.
				SFIN any Memcpy_block(any dst, cAny src, SIZE_T count);
				//Alternate version of memcpy that streams copy commands to avoid L2 cache pollution by means of overloading with large blocks
				SFIN any Memcpy_streamed(any dst, cAny src, SIZE_T count);
		};

	};

};

#endif //GALACTIC_PLATFORM_GENERIC_PLATFORMMEMORY