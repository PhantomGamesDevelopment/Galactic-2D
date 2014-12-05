/**
* Galactic 2D
* Source/EngineCore/Thread/pThreadCriticalSection.h
* Defines the mutex locking classes for the PThread instances
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

//This file should only if PThread == 1, but we throw this in here, just in case ;)
#if GALACTIC_USE_PTHREAD == 1

	#ifndef GALACTIC_PT_CRITICALSECTION
	#define GALACTIC_PT_CRITICALSECTION

	#include <pthread.h>
	#include <errno.h>

	namespace Galactic {

		namespace Core {

			/*
			PlatformCriticalSection: Implements a mutex locking module for all platforms that use pThread. 
			 WARNING: Please be mindful that any methods you add here MUST also have a Windows equivalent in 
			 Platform/Windows/WinCriticalSection.h
			*/
			class PlatformCriticalSection {
				public:
					/* Constructor / Destructor */
					//Default Constructor
					FINLINE PlatformCriticalSection() {
						pthread_mutexattr_t attrb;
						pthread_mutexattr_init(&attrb);
						pthread_mutexattr_settype(&attrb, PTHREAD_MUTEX_RECURSIVE);
						pthread_mutex_init(&cSec, &attrb);
					}

					//Destructor
					FINLINE ~PlatformCriticalSection() {
						pthread_mutex_destroy(&cSec);
					}

					/* Public Class Methods */
					//Lock
					FINLINE void lock() {
						pthread_mutex_lock(&cSec);
					}

					//Unlock
					FINLINE void unlock() {
						pthread_mutex_unlock(&cSec);
					}
				
				private:
					/* Private Class Members */
					//The Critical Section Object
					pthread_mutex_t cSec;
			};

		};

	};

	#endif //GALACTIC_PT_CRITICALSECTION

#endif