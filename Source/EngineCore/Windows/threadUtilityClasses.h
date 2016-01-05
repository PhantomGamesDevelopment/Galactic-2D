/**
* Galactic 2D
* Source/EngineCore/Windows/threadUtilityClasses.h
* Defines platform specific thread helper classes
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

#ifdef GALACTIC_WINDOWS

	#ifndef GALACTIC_PLATFORM_WINDOWS_THREADCLASSES
	#define GALACTIC_PLATFORM_WINDOWS_THREADCLASSES

	namespace Galactic {

		namespace Core {
			
			/*
			PlatformEvent: A Windows based wrapper for the generic Event threading class
			*/
			class PlatformEvent : public Event {
				public:
					/* Public Class Methods */
					//Default Constructor
					PlatformEvent() : eventObj(NULL) { }

					//Default Destructor
					virtual ~PlatformEvent() { 
						if (eventObj != NULL) {
							CloseHandle(eventObj);
						}
					}

					//init(): initialize the event
					virtual bool init(bool manualReset = false) {
						eventObj = CreateEventW(NULL, manualReset, false, NULL);
						return eventObj != NULL;
					}

					//reset(): reset the event state to prior to execution
					virtual void reset() {
						if (!eventObj) {
							GC_Error("PlatformEvent::reset(): NULL event object, unable to reset");
							return;
						}
						ResetEvent(eventObj);
					}

					//fire(): triggers the event and it's representative code.
					virtual void fire() {
						if (!eventObj) {
							GC_Error("PlatformEvent::fire(): NULL event object, unable to fire");
							return;
						}
						SetEvent(eventObj);
					}

					//wait(): hold the execution of the event until the stated amount of MS has passed, passing no variable sets the event to wait infinitely
					virtual bool wait(U32 timeInMS = ((U32)0xffffffff));

				private:
					/* Private Class Members */
					//The event handle object
					HANDLE eventObj;
			};

			/*
			PlatformContinualThread: A Windows based wrapper for the ContinualThread class
			*/
			class PlatformContinualThread : public ContinualThread {
				public:
					/* Public Class Methods */
					//Default Constructor
					PlatformContinualThread() :
						threadObj(NULL),
						objThread(NULL),
						initValidation(NULL),
						createValidation(NULL),
						threadID(0),
						threadAffinityMask(0),
						threadName(),
						enginePriority(Normal),
						shouldDeleteSelf(false),
						shouldDeleteObjThread(false),
						tsSelfDeleteCtr(0) { }

					//Destructor
					~PlatformContinualThread() {
						if (threadObj != NULL) {
							//If there's a thread running, stop it dead.
							kill(true);
						}
						//Cleanup tasks
						threadRegistry::fetchInstance().remove(threadID);
						SendToPitsOfHell(createValidation);
					}

					//Pause the running of this thread instance
					virtual void hold() {
						if (threadObj) {
							SuspendThread(threadObj);
						}
					}

					//Resume running of a held thread instance
					virtual void resume() {
						if (threadObj) {
							ResumeThread(threadObj);
						}
					}

					//Kill the thread instance
					virtual bool kill(bool waitForCompletion = false) {
						if (!threadObj) {
							GC_Error("PlatformContinualThread::kill(): Cannot perform a kill operation on a non-initialized thread instance, halting.");
							return false;
						}
						//Check for the object thread instance, and stop it.
						if (objThread) {
							objThread->stop();
						}
						//Do we need to wait?
						if (waitForCompletion) {
							//Important! Thread instances can possibly be mutex locked by other threads, trying to terminate under this condition
							// would cause a dead-lock in the code instance due to a sych-error. To avoid this from happening, we order this code
							// to indefinitely wait for completion before terminating the thread instance.
							WaitForSingleObject(threadObj, INFINITE);
						}
						//Clean up, and return
						CloseHandle(threadObj);
						threadObj = NULL;
						if (objThread && shouldDeleteObjThread) {
							SendToHell(objThread);
						}
						if (shouldDeleteSelf) {
							delete this;
						}
						return true;
					}

					//Fetch the ID of this thread
					virtual U32 getThreadID() {
						return threadID;
					}

					//Fetch the name of this thread
					virtual String getThreadName() {
						return threadName;
					}

					//Set the priority level of this thread instance
					virtual void setPriority(ThreadPriority newPriority) {
						if (enginePriority != newPriority) {
							S32 nPriority = (newPriority == Lowest ? THREAD_PRIORITY_LOWEST : 
								             newPriority == Low ? THREAD_PRIORITY_BELOW_NORMAL :
											 newPriority == High ? THREAD_PRIORITY_ABOVE_NORMAL :
											 newPriority == Highest ? THREAD_PRIORITY_HIGHEST :
											 THREAD_PRIORITY_NORMAL);
							::SetThreadPriority(threadObj, nPriority);
							enginePriority = newPriority;
						}
					}

					//Set the affinity mask for this thread instance
					virtual void setAffinityMask(U64 newMask) {
						::SetThreadAffinityMask(threadObj, (::DWORD_PTR)newMask);
					}

					//Order the thread instance to be placed on waiting until it is complete
					virtual void waitForCompletion() {
						WaitForSingleObject(threadObj, INFINITE);
					}

				protected:
					/* Protected Class Methods */
					//Create a ContinualThread instance internally
					virtual bool create(UTF16 name, ObjectThread *refObjThrd, bool delObjThrd_exit = false, bool delSelf_exit = false, U64 stackSize = 0, ThreadPriority p = Normal, U64 affinityMask = 0) {
						if (!refObjThrd) {
							GC_Error("PlatformContinaulThread::creeate(): Cannot call this method without a referenced object thread instance.");
							return false;
						}
						//Apply properties and initialize the creation validation events
						objThread = refObjThrd;
						shouldDeleteObjThread = delObjThrd_exit;
						shouldDeleteSelf = delSelf_exit;
						threadAffinityMask = affinityMask;
						initValidation = PlatformProcess::createEvent(true);
						createValidation = PlatformProcess::createEvent(true);
						//Establish the thread using windows thread libs... clean up if we fail
						threadObj = CreateThread(NULL, stackSize, __threadProc, this, STACK_SIZE_PARAM_IS_A_RESERVATION, (::DWORD *)&threadID);
						if (!threadObj) {
							if (delObjThrd_exit) {
								SendToPitsOfHell(refObjThrd);
							}
							objThread = NULL;
						}
						else {
							initValidation->wait(INFINITE);
							threadName = name ? name : String("Unnamed Thread");
							setThreadName(threadID, threadName);
							setPriority(p);
						}
						//Final cleaning...
						SendToHell(initValidation);
						return threadObj != NULL;
					}

					//Quick callback function parsed after the thread is created
					virtual bool onCreated() {
						cbol done = FBOOL(tsSelfDeleteCtr.fetch());
						createValidation->fire();
						return done;
					}

				private:
					/* Private Class Methods */
					//Thread entry point function
					static ::DWORD __stdcall __threadProc(LPVOID thisInst) {
						if (thisInst != NULL) {
							return ((PlatformContinualThread*)thisInst)->run();
						}
						return NULL; 
					}

					//Run this instance
					U32 run() {
						U32 exitCode = 1;
						if (!objThread) {
							GC_Error("PlatformContinualThread::run(): Can't run a thread without an object thread instance, stopping.");
							return exitCode;
						}
						//Initialize and run the object thread instance. If it fails, trigger the init validation for error purposes
						if (objThread->init()) {
							initValidation->fire();
							exitCode = objThread->run();
							objThread->stop();
						}
						else {
							initValidation->fire();
						}
						//Once we're done, let's clean stuff up.
						if (shouldDeleteObjThread) {
							SendToHell(objThread);
						}
						if (shouldDeleteSelf) {
							tsSelfDeleteCtr++;
							createValidation->wait();
							CloseHandle(threadObj);
							threadObj = NULL;
							delete this;
						}
						return exitCode;
					}

					//Set the thread name
					static void setThreadName(U32 tID, String newName) {
						//Windows uses a very specific format for naming threads, and they're only visible for debugging purposes
						struct THREAD_INFO {
							//Type Flag, for thread name setting this must be 0x1000
							U32 dwType;
							//The name that we're going to set
							LPCSTR szName;
							//The Thread's ID number
							U32 dwThreadID;
							//Flags that are currently not being used, potential for future versions of windows?
							U32 dwFlags;
						};
						//Create our naming info...
						THREAD_INFO info;
						info.dwType = 0x1000;
						info.szName = (LPCSTR)newName.c_str();
						info.dwThreadID = tID;
						info.dwFlags = 0;
						//Try to set the name... The code to use for this is provided by http://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx
						__try {
							::DWORD nNumArgs = sizeof(THREAD_INFO) / sizeof(ULONG_PTR);
							const ULONG_PTR *nArgs = ((ULONG_PTR *)&info);
							RaiseException(0x406D1388, 0, nNumArgs, nArgs);
						}
						__except(EXCEPTION_EXECUTE_HANDLER) {
							//Failed... do nothing.
						}
					}

					/* Private Class Members */
					//The thread handle object
					HANDLE threadObj;
					//The threaded object instance attached to this thread.
					ObjectThread *objThread;
					//This is a special event to validate that we called the parent init() method before proceeding with executing.
					Event *initValidation;
					//This is a special event, which runs after initValidation to confirm that create() is cakked before proceeding with execution.
					Event *createValidation;
					//The ID # of this thread
					U32 threadID;
					//The affinity mask of this thread
					U64 threadAffinityMask;
					//The name assigned to this thread
					String threadName;
					//The thread priority in engine terms on this thread (used for backwards compatibility with pThread)
					ThreadPriority enginePriority;
					//Should the thread delete itself upon completion?
					bool shouldDeleteSelf;
					//Should the thread delete the associated object thread when destroyed (Treat this instance as a strongReference)?
					bool shouldDeleteObjThread;
					//This is a thread-safe counter instance used to track a flag that this thread is ready to be deleted.
					TSCounter tsSelfDeleteCtr;
			};

			/*
			PlatformCriticalSection: Implements a mutex locking module for the Windows platform
			WARNING: Please be mindful that any methods you add here MUST also have a Generic equivalent in
			Platform/Generic/Thread/pThreadCriticalSection.h
			*/
			class PlatformCriticalSection {
				public:
					/* Constructor / Destructor */
					//Default Constructor
					FINLINE PlatformCriticalSection() {
						InitializeCriticalSection(&cSec);
						SetCriticalSectionSpinCount(&cSec, 4500);
					}

					//Destructor
					FINLINE ~PlatformCriticalSection() {
						DeleteCriticalSection(&cSec);
					}

					/* Public Class Methods */
					//Lock
					FINLINE void lock() {
						if (!TryEnterCriticalSection(&cSec)) {
							EnterCriticalSection(&cSec);
						}
					}

					//Unlock
					FINLINE void unlock() {
						LeaveCriticalSection(&cSec);
					}

				private:
					/* Private Class Members */
					//Critical Section Object
					CRITICAL_SECTION cSec;
			};

		};

	};

	#endif //GALACTIC_PLATFORM_WINDOWS_THREADCLASSES

#endif //GALACTIC_WINDOWS