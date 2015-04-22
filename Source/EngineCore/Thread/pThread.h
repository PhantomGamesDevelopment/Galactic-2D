/**
* Galactic 2D
* Source/EngineCore/Thread/pThread.h
* Defines standardized threading classes for platforms that use the PThread system.
* (C) 2014-2015 Phantom Games Development - All Rights Reserved
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