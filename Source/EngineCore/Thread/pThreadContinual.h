/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* pThreadContinual.h
*
* Declares the continual thread class for PThread instances
**/

//This file should only if PThread == 1, but we throw this in here, just in case ;)
#if GALACTIC_USE_PTHREAD == 1

	#ifndef GALACTIC_PT_CONTINUALTHREAD
	#define GALACTIC_PT_CONTINUALTHREAD

		#include <pthread.h>
		//Note: We need to define a special case of NULL for linux platforms...
		#ifdef GALACTIC_LINUX
			#define PT_NULL -1
		#else
			#define PT_NULL NULL
		#endif

		namespace Galactic {

			namespace Core {

				class PContinualThread : public ContinualThread {
					/* Typedefs */
					//The entry point (function callback) for the thread instance.
					typedef any (*entryPoint)(any argument);

					public:
						/* Constructor / Destructor */
						//Default Constructor
						PContinualThread();
						//Destructor
						~PContinualThread();

						/* Public Class Methods */
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

					protected:
						/* Protected Class Methods */
						//create(): Internally create a continualThread object with the specified params
						virtual bool create(UTF16 name, ObjectThread *refObjThrd, bool delObjThrd_exit = false, bool delSelf_exit = false, U64 stackSize = 0, ThreadPriority p = Normal, U64 affinityMask = 0);
						//onCreated(): Simple internal callback
						virtual bool onCreated();
						//Thread entry run function
						U32 run();
						//Thread entry point call, this is the standard C++ syntax for this.
						static any STDCALL _threadProcHandle(any thisInst);
						//little insertion area for code to be executed prior to running the thread.
						virtual void preRun();
						//little insertion area for code to be executed after the thread runs.
						virtual void postRun();
						//Fetch the entry point instance for this thread
						virtual entryPoint fetchEntryPoint();
						//Update the stack size on the thread
						virtual U32 updateThreadStackSize(U32 newSize);
						//Fetch the platform specific default stack-size...
						virtual U32 fetchDefaultStackSize();
						//Initialize the thread with the specified params
						bool init_internal(pthread_t *threadHandle, U32 newStackSize, entryPoint threadEntryPt, any arg);
						//Convert our thread priority names to a format accepted by PThread
						virtual S32 convPriorityToPTFormat(ThreadPriority v);
						//Apply the priority to the thread inst
						virtual void setPriority_internal(pthread_t thread, ThreadPriority newPriority);

						/* Protected Class Members */
						//The thread instance
						pthread_t threadInst;
						//The threaded object instance attached to this thread.
						ObjectThread *objThread;
						//This is a special event to validate that we called the parent init() method before proceeding with executing.
						Event *initValidation;
						//This is a special event, which runs after initValidation to confirm that create() is cakked before proceeding with execution.
						Event *createValidation;
						//The ID # of this thread
						U32 threadID;
						//The name assigned to this thread
						String threadName;
						//Is this thread currently running?
						volatile bool isRunning;
						//The thread priority in engine terms on this thread (used for backwards compatibility with pThread)
						ThreadPriority enginePriority;
						//Should the thread delete itself upon completion?
						bool shouldDeleteSelf;
						//Should the thread delete the associated object thread when destroyed (Treat this instance as a strongReference)?
						bool shouldDeleteObjThread;
						//This is a thread-safe counter instance used to track a flag that this thread is ready to be deleted.
						TSCounter tsSelfDeleteCtr;
				};

			};

		};

	#endif //GALACTIC_PT_CONTINUALTHREAD

#endif //GALACTIC_USE_PTHREAD