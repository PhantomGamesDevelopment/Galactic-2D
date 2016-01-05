/**
* Galactic 2D
* Source/EngineCore/PlatformCore/platformMemory.h
* Cross-Platform memory manipulation wrapper
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

#ifndef GALACTIC_PLATFORM_GENERICMEMORY
#define GALACTIC_PLATFORM_GENERICMEMORY

namespace Galactic {

	namespace Core {

		/* Declare the global allocater system */
		extern class Allocater *_GAllocater;

		/*
		Memory: The highest level generic memory class in the engine. Wraps all of the platform specific functions into an easy
		to use overlay.
		*/
		class Memory {
			public:
				/* Public Class Members */
				//Alignments: Enumerates some constants for usage throughout the memory methods.
				enum Alignments {
					/*
					Default: Follows the standard memory alignment rules. Basically, we align blocks of memory >16 bytes to 16, and <16 to 8.
					 This enum behaves more as a flag to trigger proper alignment.
					*/
					Default = 0,
					//Minimum: The minimum block alignment for memory in the engine is 8 blocks.
					Minimum = 8,
				};

				/* Public Class Methods */
				//memcmp: Declare a platform independant memcmp wrapper
				SFIN S32 gmemcmp(cAny ptr1, cAny ptr2, SIZE_T amount);
				//memcpy: Declare a platform independant memcpy wrapper
				SFIN any gmemcpy(any dstPtr, cAny srcPtr, SIZE_T amount);
				//memmove: Declare a platform independant memmove wrapper
				SFIN any gmemmove(any dstPtr, cAny srcPtr, SIZE_T amount);
				//memset: Declare a platform independant memset wrapper
				SFIN any gmemset(any dstPtr, S32 value, SIZE_T amount);
				//sysmalloc: Declare a platform independant malloc wrapper
				SFIN any sysmalloc(SIZE_T amount) {
					return ::malloc(amount);
				}
				//sysfree: Declare a platform independant free wrapper
				SFIN void sysfree(any ptr) {
					::free(ptr);
				}

				/* Define global usage functions */
				//malloc
				static any gmalloc(SIZE_T amount, U32 memAlignment = Default);
				//realloc
				static any grealloc(any src, SIZE_T amount, U32 memAlignment = Default);
				//free
				static void gfree(any trg);
		};

		/*
		AllocaterSystem: This is a internal class (You shouldn't define this... ever). It basically translates the Memory functions to a format
		 that can be used by the Allocater class below.
		*/
		class AllocaterSystem {
			public:
				/* Operators */
				//new: NOTE: we're forced to use size_t here because C++ says we need to, this may cause some problems later on, investigate.
				any operator new(size_t amount){
					return Memory::sysmalloc(amount);
				}

				//delete
				void operator delete(any ptr) {
					Memory::sysfree(ptr);
				}

				//new[], see note above...
				any operator new[](size_t amount) {
					return Memory::sysmalloc(amount);
				}

				//delete[]
				void operator delete[](any ptr) {
					Memory::sysfree(ptr);
				}
		};

		/*
		Allocater: This class is the main wrapper class that handles memory allocation, and the such.
		*/
		class Allocater : public AllocaterSystem {
			public:
				/* Public Class Methods */
				//malloc: Declare a platform independant malloc wrapper
				virtual any gmalloc(SIZE_T amount, U32 memAlignment = Memory::Default) = 0;
				//realloc: Declare a platform independant realloc wrapper
				virtual any grealloc(any srcPtr, SIZE_T amount, U32 memAlignment = Memory::Default) = 0;
				//free: Declare a platform independant free wrapper
				virtual void gfree(any trgPtr) = 0;
				//Is this allocater thread safe?
				virtual bool isThreadSafe() const { return false; }
				//Validate the allocation heap
				virtual bool validateHeap() { return true; }
		};

	};

};

#endif //GALACTIC_PLATFORM_GENERICMEMORY