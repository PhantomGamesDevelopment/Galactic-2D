/**
* Galactic 2D
* Source/EngineCore/Thread/singleThreadBase.h
* Defines engine threading classes to be used in single-threaded mode
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

#ifndef GALACTIC_SINGLETHREADBASE
#define GALACTIC_SINGLETHREADBASE

namespace Galactic {

	namespace Core {

		/*
		SingleThreadedEvent: When multi-threading is disabled, use this special version of Event.
		*/
		class SingleThreadedEvent : public Event {
			public:
				/* Constructor / Destructor */
				//Default Constructor
				SingleThreadedEvent();
				/* Public Class Methods */
				//init(): initialize the event
				virtual bool init(bool manualReset = false);
				//reset(): reset the event state to prior to execution
				virtual void reset();
				//fire(): triggers the event and it's representative code.
				virtual void fire();
				//wait(): hold the execution of the event until the stated amount of MS has passed, passing no variable sets the event to wait infinitely
				virtual bool wait(U32 timeInMS = ((U32)0xffffffff));

			private:
				/* Private Class Members */
				//Has this event been fired off?
				bool hasFired;
				//Should this event reset manually (true) or automatically (false)
				bool shouldResetManually;
		};

		/*
		SingleThreadedObjThread: When multi-threading is disabled, this class runs as the equivalent of ObjectThread. Be cautious when reading this code, it
		is in fact NOT SUPPOSED to inherit ObjectThread, as this capability is mainly disabled when using Single-Threaded mode. All of the features usually
		ran by ObjectThread are handled by SingleThreadedContinualThread in ST mode.
		*/
		class SingleThreadedObjThread {
			public:
				/* Constructor / Destructor */
				//Destructor
				virtual ~SingleThreadedObjThread() { }

				/* Public Class Methods */
				//Called each time the thread is parsed (Called once per instance of FrameTicker::tick())
				virtual void run() = 0;
		};

		/*
		SingleThreadedContinualThread: When multi-threading is disabled, this class runs as the equivalent of ContinualThread. For engine instances running in
		single-threaded mode, this is sort of the "primary" class for threading in the engine, handling most, if not all of the threading tasks.
		*/
		class SingleThreadedContinualThread : public ContinualThread {
			public:
				/* Constructor / Destructor */
				//Default Constructor
				SingleThreadedContinualThread();
				//Destructor
				virtual ~SingleThreadedContinualThread();

				/* Public Class Methods */
				//Create an instance of the thread
				virtual bool create(UTF16 name, ObjectThread *refObjThrd, bool delObjThrd_exit = false, bool delSelf_exit = false, U64 stackSize = 0, ThreadPriority p = Normal, U64 affinityMask = 0);
				//Run the thread and it's relevant task (Called once per instance of FrameTicker::tick())
				void run();
				//hold(): orders the thread to hold execution
				virtual void hold();
				//resume(): orders the thread to resume execution
				virtual void resume();
				//kill(): deletes the thread, you can specify whether or not the thread should wait to die
				virtual bool kill(bool waitForCompletion = false);
				//getThreadID(): returns the thread's ID
				virtual U32 getThreadID();
				//getThreadName(): returns the thread's name
				virtual String getThreadName();
				//setPriority(): set the priority of the thread
				virtual void setPriority(ThreadPriority newPriority);
				//setAffinityMask(): set the affinity mask of the thread
				virtual void setAffinityMask(U64 newMask);
				//waitForCompletion(): Hold the calling function/method until the thread is complete
				virtual void waitForCompletion();
				//onCreated(): Simple internal callback
				virtual bool onCreated();

			private:
				/* Private Class Members */
				//The name of the thread
				String threadName;
				//The thread's identification number
				U32 threadID;
				//The object thread instance attached to this thread (if any)
				SingleThreadedObjThread *objThread;
				//Is the thread currently beind held?
				bool onHold;
				//Should the thread delete itself upon completion?
				bool shouldDeleteSelf;
				//Should the thread delete the associated object thread when destroyed (Treat this instance as a strongReference)?
				bool shouldDeleteObjThread;
				//For single-threaded threads, we start the identification number "really really" high (2e16 - 1) for differentiation
				static U32 startIDAt;
		};

		/*
		SingleThreadedThreadManager: The control class for the list of threads when multi-threading is disabled in the engine.
		*/
		class SingleThreadedThreadManager {
			public:
				/* Public Class Methods */
				//Fetch the managedSingleton instance of the thread manager
				static SingleThreadedThreadManager &fetchInstance();
				//Send a run() event to all attached thread instances
				void run();
				//Add a thread instance to the manager
				void add(SingleThreadedContinualThread *t);
				//Remove a thread instance from the manager
				void remove(SingleThreadedContinualThread *t);

			private:
				/* Private Class Members */
				//The list containing the thread instances
				DynArray<SingleThreadedContinualThread *> threadInstances;
		};

	};

};

#endif //GALACTIC_SINGLETHREADBASE