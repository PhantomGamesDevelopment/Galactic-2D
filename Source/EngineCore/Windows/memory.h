/**
* Galactic 2D
* Source/EngineCore/Windows/memory.cpp
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

#ifdef GALACTIC_WINDOWS

	#ifndef PLATFORM_WINDOWS_MEMORY
	#define PLATFORM_WINDOWS_MEMORY

	namespace Galactic {

		namespace Core {

			/*
			PlatformMemory: Windows specific memory operations
			*/
			class PlatformMemory : public GenericPlatformMemory {
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

					/* Public Class Methods */
					//initialize the module
					static void init();
					//obtain the instance of the Allocater class
					static class Allocater *Allocater();
					//Alloc method for windows
					static any Alloc(SIZE_T amount);
					//Free method for windows
					static void Free(any ptr);
			};

		}

	}

	#endif //PLATFORM_WINDOWS_MEMORY

#endif //GALACTIC_WINDOWS