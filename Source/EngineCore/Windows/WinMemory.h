/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* platformMemory.h
*
* Loads the memory module for Windows platforms
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