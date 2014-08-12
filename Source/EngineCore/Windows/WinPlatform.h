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
				public:
					/*
					Semaphore: Windows definition of the GenericSemaphore class
					*/
					class Semaphore : public GenericSemaphore {
						public:
							/* Constructor / Destructor */
							//Constructor
							Semaphore(const String &name, HANDLE inObj);
							//Destructor
							virtual ~Semaphore() { }

							/* Public Class Methods */
							//acquire(): force the system to obtain the semaphore lock for the specified thread
							virtual void acquire();
							//release(): release the semaphore lock
							virtual void release();
							//tryAcquire(): Safer form of acquire, set the system to try to acquire the lock over a specified time
							virtual bool tryAcquire(U64 nsToWait);
							//fetch(): Fetch the semaphore object instance
							HANDLE fetch() { return semObj; }

						protected:
							/* Protected Class Members */
							//The actual Semaphore Object
							HANDLE semObj;
					};

					/* General Platform Processing Information */
					//Get the process ID
					static U32 getProcID();
					//Get the user directory
					static UTF16 getUserDir();
					//Get the application settings directory
					static UTF16 getAppSetDir(UTF16 append = "", bool forceUpdate = false);
					//Get the user settings directory
					static UTF16 getUserSetDir();
					//Set the process affinity mask (called on the main thread)
					static void setAffinityMask(U64 mask);
					//Get the user name
					static UTF16 userName();
					//Get the computer name
					static UTF16 compName();
					//Get the name of the executable being ran
					static UTF16 getExeName(bool includeExtension = false);

					/* Platform Specific Library Loading */
					//Load a dynamic library into a handle
					static any getLibHandle(UTF16 filePath);
					//Free a library handle
					static void freeLibHandle(any handle);
					//Fetch the specified function from the lib
					static any fetchFunction(any handle, UTF16 procName);
					//Fetch the file extension for libraries on this platform
					static UTF16 getLibExtension();
					//Fetch the version of the specified binary file (.exe, .dll, .so, etc)
					static BinaryVersion fetchVersion(UTF16 filePath);

					/* Process Functions */
					//Launch a new process with the given parameters
					static PlatformHandle launchProcess(UTF16 path, UTF16 args, bool newWindow, bool minimized, bool hiddenProcess, U32 forceID, S32 threadPriority, UTF16 procWD);
					//Launch a processes with normal level access
					static bool launchProcess(UTF16 path, UTF16 args, S32 *retCodePtr, String *stdOut, String *stdErr);
					//Launch a process with admin access
					static bool launchAdminProcess(UTF16 path, UTF16 args, S32 *retCodePtr);
					//Check is the specified process is active
					static bool activeProc(PlatformHandle &proc);
					//Duplicate of above, uses process id
					static bool activeProc(U32 procID);
					//Duplicate of above, uses process name
					static bool activeProc(UTF16 procName);
					//Assign a flag to the specified process that it must stop before the main process can also stop
					static void forceMustStop(PlatformHandle &proc);
					//Returns the name of the process if one is present
					static UTF16 getProcName(U32 procID);
					//Return a flag based on if the process has focus
					static bool hasFocus();
					//Get the return code from the specified process
					static bool getReturnCode(PlatformHandle &proc, S32 *retCodePtr);
					//Terminate the process, set the second flag to true to terminate all sub-processes as well
					static void terminateProc(PlatformHandle &proc, bool termSubProc = false);
					//Switch the process into a standard deamon/service
					static bool becomeServiceProcess();

					/* Misc Functions */
					//Is this platform multithreaded?
					static bool isMultithreaded();
					//Fetch the affinity mask based on the name of the thread
					static U64 fetchAffinityMask(UTF16 name);
					//create a event object
					static class Event *createEvent(bool manualReset = false);
					//create a continual thread object
					static class ContinualThread *createContThread();
					//attempt to open a semaphore object, set create=false to override an existing one. maxLocks=1 can be used to force the sem to act as a mutex
					static Semaphore *openSemaphore(const String &name, bool create = true, U32 maxLocks = 1);
					//delete a semaphore
					static bool killSemaphore(Semaphore *trg);
					//Force the current thread to sleep for the specified time period, or set parameter 2 to true to sleep indefinitely
					static void sleep(F64 seconds = 0.0f, bool sleepInfinite = false);
			};

		};

	};

	#endif //GALACTIC_PLATFORM_WINDOWS_PLATFORMPROCESS

#endif //GALACTIC_WINDOWS