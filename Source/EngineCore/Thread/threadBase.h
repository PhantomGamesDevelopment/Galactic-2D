/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* threadBase.h
*
* Defines standardized threading classes used throughout the engine.
**/

#ifndef GALACTIC_THREADBASE
#define GALACTIC_THREADBASE

namespace Galactic {

	namespace Core {

		/*
		ThreadBase: This class sets up some common properties and settings used by all thread classes.
		*/
		class ThreadBase {
			public:
				/* Public Class Members */
				//ThreadPriority: Declares the level of priority the specified thread has to the platform
				enum ThreadPriority {
					//Lowest: Declare the thread to have the lowest priority in the system
					Lowest,
					//Low: Declare the thread to have a low priority in the system
					Low,
					//Normal: Declare the thread to have standard priority in the system
					Normal,
					//High: Declare the thread to have high priority in the system
					High,
					//Highest: Declare the thread to have the highest priority in the system
					Highest,
					//Note: While Realtime is also a standard thread priority level, we don't actually need it in the engine, so it's ignored.
				};
		};

		/*
		Event: A basic executable event that runs each time a thread accesses this class
		*/
		class Event : public ThreadBase {
			public:
				/* Constructor / Destructor */
				//Destructor
				virtual ~Event() {}
				/* Public Class Methods */
				//init(): initialize the event
				virtual bool init(bool manualReset = false) = 0;
				//reset(): reset the event state to prior to execution
				virtual void reset() = 0;
				//fire(): triggers the event and it's representative code.
				virtual void fire() = 0;
				//wait(): hold the execution of the event until the stated amount of MS has passed, passing no variable sets the event to wait infinitely
				virtual bool wait(U32 timeInMS = ((U32)0xffffffff)) = 0;
		};

		/*
		EventPool: A special container class instance that holds all of the Events queued in the engine
		*/
		class EventPool {
			public:
				/* Public Class Methods */
				//Fetch the managedSingleton instance of this class
				static EventPool &fetchInstance();
				//Fetch the 'last' event from the pool
				Event *fetchFromPool();
				//Return an event to the pool
				void returnToPool(Event *e);

			private:
				/* Private Class Members */
				//The list of events stored in the engine
				DynArray<Event *>ePool;
		};

		/*
		SingleEvent: A special class that can scope an event to handle single-fire actions when necessary
		*/
		class SingleEvent : public ThreadBase {
			public:
				/* Constructor / Destructor */
				//Default Constructor
				SingleEvent();
				//Destructor
				~SingleEvent();

				/* Public Class Methods */
				//Fetch our event object
				Event *fetch();
				//Fire our event off
				void fire();

			protected:
				/* Protected Class Methods */
				//Fetch the event from the pool
				static Event *fetchFromPool();
				//Return the event to the pool
				static void returnToPool(Event *e);

			private:
				/* Private Class Members */
				//The stored event on this class
				Event *storedEvent;

		};

		/*
		ObjectThread: A special thread class that creates an arbitrary object that can perform operations like a regular object class, but
		also has full threading capabilties.
		*/
		class ObjectThread : public ThreadBase {
			public:
				/* Constructor / Destructor */
				//Destructor
				virtual ~ObjectThread();
				/* Public Class Methods */
				//init(): initialize the object class, returns true on success
				virtual bool init();
				//run(): called when the thread executes it's code on this object, returns a numerical code value
				virtual U32 run() = 0;
				//hold(): call this method to cancel the execution of the thread process
				virtual void hold();
				//stop(): contextual method called to perform cleanup operations on the thread once it is terminated
				virtual void stop();
				//fetchNMT(): special override method to fetch the similar thread from the NMT manager in the event the platform is single threaded.
				virtual class SingleThreadedObjThread *fetchNMT();
		};

		/*
		ContinualThread: The main threading class of the engine, places all of the common threading concepts and methods into one easy
		to deploy and use class.
		*/
		class ContinualThread : public ThreadBase {
			public:
				/* Constructor / Destructor */
				//Destructor
				virtual ~ContinualThread();

				/* Public Class Methods */
				//init(): create a Continual Thread instance
				static ContinualThread *init(UTF16 name, ObjectThread *refObjThrd, bool delObjThrd_exit = false, bool delSelf_exit = false, U64 stackSize = 0, ThreadPriority p = Normal, U64 affinityMask = 0);
				//hold(): orders the thread to hold execution
				virtual void hold() = 0;
				//resume(): orders the thread to resume execution
				virtual void resume() = 0;
				//kill(): deletes the thread, you can specify whether or not the thread should wait to die
				virtual void kill(bool waitForCompletion = false) = 0;
				//getThreadID(): returns the thread's ID
				virtual U32 getThreadID() = 0;
				//getThreadName(): returns the thread's name
				virtual String getThreadName() = 0;
				//setPriority(): set the priority of the thread
				virtual void setPriority(ThreadPriority newPriority) = 0;
				//setAffinityMask(): set the affinity mask of the thread
				virtual void setAffinityMask(U64 newMask) = 0;
				//waitForCompletion(): Hold the calling function/method until the thread is complete
				virtual void waitForCompletion() = 0;
				//Returns a delegate for thread destruction
				BasicMulticastDelegate &onDestroyed();

			protected:
				/* Protected Class Methods */
				//create(): Internally create a continualThread object with the specified params
				virtual bool create(UTF16 name, ObjectThread *refObjThrd, bool delObjThrd_exit = false, bool delSelf_exit = false, U64 stackSize = 0, ThreadPriority p = Normal, U64 affinityMask = 0) = 0;
				//onCreated(): Simple internal callback
				virtual bool onCreated() = 0;

				/* Protected Class Members */
				//Stored delegate method for the onDestroyed() callback
				BasicMulticastDelegate onThreadDestroyedDelegate;
		};

		/*
		threadRegistry: A singleton instance that stores all of the ContinualThread instances in a simple to use and access map that uses the direct
		 instances as well as a provided ID.
		*/
		class threadRegistry {
			public:
				/* Public Class Methods */
				//fetch the thread registry singleton instance
				static threadRegistry &fetchInstance();
				//add(): Add thread to registry
				void add(U32 id, ContinualThread *t);
				//remove(): Remove a thread from the registry based on ID
				void remove(U32 id);
				//fetch(): Fetch the specified thread based on it's ID
				ContinualThread *fetch(U32 id);
				//count(): Get the number of threads in the registry
				S32 count();
				//lock(): lock the current thread
				void lock();
				//unlock(): unlock the current thread
				void unlock();
				//reset(): reset the updated flag
				void reset();
				//isUpdated(): check if the registry is updated
				bool isUpdated();

			private:
				/* Private Class Members */
				//The internal thread registry
				Map<U32, ContinualThread *> tRegistry;
				//The attached critical section object
				PlatformCriticalSection cSec;
				//Flag for the status of the registry
				bool updated;
		};

	};

};

#endif //GALACTIC_THREADBASE