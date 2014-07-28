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
				/* 
				Note: This definition block is here for the reason discussed in WinAtomics.h, Windows platforms below Windows Vista do not support
				 Atomic Locking Functions that use 64-bit integers, this system therefore provides those platforms with a 32-bit framework that can
				 function alongside the standard 64-bit version.
				*/
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
					//Add one to the counter
					S64 inc();
					//Decrement one from the coutner
					S64 dec();
					//Add to the counter
					S64 add(S64 amount);
					//Subtract from the counter
					S64 sub(S64 amount);
					//Set the counter to the specified value, pass no parameter to reset the counter
					S64 set(S64 value = 0);

					/* Operators */
					//Increment Operator
					S64 operator++();
					//Decrement Operator
					S64 operator--();
					//Addition Operator
					S64 operator+=(S64 amount);
					//Subtraction Operator
					S64 operator-=(S64 amount);
					//Application Operator
					S64 operator=(S64 value);

				#else
					//Default Constructor
					TSCounter(S32 initValue = 0);
					//Copy Constructor
					TSCounter(const TSCounter &c);

					/* Public Class Methods */
					//Fetch the value on the counter
					S32 fetch() const;
					//Convert the counter to a 32-bit integer, if possible
					S32 toS32() const;
					//Add one to the counter
					S32 inc();
					//Decrement one from the coutner
					S32 dec();
					//Add to the counter
					S32 add(S32 amount);
					//Subtract from the counter
					S32 sub(S32 amount);
					//Set the counter to the specified value, pass no parameter to reset the counter
					S32 set(S32 value = 0);

					/* Operators */
					//Increment Operator
					S32 operator++();
					//Decrement Operator
					S32 operator--();
					//Addition Operator
					S32 operator+=(S32 amount);
					//Subtraction Operator
					S32 operator-=(S32 amount);
					//Application Operator
					S32 operator=(S32 value);

				#endif

			private:
				/* Private Class Methods */
				//Block access to the assignment operator
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
		WorkerThread: A thread instance used to perform a work task. Think of this as the ObjectThread instance where Work can be treated as a form of
		 Event class.
		*/
		class WorkerThread : public ObjectThread {
			public:
				/* Constructor / Destructor */
				//Default Constructor
				WorkerThread();

				/* Public Class Methods */
				//Create an instance of the WorkedThread
				virtual bool create(class WorkPoolBase *owningPool, ThreadBase::ThreadPriority p = ThreadBase::Normal, U32 stackSize = 0);
				//Order the thread to perform it's work
				void performWork(Work *workToDo);
				//Kill this thread instance
				virtual bool kill();

			protected:
				/* Protected Class Methods */
				//The process to run when this thread is called
				virtual U32 run();

				/* Protected Class Members */
				//Flag to tell the thread to die, since the pool is also by definition thread-safe (wierd, right), we use a integer under an atomic lock here.
				volatile S32 killThreadFlag;
				//The thread instance of the workerThread
				ContinualThread *threadInst;
				//The instance of the thread pool this belongs to
				class WorkPoolBase *poolInst;
				//The event object (if any), this thread is attached to
				Event *workEvent;
				//And the work task itself...
				volatile Work *threadWork;
		};

		/*
		WorkPoolBase: Holds all instances of Work objects and their individual threads in a queue to be executed in order that they were added to the list of
		 items to be done. However, this only defines some template instances, the actual class used by the engine is right below MutexLock.
		*/
		class WorkPoolBase {
			public:
				/* Constructor / Destructor */
				//Destructor
				virtual ~WorkPoolBase() { }

				/* Public Class Methods */
				//Allocate an instance of the WorkPoolBase for use
				static WorkPoolBase *createInstance();
				//Create the thread pool with the specified number of threads and properties
				virtual bool createWithAmount(U32 amountOfThreads, ThreadBase::ThreadPriority p = ThreadBase::Normal, U32 stackSize = GALACTIC_THREAD_DEFAULT_STACKSIZE) = 0;
				//Kill off any thread instances
				virtual void cleanThreads() = 0;
				//Add a work object to the pool
				virtual void addWork(Work *w) = 0;
				//Fetch the next task.
				virtual Work *fetchNextTask(WorkerThread *toPool) = 0;
				//Remove a work object from the pool
				virtual bool removeWork(Work *w) = 0;
		};

		/*
		MutexLock: A useful class to "lock" aspects of a class to be off limits to other threads while execution is in process in the current thread.
		*/
		class MutexLock {
			public:
				/* Constructor / Destructor */
				//Creation Constructor
				MutexLock(PlatformCriticalSection *cs);
				//Destructor
				~MutexLock();

			private:
				/* Private (Blocked) Constructors / Destructors */
				//Default Constructor 
				MutexLock();
				//Copy Constructor
				MutexLock(const MutexLock &);

				/* Private (Blocked) Operators */
				//Block the assignment operator
				MutexLock& operator=(const MutexLock &) {
					return *this;
				}

				/* Private Class Members */
				//The critical section object used to perform the lock
				PlatformCriticalSection *cSec;
		};

		/*
		WorkPool: The primary thread management class in the engine. This class is responsible for storing lists of various events, threads, and instanced 
		 objects that use the threading system throughout the engine.
		*/
		class WorkPool : public WorkPoolBase {
			public:
				/* Constructor / Destructor */
				//Constructor
				WorkPool();
				//Destructor
				virtual ~WorkPool() { }

				/* Public Class Methods */
				//Create the thread pool with the specified number of threads and properties
				virtual bool createWithAmount(U32 amountOfThreads, ThreadBase::ThreadPriority p = ThreadBase::Normal, U32 stackSize = GALACTIC_THREAD_DEFAULT_STACKSIZE);
				//Kill off any thread instances
				virtual void cleanThreads();
				//Add a work object to the pool
				virtual void addWork(Work *w);
				//Fetch the next task.
				virtual Work *fetchNextTask(WorkerThread *toPool);
				//Remove a work object from the pool
				virtual bool removeWork(Work *w);

			protected:
				/* Protected Class Members */
				//The critical section object attached to this pool.
				PlatformCriticalSection *cSec;
				//The destruction process has begun
				bool isBeingDeleted;
				//List of all of the thread objects being stored
				DynArray<WorkerThread *> allThreadObjects;
				//List of all of the work that needs to be done.
				DynArray<Work *> jobsToDo;
				//List of available threads to perform those jobsToDo
				DynArray<WorkerThread *> openWorkerThreads;
		};

	};

};

#endif //GALACTIC_THREADTASKS