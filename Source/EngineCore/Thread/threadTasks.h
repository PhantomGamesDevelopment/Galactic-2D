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

		};

		/*
		Work: Creates a class instance to store information regarding a task that needs to be done as part of the global thread pool
		*/
		class Work {

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