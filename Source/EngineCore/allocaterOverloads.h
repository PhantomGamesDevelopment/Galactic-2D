/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* allocaterOverloads.h
*
* Loads the specific allocater classes. These are the allocater classes that are actually used by the memory system.
**/

#ifndef GALACTIC_PLATFORM_ALLOCATEROVERLOADS
#define GALACTIC_PLATFORM_ALLOCATEROVERLOADS

#include "platformMemory.h"
#include "../Internal/Tools/advTools.h"

namespace Galactic {

	namespace Core {

		//Start by defining a check to use an alligned version of malloc
		#if _MSC_VER || GALACTIC_MAC
			#define ALIGN_MALLOC 1
		#else
			#undef ALIGN_MALLOC
		#endif
		//If we're on IOS, load in mach.h
		#ifdef GALACTIC_IOS
			#include <mach/mach.h>
		#endif

		/*
		ANSIAllocater: C-Language ANSI Style allocater system. Mainly used to keep backwards compatibility with older systems.
		*/
		class ANSIAllocater : public Allocater {
			public:
				/* Public Class Members */
				//Default Constructor
				ANSIAllocater() {
					//If we're on windows, we want to enable low-fragmentation for the heap. See: http://msdn2.microsoft.com/en-US/library/aa366750.aspx
					#ifdef GALACTIC_WINDOWS
						intptr_t HeapHandle = _get_heap_handle();
						ULONG LFH = 2;
						HeapSetInformation((PVOID)HeapHandle, HeapCompatibilityInformation, &LFH, sizeof(LFH));
					#endif
				}

				//Malloc override
				virtual any gmalloc(SIZE_T amount, U32 memAlignment) {
					memAlignment = gMax(amount >= 16 ? (U32)16 : (U32)8, memAlignment);
					//Check for use of aligned_malloc()
					#ifdef ALIGN_MALLOC
						any newPtr = _aligned_malloc(amount, (SIZE_T)memAlignment);
					#else
						//We'll need to manually allign it.
						any newMem = malloc(amount + memAlignment + sizeof(any) + sizeof(SIZE_T));
						//validate the pointer
						if (!newMem) {
							return NULL;
						}
						//alignVal() is located in Internal/Tools/advTools.h
						any newPtr = alignVal((UTX8)newMem + sizeof(any) + sizeof(SIZE_T), memAlignment);
						//Back out return values for amount and newMem in case we failed to generate it.
						amount = *((SIZE_T*)((UTX8)newPtr - sizeof(any) - sizeof(SIZE_T)));
						newMem = *((any*)((UTX8)newPtr - sizeof(any)));
					#endif
					if (!newPtr) {
						PlatformMemory::onOutOfMem(amount, memAlignment);
					}
					return newPtr;
				}

				virtual any grealloc(any srcPtr, SIZE_T amount, U32 memAlignment) {
					any newPtr = NULL;
					memAlignment = gMax(amount >= 16 ? (U32)16 : (U32)8, memAlignment);
					#ifdef ALIGN_MALLOC
						if (srcPtr && amount) {
							newPtr = _aligned_realloc(srcPtr, amount, memAlignment);
						}
						else if(!srcPtr) {
							newPtr = _aligned_malloc(amount, memAlignment);
						}
						else {
							_aligned_free(srcPtr);
						}
					#else
						if (srcPtr && amount) {
							//since we're aligning the memory, it's unsafe to use realloc, therefore, we'll use malloc on the new size and free up the old mem.
							newPtr = gmalloc(amount, memAlignment);
							Memory::memcpy(newPtr, srcPtr, gMin(NewSize, *((SIZE_T*)((UTX8)srcPtr - sizeof(any) - sizeof(SIZE_T)))));
							gfree(srcPtr);
						}
						else if (!srcPtr) {
							newPtr = gmalloc(amount, memAlignment);
						}
						else {
							free(*((any*)((UTX8)srcPtr - sizeof(any))));
						}
					#endif
					if (!newPtr && amount != 0) {
						PlatformMemory::onOutOfMem(amount, memAlignment);
					}
					return newPtr;
				}

				virtual void gfree(any trgPtr) {
					#ifdef ALIGN_MALLOC
						_aligned_free(trgPtr);
					#else
						if(trgPtr) {
							free(*((any*)((UTX8)trgPtr - sizeof(any))));
						}
					#endif
				}

				virtual bool isThreadSafe() const {
					#if defined(GALACTIC_MAC) || defined(GALACTIC_IOS)
						return true;
					#else
						return false;
					#endif
				}

				virtual bool validateHeap() {
					#ifdef GALACTIC_WINDOWS
						//Windows has a heap test function, we'll check our heap for potential errors and return false if we've got an issue.
						S32 test = _heapchk();
						if (test == _HEAPBADBEGIN || test == _HEAPBADNODE || test == _HEAPBADPTR || test == _HEAPEMPTY) {
							return false;
						}
					#endif
					return true;
				}
		};

		/*
		IntelTBBAllocater: 64-bit Allocater system used for support on 64-bit intel systems
		*/
		class IntelTBBAllocater : public Allocater {

		};

		/*
		StandardAllocater: Standardized Allocater system for usage on pretty much any platform
		*/
		class StandardAllocater : public Allocater {

		};

		/*
		ThreadSafeAllocater: Allocater system with a guarenteed thread-safe function proxy
		*/
		class ThreadSafeAllocater : public Allocater {

		};

	};

};

#endif //GALACTIC_PLATFORM_ALLOCATEROVERLOADS