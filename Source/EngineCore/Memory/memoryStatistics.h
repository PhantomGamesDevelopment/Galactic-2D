/**
* Galactic 2D
* Source/EngineCore/Memory/memoryStatistics.h
* Defines a statistics collection class instance to be used for the memory systems to track engine memory usage
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

#ifndef GALACTIC_CORE_MEMORY_MEMSTATS
#define GALACTIC_CORE_MEMORY_MEMSTATS

namespace Galactic {

	namespace Core {

		/*
		MemoryStatistics: A basic container implementation that is used to hold memory statistics to be tracked by the engine
		*/
		class MemoryStatistics {
			public:
				/* Public Class Methods */
				//Add a statistic to the container, or update an existing one
				void addStatistic(String name, SIZE_T value, bool expectingExisting = true) {
					if (!mappedStatistic.find(name)) {
						mappedStatistic.insert(name, value);
					}
					else {
						MapNode<String, SIZE_T> &n = mappedStatistic.at(name);
						if (!expectingExisting && (&n != NULL)) {
							GC_Error("MemoryStatistics::addStatistic(%s, %lld): Found existing named value of this type when expectation was a non-existant case.", name, value);
							return;
						}
						n = value;
					}
				}

				//Obtain the current value of a named statistic
				SIZE_T fetchStoredValue(String name) {
					if (!mappedStatistic.find(name)) {
						GC_Error("MemoryStatistics::fetchStoredValue(%s): No memory statistic of the given name is stored.", name);
						return -1;
					}
					return mappedStatistic.at(name).second;
				}

				//Purge the map of values
				void purgeStatistics() {
					mappedStatistic.clear();
				}

			private:
				/* Private Class Members */
				//A mapped memory statistic to be held by the engine
				Map<String, SIZE_T> mappedStatistic;
		};

		/*
		memoryCommandCalls: A singleton class instance that holds the global number of calls to malloc(), realloc(), and free() for engine statistics
		 collection purposes.
		*/
		class memoryCommandCalls {
			public:
				/* Public Class Methods */
				//Constructor
				memoryCommandCalls() :
					lastMallocCount(0),
					lastReallocCount(0),
					lastFreeCount(0),
					currentMallocCount(0),
					currentReallocCount(0),
					currentFreeCount(0),
					totalCount(0) { }

				//Fetch the singleton instance of this class
				static memoryCommandCalls &fetchInstance() {
					if (managedSingleton<memoryCommandCalls>::instance() == NULL) {
						managedSingleton<memoryCommandCalls>::createInstance();
					}
					return *(managedSingleton<memoryCommandCalls>::instance());
				}

				//Dump the statistics to a MemoryStatistics module
				void dumpStatistics(MemoryStatistics &statContainer) {
					statContainer.addStatistic("MallocCalls", currentMallocCount);
					statContainer.addStatistic("ReallocCalls", currentReallocCount);
					statContainer.addStatistic("FreeCalls", currentFreeCount);
					statContainer.addStatistic("TotalCommandCalls", totalCount);
				}

				//Update the count based on the allocator class
				void update() {
					currentMallocCount = Allocater::mallocCalls - lastMallocCount;
					currentReallocCount = Allocater::reallocCalls - lastReallocCount;
					currentFreeCount = Allocater::freeCalls - lastFreeCount;
					lastMallocCount = Allocater::mallocCalls;
					lastReallocCount = Allocater::reallocCalls;
					lastFreeCount = Allocater::freeCalls;
					totalCount = currentMallocCount + currentReallocCount + currentFreeCount;
				}

				/* Public Class Members */
				//The number of malloc() calls on the last update
				U32 lastMallocCount;
				//The number of realloc() calls on the last update
				U32 lastReallocCount;
				//The number of free() calls on the last update
				U32 lastFreeCount;
				//The number of malloc() calls on the this update
				U32 currentMallocCount;
				//The number of realloc() calls on the this update
				U32 currentReallocCount;
				//The number of free() calls on the this update
				U32 currentFreeCount;
				//The total number of memory commands called on this update
				U32 totalCount;
		};

	};

};

#endif //GALACTIC_CORE_MEMORY_MEMSTATS