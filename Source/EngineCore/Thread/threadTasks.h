/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* threadTasks.h
*
* Defines classes and operations to wire together the threading classes defined in threadBase.h & singleThreadBase.h
**/

#ifndef GALACTIC_THREADTASKS
#define GALACTIC_THREADTASKS

namespace Galactic {

	namespace Core {

		/*
		TSCounter: Makes use of atomic functions to lock a counter to be marked as "thread-safe". Has many uses around the engine to ensure values are
		 valid for uses on all threads.
		*/
		class TSCounter {
			public:	
				#if (!defined(GALACTIC_WINDOWS) || WINVER >= 0x0600)
					/* Constructor / Destructor */
					//Default Constructor
					TSCounter(S64 initValue = 0);
					//Copy Constructor
					TSCounter(const TSCounter &c);

					/* Public Class Methods */
					//Fetch the value on the counter
					S64 fetch() const;
					//Convert the counter to a 32-bit integer, if possible
					S32 toS32() const;
				#else
					//Default Constructor
					TSCounter(S32 initValue = 0);
					//Copy Constructor
					TSCounter(const TSCounter &c);

					/* Public Class Methods */
					//Fetch the value on the counter
					S32 fetch() const;
					//Convert the counter to a 32-bit integer, if possible
					S32 toS32() const { GC_Error("TSCounter::toS32(): This version of windows does not support 64-bit thread counters."); return fetch(); }
				#endif

			private:
				/* Private Class Methods */
				//Block access to the = operator
				void operator=(const TSCounter &) { }

				/* Private Class Members */
				#if (!defined(GALACTIC_WINDOWS) || WINVER >= 0x0600)
					//The numerical value of the counter instance
					volatile S64 tsCounter;
				#else
					//The numerical value of the counter instance
					volatile S32 tsCounter;
				#endif
		};

		/*
		Work: Creates a class instance to store information regarding a task that needs to be done as part of the global thread pool
		*/
		class Work {
			public:
				/* Constructor / Destructor */
				//Destructor
				virtual ~Work() { }

				/* Public Class Methods */
				//Perform the work task
				virtual void perform() = 0;
				//Stop the task from executing
				virtual void halt() = 0;
		};

		/*
		WorkPool: Holds all instances of Work objects and their individual threads in a queue to be executed in order that they were added to the list of
		 items to be done.
		*/
		class WorkPool {

		};

		/*
		ThreadedSingletonObject: A very special and unique thread class that defines a list of properties and parameters to allow singleton instances to be
		 globally safe throughout the engine when working with multiple threads.
		*/
		class ThreadedSingletonObject {

		};

		/*
		MutexLock: A useful class to "lock" aspects of a class to be off limits to other threads while execution is in process in the current thread.
		*/
		class MutexLock {

		};

	};

};

#endif //GALACTIC_THREADTASKS