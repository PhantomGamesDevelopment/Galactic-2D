/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* genericPlatform.h
*
* Defines methods and operations that are specific to platforms, in this case, these are templates to other platforms for easy declaration
**/

#ifndef GALACTIC_PLATFORM_GENERIC_PLATFORMDEC
#define GALACTIC_PLATFORM_GENERIC_PLATFORMDEC

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		BinaryVersion: A very basic class used to identify version numbers of .DLLs and .EXEs
		*/
		class BinaryVersion {
			public:
				/* Constructor / Destructor */
				//Default Constructor
				BinaryVersion(S32 V, S32 Ma, S32 Mi, S32 R) : Version(V), Major(Ma), Minor(Mi), Revision(R) { }

				/* Public Class Methods */
				//Test if the numerical values are valid
				bool valid() { return ((Version | Major | Minor | Revision) != 0); }
				//Print the values to a string
				void toStr(const String &out);

				/* Operators */
				//Assignment Operator
				BinaryVersion &operator=(const BinaryVersion &c) { Version = c.Version; Major = c.Major; Minor = c.Minor; Revision = c.Revision; return *this; }
				//Equality Operator
				bool operator==(const BinaryVersion &c) { return (Version == c.Version && Major == c.Major && Minor == c.Minor && Revision == c.Revision); }

			private:
				/* Private Class Members */
				//The main version number on the file
				S32 Version;
				//The major version number on the file
				S32 Major;
				//The minor version number on the file
				S32 Minor;
				//The revision version number on the file
				S32 Revision;
		};

		/*
		processHandle: Implements a template class for a HANDLE object, used mainly by platform operations throughout this module
		*/
		template <typename T, T inv> class processHandle {
			public:
				/* Constructor / Destructor */
				//Default Constructor
				FINLINE processHandle() : Handle(inv) { }
				//Copy Constructor
				FINLINE processHandle(T copy) : Handle(copy) { }

				/* Public Class Methods */
				//fetch(): get the stored Handle
				FINLINE T fetch() const { return Handle; }
				//valid(): returns if the handle is valid or not
				FINLINE bool valid() const { return (Handle != Inv && Handle != NULL); }
				//close(): close the handle object
				FINLINE bool close() { return valid(); }
				//reset(): reset the handle object
				FINLINE void reset() { Handle = inv; }

				/* Operators */
				//Assignment Operator
				FINLINE processHandle &operator=(const processHandle &c) { Handle = c.Handle; }
		
			protected:
				/* Protected Class Members */
				//The Handle Object
				T Handle;
		};

		//Forward declaration for platform specific version of processHandle
		class pHandle;

		/*
		GenericPlatformProcess: Declares a set of methods that are platform specific. Most of these tend to be template functions and some are just
		 simply unused but are defined to serve as points for platforms that may need them
		*/
		class GenericPlatformProcess {
			public:
				/* 
				Special Note: Everything in this class is public, so there's no need for special separation comments. Y/w :) ~Phantom 
				Instead I'll separate things by what they do as a process
				*/

				/*
				Semaphore: Declare a platform specific semaphore object
				*/
				class Semaphore {
					public:
						/* Constructor / Destructor */
						//Constructor
						Semaphore(const String &name);
						//Destructor
						virtual ~Semaphore();

						/* Public Class Methods */
						//acquire(): force the system to obtain the semaphore lock for the specified thread
						virtual void acquire() = 0;
						//release(): release the semaphore lock
						virtual void release() = 0;
						//tryAcquire(): Safer form of acquire, set the system to try to acquire the lock over a specified time
						virtual bool tryAcquire(U64 nsToWait) = 0;
						//getName(): Get the stored name on the object
						const TCHAR *getName() const;

					protected:
						/* Protected Class Members */
						//Name of the semaphore object
						C8 semName[128];
				};

				/* General Platform Processing Information */
				//Get the process ID
				static U32 getProcID();
				//get the base directory of the project
				static const TCHAR *getBaseDir();
				//Get the user directory
				static const TCHAR *getUserDir();
				//Get the application settings directory
				static const TCHAR *getAppSetDir();
				//Get the user settings directory
				static const TCHAR *getUserSetDir();
				//Set the process affinity mask (called on the main thread)
				static void setAffinityMask(U64 mask);
				//Get the user name
				static const TCHAR *userName();
				//Get the computer name
				static const TCHAR *compName();
				//Get the name of the executable being ran
				static const TCHAR *getExeName(bool includeExtension = false);

				/* Platform Specific Library Loading */
				//Load a dynamic library into a handle
				static any getLibHandle(const TCHAR *filePath);
				//Free a library handle
				static void freeLibHandle(any handle);
				//Fetch the specified function from the lib
				static any fetchFunction(any handle, const TCHAR *procName);
				//Fetch the file extension for libraries on this platform
				static const TCHAR *getLibExtension();
				//Fetch the version of the specified binary file (.exe, .dll, .so, etc)
				static BinaryVersion fetchVersion(const TCHAR *filePath);

				/* Process Functions */
				//Launch a new process with the given parameters
				static pHandle launchProcess(const TCHAR *path, const TCHAR *args, bool newWindow, bool minimized, bool hiddenProcess, U32 forceID, S32 threadPriority, const TCHAR *procWD);
				//Launch a processes with normal level access
				static bool launchProcess(const TCHAR *path, const TCHAR *args, S32 *retCodePtr, String *stdOut, String *stdErr);
				//Launch a process with admin access
				static bool launchAdminProcess(const TCHAR *path, const TCHAR *args, S32 *retCodePtr);
				//Check is the specified process is active
				static bool activeProc(pHandle &proc);
				//Duplicate of above, uses process id
				static bool activeProc(U32 procID);
				//Duplicate of above, uses process name
				static bool activeProc(const TCHAR *procName);
				//Assign a flag to the specified process that it must stop before the main process can also stop
				static void forceMustStop(pHandle &proc);
				//Returns the name of the process if one is present
				static const TCHAR *getProcName(U32 procID);
				//Return a flag based on if the process has focus
				static bool hasFocus();
				//Get the return code from the specified process
				static bool getReturnCode(pHandle &proc, S32 *retCodePtr);
				//Terminate the process, set the second flag to true to terminate all sub-processes as well
				static void terminateProc(pHandle &proc, bool termSubProc = false);
				//Switch the process into a standard deamon/service
				static bool becomeServiceProcess();

				/* Misc Functions */
				//Delete all temporary files and cached stuff
				static void clearTemp() { };
				//Is this platform multithreaded?
				static bool isMultithreaded();
				//create a event object
				static class Event *createEvent(bool manualReset = false);
				//create a continual thread object
				static class ContinualThread createContThread();
				//attempt to open a semaphore object, set create=false to override an existing one. maxLocks=1 can be used to force the sem to act as a mutex
				static Semaphore *openSemaphore(const String &name, bool create = true, U32 maxLocks = 1);
				//delete a semaphore
				static bool killSemaphore(Semaphore *trg);
				//If the platform has access to <sys/time.h>, then we can define some helpful sleep methods
				#if GALACTIC_USE_SYS_TIME == 1
					//Force the current thread to sleep for the specified time period, or set parameter 2 to true to sleep indefinitely
					static void sleep(F32 seconds = 0.0f, bool sleepInfinite = false);
				#endif
		};

	};

};

/* If we're using a PThread platform, load the PThread code now */
#if GALACTIC_USE_PTHREAD == 1
    //NOTE! The actual PThread module itself is loaded by the platform
	#include "../Generic/Thread/pThreadCritcalSection.h"
#endif

#endif //GALACTIC_PLATFORM_GENERIC_PLATFORMDEC