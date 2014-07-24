/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* WinCriticalSection.h
*
* Loads the critical section locking (mutex) module for Windows
**/

#ifdef GALACTIC_WINDOWS

	#ifndef PLATFORM_WINDOWS_CRITICALSECTION
	#define PLATFORM_WINDOWS_CRITICALSECTION

	namespace Galactic {

		namespace Core {
		
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

	#endif //PLATFORM_WINDOWS_CRITICALSECTION

#endif //GALACTIC_WINDOWS