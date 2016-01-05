/**
* Galactic 2D
* Source/EngineCore/Thread/pThreadContinual.cpp
* Defines the PContinualThread class for the actual PThread instances in the engine
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

//This file should only if PThread == 1, but we throw this in here, just in case ;)
#if GALACTIC_USE_PTHREAD == 1

	#include "../../engineCore.h"

	namespace Galactic {

		namespace Core {

			PContinualThread::PContinualThread() :
				threadInst(PT_NULL),
				objThread(NULL),
				initValidation(NULL),
				createValidation(NULL),
				threadID(0),
				isRunning(false),
				enginePriority(Normal),
				shouldDeleteSelf(false),
				shouldDeleteObjThread(false),
				tsSelfDeleteCtr(0) {
			
			}

			PContinualThread::~PContinualThread() {
				if(threadInst != PT_NULL) {
					//Stop the thread from running
					kill(true);
				}
				//Delete from the registry
				threadRegistry::fetchInstance().remove(threadID);
				SendToPitsOfHell(createValidation);
			}

			void PContinualThread::hold() {
				//ToDo: Explore option of adding a bool lock to the run() method to bypass this, this will require investigation into execution timings, etc.
				GC_Warn("PContinualThread::hold(): PThread does not support thread pause/resume.");
			}

			void PContinualThread::resume() {
				GC_Warn("PContinualThread::resume(): PThread does not support thread pause/resume.");
			}

			bool PContinualThread::kill(bool waitForCompletion) {
				//Deleting threads is always a challenge as you need to make sure it's not busy running something at the time...
				if(threadInst == PT_NULL) {
					//Don't call kill() if there is nothing to kill.
					GC_Error("PContinualThread::kill(): Cannot kill an uninitialized thread instance.");
					return false;
				}
				//Stop attached object thread.
				if(objThread) {
					objThread->stop();
				}
				//If we need to hold off on deleting this instance, then continually sleep for an infintesimally small ammount until we can delete.
				if(waitForCompletion) {
					while(isRunning) {
						//Note: This may not be the most 'optimal' route to take to wait for thread halting, but this alone blocks the infinite loop
						// lock. We should possibly investigate increasing this time by an order of magnitude for a slight performance boost...
						// Also, for a secondary note, look below at the delete self block for a kill-leak that may happen through this loop.
						PlatformProcess::sleep(0.001f);
					}
				}
				//If the object thread is still hanging around, kill it off.
				if(objThread && shouldDeleteObjThread) {
					SendToHell(objThread);
				}
				//It's never 100% 'safe' to delete a PThread instance, so just flag it "dead" by assigning it to NULL and moving on.
				threadInst = PT_NULL;
				if(shouldDeleteSelf) {
					//Note: See note below on PT deletion, also, we need to double check that this instance isn't already dead somehow because it's quite
					// possible that sometime during the above loop for isRunning(), the function may leak a kill() command out to this method and delete
					// this instance before we do so here. What I currently have here may not be 100% safe in terms of protection and may even violate a few
					// 'new' standards, but for the time being, it offers a level of application protection. A valid discussion on the manner is available 
					// here: http://stackoverflow.com/questions/1844005/checking-if-this-is-null
					if(this != NULL) {
						SendToHell(this);
					}
					else {
						GC_Error("PContinualThread::kill(): Thread kill exception leak blocked...");
						return false;
					}
				}
				return true;
			}

			U32 PContinualThread::getThreadID() {
				return threadID;
			}

			String PContinualThread::getThreadName() {
				return threadName;
			}

			void PContinualThread::setPriority(ThreadPriority newPriority) {
				if(enginePriority == newPriority) {
					//Whoa there pal, no need to update this...
					return;
				}
				enginePriority = newPriority;
				//Set the priority in terms of PT now.
				setPriority_internal(threadInst, newPriority);
			}

			void PContinualThread::setAffinityMask(U64 newMask) {
				//This is handled by the platform... so we ignore the call here...
			}

			void PContinualThread::waitForCompletion() {
				//This method basically holds off execution of anything else until the current thread is done. This should mainly be applied as a 
				// debugging tool and not touched by anything else...
				while(isRunning) {
					PlatformProcess::sleep(0.001f);
				}			
			}

			bool PContinualThread::create(UTF16 name, ObjectThread *refObjThrd, bool delObjThrd_exit, bool delSelf_exit, U64 stackSize, ThreadPriority p, U64 affinityMask) {
				if(!refObjThread) {
					GC_Error("PContinualThread::create(): Cannot send a NULL refObjThrd parameter to this method.");
					return false;
				}
				//Apply some basic params
				objThread = refObjThread;
				shouldDeleteObjThread = delObjThrd_exit;
				shouldDeleteSelf = delSelf_exit;
				threadName = name ? name : "Unnamed_Thread";
				//Create our two special event classes to ensure the thread initializes in the correct order
				initValidation = PlatformProcess::createEvent(true);
				createValidation = PlatformProcess::createEvent(true);
				//Init the thread internally
				bool didInit = init_internal(&threadInst, fetchEntryPoint(), stackSize, this);
				if(!didInit) {
					if(delObjThrd_exit) {
						SendToPitsOfHell(refObjThread);
					}
					objThread = NULL;
					return false;
				}
				//Finish up the initialization
				pthread_detach(threadInst);
				initValidation->wait();
				setPriority(p);
				setAffinityMask(affinityMask);
				//Clean up...
				SendToHell(initValidation);
				//Finished....
				return FBOOL(threadInst != PT_NULL);
			}

			bool PContinualThread::onCreated() {
				const bool threadDone = FBOOL(tsSelfDeleteCtr.fetch());
				//Trigger the create check, then tell the thread it's safe for deletion...
				createValidation->fire();
				return threadDone;
			}

			U32 PContinualThread::run() {
				if(!refObjThread) {
					//Can't do anything without an object thread to run on...
					GC_Error("PContinualThread::run(): Cannot run a thread with no object reference to run on.");
					return 0;
				}
				isRunning = true;
				U32 exitCode = 1;
				//Try to perform an init() call on the object thread instance...
				if(!refObjThread->init()) {
					//Failed, it's likely the thread itself isn't done yet, so validate that now...
					initValidation->fire();
				}
				else {
					//We're good to go, fire everything off...
					initValidation->fire();
					exitCode = refObjThread->run();
					refObjThread->stop();
				}
				//Execution is finished... Do we need to kill the obj thread?
				if(shouldDeleteObjThread) {
					SendToHell(refObjThread);
				}
				isRunning = false;
				return exitCode;
			}

			any STDCAll PContinualThread::_threadProcHandle(any thisInst) {
				//Validate the input instance...
				if(!thisInst) {
					GC_Error("PContinualThread::_threadProcHandle(): Cannot send a NULL thread instance to this method.");
					return NULL;
				}
				PContinualThread *myself = (PContinualThread*)thisInst;
				//Fetch the thread ID and store it...
				myself->threadID = PlatformThreadStorage::getIdOfCurrentThread();
				//Run it....
				myself->preRun();
				myself->run();
				myself->postRun();
				//And exit....
				pthread_exit(NULL);
				return NULL;
			}

			void PContinualThread::preRun() {
				//Basic stub function... this can be overloaded by other instances...
			}

			void PContinualThread::postRun() {
				if(shouldDeleteSelf) {
					tsSelfDeleteCtr++;
					//Check to ensure that the thread is fully "created" before deleing...
					createValidation->wait();
					//Lastly delete this instance... You'll want to see my notes in kill() regarding potential kill-leaks and how we protect it here...
					threadInst = PT_NULL;
					SendToHell(this);
				}
			}

			PContinualThread::entryPoint PContinualThread::fetchEntryPoint() {
				return _threadProcHandle;
			}

			U32 PContinualThread::updateThreadStackSize(U32 newSize) {
				//This method doesn't necessarily pass along the stack size to the thread instance, more-so just handle the proper fetching of the 
				// correct value when parsing the information through the system...
				if(newSize == 0) {
					newSize = fetchDefaultStackSize();
				}
				return newSize;
			}

			U32 PContinualThread::fetchDefaultStackSize() {
				//This function is overloaded by the platforms to set the correct information. Please see the valid definitions there for more info...
				return 0;
			}

			bool PContinualThread::init_internal(pthread_t *threadHandle, U32 newStackSize, entryPoint threadEntryPt, any arg) {
				pthread_attr_t *defaultAttributes = NULL;
				pthread_attr_t threadStackAttributes;
				//Have the platform update the stack size...
				newStackSize = updateThreadStackSize(newStackSize);
				if(newStackSize != 0) {
					//If we have a stack size to apply, do so now...
					if(pthread_attr_init(&threadStackAttributes) == 0){
						SIZE_T stackSize = (SIZE_T)newStackSize;
						if(pthread_attr_setstacksize(&threadStackAttributes, newStackSize) == 0) {
							defaultAttributes = &threadStackAttributes;
						}
					}
					//Check to ensure everything was updated.
					if(!defaultAttributes) {
						GC_Error("PContinualThread::init_internal(): Failed to apply a stack size of %d bytes.", (S32)newStackSize);
					}
				}
				//Now create the thread instance...
				X32 ptErrno = pthread_create(threadHandle, defaultAttributes, threadEntryPt, arg);
				if(defaultAttributes != NULL) {
					//Kill the att. ptr...
					pthread_attr_destroy(defaultAttributes);
				}
				bool success = (ptErrno == 0);
				if(!success) {
					GC_Error("PContinualThread::init_internal(): Failed to init a new PThread instance.");
				}
				return success;
			}

			S32 PContinualThread::convPriorityToPTFormat(ThreadPriority v) {
				//PThread has a numerical scale for thread priority where 0 is the lowest and 31 is the highest.
				switch(v) {
					case Lowest:
						return 1;
					case Low:
						return 5;
					case Normal:
						return 15;
					case High:
						return 25;
					case Highest:
						return 30;
					//case Realtime:
					//	return 31;
					default:
						GC_Error("PContinualThread::convPriorityToPTFormat(): Unknown priority instance sent to this method.");
						return 0;
				}
			}

			void PContinualThread::setPriority_internal(pthread_t thread, ThreadPriority newPriority) {
				//Init the sched_param struct, then set the priority to the thread.
				struct sched_param ptSchedParam;
				Memory::gmemset(&ptSchedParam, 0, sizeof(struct sched_param));
				ptSchedParam.sched_priority = convPriorityToPTFormat(newPriority);
				pthread_setschedparam(thread, SCHED_PR, &ptSchedParam);
			}

		};

	};

#endif //GALACTIC_USE_PTHREAD