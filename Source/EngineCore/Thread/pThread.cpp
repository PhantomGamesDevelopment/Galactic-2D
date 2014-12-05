/**
* Galactic 2D
* Source/EngineCore/Thread/pThread.cpp
* Defines standardized threading classes for platforms that use the PThread system.
* (C) 2014 Phantom Games Development - All Rights Reserved
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

#if GALACTIC_USE_PTHREAD == 1

	#include "../../engineCore.h"

	namespace Galactic {

		namespace Core {

			PEvent::PEvent() {
				initialized = false;
				manResetYet = false;
				t = None;
				thrdsWaiting = 0;
			}

			PEvent::~PEvent() {
				//If the event has been initialized, we need to exit the code being ran.
				if (initialized) {
					//Start by trying to empty the thread call stack
					lockMutex();
					manResetYet = true;
					unlockMutex();
					fire();
					//Block all remaining calls to this thread.
					lockMutex();
					initialized = false;
					while (thrdsWaiting > 0) {
						//If we have threads waiting on us, they'll need to have their red flag trigger on us, so let's take care of them.
						unlockMutex();
						lockMutex();
					}
					//Lastly, clean everything up and exit.
					pthread_cond_destroy(&tCond);
					unlockMutex();
					pthread_mutex_destroy(&tMutex);
				}
			}

			bool PEvent::init(bool manualReset) {
				if (initialized) {
					GC_Error("PEvent::init(): Cannot initialize a thread that had already been initialized.");
					return false;
				}
				t = None;
				manResetYet = manualReset;
				//attempt to init the mutex
				if (pthread_mutex_init(&tMutex, NULL) == 0) {
					//Now init the condition
					if (pthread_cond_init(&tCond, NULL) == 0) {
						//We're good!
						initialized = true;
						return true;
					}
					pthread_mutex_destroy(&tMutex);
				}
				return false;
			}

			void PEvent::reset() {
				if (!initialized) {
					GC_Error("PEvent::reset(): Cannot perform a reset operation on a thread that is not initialized.");
					return;
				}
				//lock & unlock to flush the stack
				lockMutex();
				t = None;
				unlockMutex();
			}

			void PEvent::fire() {
				if (!initialized) {
					GC_Error("PEvent::fire(): Cannot fire a command on a thread that is not initialized.");
					return;
				}
				//Lock the stack and operate, then unlock.
				lockMutex();
				if (manResetYet) {
					//if we reset manually, make sure to trigger everything on this event, then confirm there's nothing.
					t = All;
					S32 execCount = pthread_cond_broadcast(&tCond);
					if (execCount != 0) {
						GC_Warn("PEvent::fire(): pthread_cond_broadcast operation has operations remaining on the stack that were not executed. [%i]", execCount);
					}
				}
				else {
					//Just one event to be fired off, take care of it now.
					t = Single;
					S32 execCount = pthread_cond_signal(&tCond);
					if (execCount != 0) {
						GC_Warn("PEvent::fire(): pthread_cond_signal operation has operations remaining on the stack that were not executed. [%i]", execCount);
					}
				}
				unlockMutex();
			}

			void PEvent::lockMutex() {
				Z32 errCode = pthread_mutex_lock(&tMutex);
				if (errCode != 0) {
					GC_Warn("PEvent::lockMutex(): Function returned an error code [%i].", errCode);
				}
			}

			void PEvent::unlockMutex() {
				Z32 errCode = pthread_mutex_unlock(&tMutex);
				if (errCode != 0) {
					GC_Warn("PEvent::unlockMutex(): Function returned an error code [%i].", errCode);
				}
			}

		};

	};

#endif //GALACTIC_USE_PTHREAD