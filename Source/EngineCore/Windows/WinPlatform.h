/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* WinPlatform.h
*
* Defines the PlatformProcess, Semaphore, PlatformHandle, and BinaryVersion classes for the Windows Platform
**/

#ifdef GALACTIC_WINDOWS

	#ifndef GALACTIC_PLATFORM_WINDOWS_PLATFORMPROCESS
	#define GALACTIC_PLATFORM_WINDOWS_PLATFORMPROCESS

	namespace Galactic {

		namespace Core {
			
			/*
			PlatformHandle: Windows version of the templated HANDLE class.
			*/
			class PlatformHandle : public processHandle<HANDLE, NULL> {
				public:
					/* Constructor / Destructor */
					//Default Constructor
					FINLINE PlatformHandle() : processHandle() { }
					//Explicit Creation Constructor
					FINLINE explicit PlatformHandle(hType inHandle) : processHandle(inHandle) { }

					/* Public Class Methods */
					//Close the handle object
					FINLINE bool close() {
						if(valid()) {
							::CloseHandle(Handle);
							reset();
							return true;
						}
						return false;
					}
			};

			/*
			PlatformProcess: Declares a set of Windows platform specific processing methods.
			*/
			class PlatformProcess : public GenericPlatformProcess {

			};

		};

	};

	//Now that we have our threading stuff, load up the CriticalSection class. (This could potentially be placed in loadWindows.h, but for now, this is fine)
	#include "WinCriticalSection.h"

	#endif //GALACTIC_PLATFORM_WINDOWS_PLATFORMPROCESS

#endif //GALACTIC_WINDOWS