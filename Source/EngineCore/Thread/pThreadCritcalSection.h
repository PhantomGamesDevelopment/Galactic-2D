/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* pThreadCriticalSection.h
*
* Loads the critical section locking (mutex) module for pThread loaded classes
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