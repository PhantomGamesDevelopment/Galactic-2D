/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* pThread.h
*
* Declares the event class for platforms that are running the pThread class.
**/

//This file should only if PThread == 1, but we throw this in here, just in case ;)
#if GALACTIC_USE_PTHREAD == 1

	#ifndef GALACTIC_PT_THREAD
	#define GALACTIC_PT_THREAD

	namespace Galactic {

		namespace Core {

			/*
			PEvent: A special version of Event that is ran when the PThreads module is active
			*/
			class PEvent : public Event {
				public:
					/* Constructor / Destructor */
					//Default Constructor
					PEvent();
					//Destructor
					virtual ~PEvent();
					/* Public Class Methods */
					//init(): initialize the event
					virtual bool init(bool manualReset = false);
					//reset(): reset the event state to prior to execution
					virtual void reset();
					//fire(): triggers the event and it's representative code.
					virtual void fire();
					//wait(): hold the execution of the event until the stated amount of MS has passed, passing no variable sets the event to wait infinitely
					virtual bool wait(U32 timeInMS = ((U32)-1)) override;

				private:
					/* Private Class Methods */
					//lockMutex(): lock the mutex object for this event
					FINLINE void lockMutex();
					//unlockMutex(): unlock the mutex object for this event
					FINLINE void unlockMutex();

					/* Private Class Members */
					//TriggerType: Used to keep engine platform compatibility with Win32 Threading System
					enum TriggerType {
						//None: No event was triggered
						None,
						//Single: One event was triggered
						Single,
						//All: All events were triggered
						All,
					};
					//Has the event thread been initialized?
					bool initialized;
					//Has the event been manually reset yet?
					bool manResetYet;
					//The associated mutex object for this thread
					pthread_mutex_t tMutex;
					//The associated thread condition object
					pthread_cond_t tCond;
					//The trigger type to use on this thread
					volatile typedef TriggerType t;
					//How many threads are waiting on this event object?
					volatile S32 thrdsWaiting;
			};

		};

	};

	#endif //GALACTIC_PLATFORM_GENERIC_PT_THREAD

#endif //GALACTIC_USE_PTHREAD