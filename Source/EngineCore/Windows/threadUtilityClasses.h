/**
* Galactic 2D
* Source/EngineCore/Windows/threadUtilityClasses.h
* Defines platform specific thread helper classes
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
					U32 run();
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