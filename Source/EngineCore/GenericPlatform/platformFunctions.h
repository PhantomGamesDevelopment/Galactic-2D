/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/platformFunctions.cpp
* Defines the PlatformProcess, Semaphore, PlatformHandle, and BinaryVersion classes for the Generic Platform
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
				FINLINE bool valid() const { return (Handle != inv && Handle != NULL); }
				//close(): close the handle object
				FINLINE bool close() { return valid(); }
				//reset(): reset the handle object
				FINLINE void reset() { Handle = inv; }

				/* Operators */
				//Assignment Operator
				FINLINE processHandle &operator=(const processHandle &c) { Handle = c.Handle; }

				/* Typedefs */
				//The type of the HANDLE object.
				typedef T hType;
		
			protected:
				/* Protected Class Members */
				//The Handle Object
				T Handle;
		};

		//Forward declaration for platform specific version of processHandle
		class PlatformHandle;

		/*
		GenericPlatformProcess: Declares a set of methods that are platform specific. Most of these tend to be template functions and some are just
		 simply unused but are defined to serve as points for platforms that may need them
		*/
		class GenericPlatformProcess {
			public:
				/*
				AffinityInfo: Declares a basic structure to store affinity data for the thread pool manager
				*/
				struct AffinityInfo {
					UTF16 threadName;
					U64 affinityMask;
				};

				/*
				GenericSemaphore: Declare a platform specific semaphore object
				*/
				class GenericSemaphore {
					public:
						/* Constructor / Destructor */
						//Constructor
						GenericSemaphore(const String &name);
						//Destructor
						virtual ~GenericSemaphore() { }

						/* Public Class Methods */
						//acquire(): force the system to obtain the semaphore lock for the specified thread
						virtual void acquire() = 0;
						//release(): release the semaphore lock
						virtual void release() = 0;
						//tryAcquire(): Safer form of acquire, set the system to try to acquire the lock over a specified time
						virtual bool tryAcquire(U64 nsToWait) = 0;
						//getName(): Get the stored name on the object
						UTF16 getName() const { return semName; };

					protected:
						/* Protected Class Members */
						//Name of the semaphore object
						C8 semName[128];
				};

				//Forward dec for Platform Semaphore
				class Semaphore;

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
				static PlatformHandle launchProcess(UTF16 path, UTF16 args, bool newWindow, bool minimized, bool hiddenProcess, U32 forceID, S32 threadPriority, UTF16 procWD, any ioWrite);
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

				/* Handle Reading Functions */
				//Spawn a handle read instance
				static bool spawnHandleIO(any &readerHandle, any& writerHandle);
				//Read from a handle
				static String readHandle(any handleIO);
				//Close a handle reader
				static void closeHandleIO(any readIO, any writeIO);

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
				//If the platform has access to <sys/time.h>, then we can define some helpful sleep methods
				#if GALACTIC_USE_SYS_TIME == 1
					//Force the current thread to sleep for the specified time period, or set parameter 2 to true to sleep indefinitely
					static void sleep(F64 seconds = 0.0f, bool sleepInfinite = false);
				#endif

			protected:
				/* Protected Class Members */
				//Affinity manager information
				static AffinityInfo affinityInformation[GALACTIC_AFFINITY_MANAGER_THREADCOUNT];
		};

	};

};

/* If we're using a PThread platform, load the PThread code now */
#if GALACTIC_USE_PTHREAD == 1
    //NOTE! The actual PThread module itself is loaded by the platform
	#include "../Generic/Thread/pThreadCritcalSection.h"
#endif

#endif //GALACTIC_PLATFORM_GENERIC_PLATFORMDEC