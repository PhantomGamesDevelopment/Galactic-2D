/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* genericPlatform.cpp
*
* Defines methods and operations that are specific to platforms, in this case, these are templates to other platforms for easy declaration
**/

#include "../engineCore.h"
#if GALACTIC_USE_SYS_TIME == 1
	#include <unistd.h>
	#include <sched.h>
#endif

namespace Galactic {

	namespace Core {

		//Definition for affinityInformation
		// Note: Aside from NULL, which is a special case, threads that require higher affinities should be declared with lower mask values.
		GenericPlatformProcess::AffinityInfo GenericPlatformProcess::affinityInformation[GALACTIC_AFFINITY_MANAGER_THREADCOUNT] = {
			//Main Thread
			{ "MainThread", CreateLevel1Mask(0) },
			//Worker Threads
			{ "WorkerThread", CreateLevel1Mask(4) },
			//Screen-Saver Blocker
			{ "ScreensaverBlocker", CreateLevel1Mask(4) },

			//This one's always last...
			{ NULL, 0 },
		};

		/* Semaphore Class */
		GenericPlatformProcess::Semaphore::Semaphore(const String &name) {
			#pragma warning( push )
			#pragma warning( disable : 4996 )
				//strcpy_s is not cross-platform safe, but strcpy is and unlike silly MSVS says, this function is not 'depricated'.
				strcpy(semName, name.c_str());
			#pragma warning( pop )
		}

		/* GenericPlatformProcess Class */
		U32 GenericPlatformProcess::getProcID() {
			return 0;
		}

		UTF16 GenericPlatformProcess::getUserDir() {
			GC_Warn("getUserDir(): This method is not implemented on the generic platform.");
			return "";
		}

		UTF16 GenericPlatformProcess::getAppSetDir() {
			GC_Warn("getAppSetDir(): This method is not implemented on the generic platform.");
			return "";
		}

		UTF16 GenericPlatformProcess::getUserSetDir() {
			GC_Warn("getUserSetDir(): This method is not implemented on the generic platform.");
			return "";
		}

		void GenericPlatformProcess::setAffinityMask(U64 mask) {
			GC_Warn("setAffinityMask(): This method is not implemented on the generic platform.");
		}

		UTF16 GenericPlatformProcess::userName() {
			GC_Warn("userName(): This method is not implemented on the generic platform.");
			return "GenericUser";
		}

		UTF16 GenericPlatformProcess::compName() {
			GC_Warn("compName(): This method is not implemented on the generic platform.");
			return "GenericComputer";
		}

		UTF16 GenericPlatformProcess::getExeName(bool includeExtension) {
			GC_Warn("getExeName(): This method is not implemented on the generic platform.");
			return "";
		}

		any GenericPlatformProcess::getLibHandle(UTF16 filePath) {
			GC_Warn("getLibHandle(): This method is not implemented on the generic platform.");
			return NULL;
		}

		void GenericPlatformProcess::freeLibHandle(any handle) {
			GC_Warn("freeLibHandle(): This method is not implemented on the generic platform.");
		}

		any GenericPlatformProcess::fetchFunction(any handle, UTF16 procName) {
			GC_Warn("fetchFunction(): This method is not implemented on the generic platform.");
			return NULL;
		}

		UTF16 GenericPlatformProcess::getLibExtension() {
			GC_Warn("getLibExtension(): This method is not implemented on the generic platform.");
			return "";
		}

		BinaryVersion GenericPlatformProcess::fetchVersion(UTF16 filePath) {
			GC_Warn("fetchVersion(): This method is not implemented on the generic platform.");
			return BinaryVersion(0, 0, 0, 0);
		}

		PlatformHandle GenericPlatformProcess::launchProcess(UTF16 path, UTF16 args, bool newWindow, bool minimized, bool hiddenProcess, U32 forceID, S32 threadPriority, UTF16 procWD) {
			GC_Warn("launchProcess(): This method is not implemented on the generic platform.");
			return PlatformHandle();
		}

		bool GenericPlatformProcess::launchProcess(UTF16 path, UTF16 args, S32 *retCodePtr, String *stdOut, String *stdErr) {
			GC_Warn("launchProcess(): This method is not implemented on the generic platform.");
			return false;
		}

		bool GenericPlatformProcess::launchAdminProcess(UTF16 path, UTF16 args, S32 *retCodePtr) {
			return PlatformProcess::launchProcess(path, args, retCodePtr);
		}

		bool GenericPlatformProcess::activeProc(PlatformHandle &proc) {
			GC_Warn("activeProc(PlatformHandle &): This method is not implemented on the generic platform.");
			return false;
		}

		bool GenericPlatformProcess::activeProc(U32 procID) {
			GC_Warn("activeProc(U32): This method is not implemented on the generic platform.");
			return false;
		}

		bool GenericPlatformProcess::activeProc(UTF16 procName) {
			GC_Warn("activeProc(UTF16): This method is not implemented on the generic platform.");
			return false;
		}

		void GenericPlatformProcess::forceMustStop(PlatformHandle &proc) {
			GC_Warn("forceMustStop(): This method is not implemented on the generic platform.");
		}

		UTF16 GenericPlatformProcess::getProcName(U32 procID) {
			GC_Warn("getProcName(): This method is not implemented on the generic platform.");
			return "GenericProcess";
		}

		bool GenericPlatformProcess::hasFocus() {
			GC_Warn("hasFocus(): This method is not implemented on the generic platform.");
			return false;
		}

		bool GenericPlatformProcess::getReturnCode(PlatformHandle &proc, S32 *retCodePtr) {
			GC_Warn("getReturnCode(): This method is not implemented on the generic platform.");
			return false;
		}

		void GenericPlatformProcess::terminateProc(PlatformHandle &proc, bool termSubProc) {
			GC_Warn("terminateProc(): This method is not implemented on the generic platform.");
		}

		bool GenericPlatformProcess::becomeServiceProcess() {
			GC_Warn("becomeServiceProcess(): This method is not implemented on the generic platform.");
			return false;
		}

		bool GenericPlatformProcess::isMultithreaded() {
			//Note! While this bool return does control some form of multithread support in the engine, this is fully controlled by the definition
			// of GALACTIC_DISABLE_MULTITHREADING in galacticSettings.h
			return !(ProcessCommandLine::fetchInstance().hasParam("noMThreads"));
		}

		U64 GenericPlatformProcess::fetchAffinityMask(UTF16 name) {
			return U64DEF(0xffffffffffffffff);
		}

		#if GALACTIC_USE_PTHREAD == 1
			//Load in the PThread Event Class now. Different platforms use the wait() method differently, so overload it here.
			#include "../Thread/pThread.h"
			bool PEvent::wait(U32 timeInMS) {
				if(!initialized) {
					GC_Error("PEvent::wait(): Cannot call wait() on an uninitialzied event.");
					return false;
				}
				//Only proceed if this is a 'timed' wait, IE: one that isn't being canceled, or waiting infinitely...
				struct timeval cTime;
				if(timeInMS > 0 && timeInMS != ((U32)-1)) {
					gettimeofday(&cTime, NULL);
				}
				Z32 cTimeMS = (cTime.tv_usec / 1000) + timeInMS;
				//Lock the event down to only this function...
				lockMutex();
				bool success = false;
				do {
					//Run through the event to catch the conditional signal the event is currently using, we also want to make sure we're holding onto
					// this call until we're finished with the wait() method.
					if(t == Single) {
						t = None;
						success = true;
					}
					else if(t = All) {
						success = true;
					}
					else if(timeInMS != 0) {
						thrdsWaiting++;
						if(timeInMS == ((U32)-1)) {
							//Infinite...
							S32 retCode = pthread_cond_wait(&tCond, &tMutex);
							if(retCode != 0) {
								//Something went wrong...
								GC_Error("PEvent::wait(): Something went wrong in the infinite wait call.");
							}
						}
						else {
							//Timed...
							struct timespec eTime;
							struct timeval curTime, deltaTime;
							//Update the time params in case we need to run this through a second loop iteration
							gettimeofday(&curTime, NULL);
							//Calculate the difference in time...
							if (curTime->tv_usec < cTime->tv_usec) {
								S32 nsec = (cTime->tv_usec - curTime->tv_usec) / 1000000 + 1;
								cTime->tv_usec -= 1000000 * nsec;
								cTime->tv_sec += nsec;
							}
							if ((curTime->tv_usec - cTime->tv_usec) > 1000000) {
								S32 nsec = (curTime->tv_usec - cTime->tv_usec) / 1000000;
								cTime->tv_usec += 1000000 * nsec;
								cTime->tv_sec -= nsec;
							}
							deltaTime->tv_sec = curTime->tv_sec - cTime->tv_sec;
							deltaTime->tv_usec = curTime->tv_usec - cTime->tv_usec;
							X32 differenceInMS = ((deltaTime.tv_sec * 1000) + (deltaTime.tv_usec / 1000));
							//Apply the wait.
							eTime.tv_sec = cTime.tv_sec + (cTimeMS / 1000);
							eTime.tv_nsec = (cTimeMS % 1000) * 1000000;
							//Try to apply the wait...
							S32 retCode = pthread_cond_timedwait(&tCond, &tMutex, &eTime);
							if(!(retCode == 0 || retCode == ETIMEDOUT)) {
								GC_Error("PEvent::wait(): Comething went wrong in the timed wait call.");
							}
							//Update the current time params
							timeInMS = ((differenceInMS >= timeInMS) ? 0 : (timeInMS - differenceInMS));
							cTime = curTime;
						}
						thrdsWaiting--;
						if(thrdsWaiting < 0) {
							//We've got a problem...
							GC_Error("PEvent::wait(): Released more waiting threads than was assigned...");
						}
					}
				}while(!success && timeInMS != 0);
				unlockMutex();
				return success;
			}
		#endif

		Event *GenericPlatformProcess::createEvent(bool manualReset) {
			#if GALACTIC_USE_PTHREAD == 1
				Event *newEvent = NULL;
				//Test for application multi-threading...
				if (PlatformProcess::isMultithreaded()) {
					//Create a regular PThread Event Class
					newEvent = new PEvent();
				}
				else {
					//Create a Single-Threaded Event Class
					newEvent = new SingleThreadedEvent();
				}
				//Try to init the event, if it fails, kill it and return NULL...
				if (!newEvent->init(manualReset)) {
					SendToHell(newEvent);
				}
				return newEvent;
			#else
				//If we don't use PThread, then we're at the disposal of the platform's thread classes, push a warn and return NULL.
				GC_Warn("createEvent(): This method is not implemented on the generic platform.");
				return NULL;
			#endif
		}

		//Note: We load this file here because PContinualThread MUST be loaded after all of the base thread instances, but not before this function def.
		#if GALACTIC_USE_PTHREAD == 1
			#include "../Thread/pThreadContinual.h"
		#endif

		ContinualThread *GenericPlatformProcess::createContThread() {
			#if GALACTIC_USE_PTHREAD == 1
				return new PContinualThread();
			#else
				//If we don't use PThread, then we're at the disposal of the platform's thread classes, push a warn and return NULL.
				GC_Warn("createContThread(): This method is not implemented on the generic platform.");
				return NULL;
			#endif
		}

		GenericPlatformProcess::Semaphore *GenericPlatformProcess::openSemaphore(const String &name, bool create, U32 maxLocks) {
			GC_Warn("openSemaphore(): This method is not implemented on the generic platform.");
			return NULL;
		}

		bool GenericPlatformProcess::killSemaphore(GenericPlatformProcess::Semaphore *trg) {
			GC_Warn("killSemaphore(): This method is not implemented on the generic platform.");
			return false;
		}

		#if GALACTIC_USE_SYS_TIME == 1
			void GenericPlatformProcess::sleep(F64 seconds, bool sleepInfinite) {
				if(sleepInfinite) {
					pause();
				}
				else {
					//Truncate the floating point seconds time to an integer...
					X32 microSec = PlatformMath::TruncateToInteger(seconds);
					if(microSec > 0) {
						usleep(microSec);
					}
					else {
						sched_yield();
					}
				}
			}
		#endif

	};

};