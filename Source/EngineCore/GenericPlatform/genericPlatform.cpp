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
			GC_Warn("activeProc(): This method is not implemented on the generic platform.");
			return false;
		}

		bool GenericPlatformProcess::isMultithreaded() {
			//Note! While this bool return does control some form of multithread support in the engine, this is fully controlled by the definition
			// of GALACTIC_DISABLE_MULTITHREADING in galacticSettings.h
			return ProcessCommandLine::fetchInstance().hasParam("noMThreads");
		}

		U64 GenericPlatformProcess::fetchAffinityMask(UTF16 name) {
			return U64DEF(0xffffffffffffffff);
		}

	};

};