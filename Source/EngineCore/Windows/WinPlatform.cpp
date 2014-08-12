/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* WinPlatform.cpp
*
* Defines the PlatformProcess, Semaphore, PlatformHandle, and BinaryVersion classes for the Windows Platform
**/

#include "../engineCore.h"
//Note: These header includes could potentially be moved to loadWindows.h, however they're only needed in this file.
#include <shellapi.h>
#include <shlobj.h>
#include <LM.h>
#include <tlhelp32.h>

#ifdef GALACTIC_WINDOWS	

namespace Galactic {

	namespace Core {

		/*
		PlatformProcess::Semaphore Definitions
		*/

		PlatformProcess::Semaphore::Semaphore(const String &name, HANDLE inObj) : GenericSemaphore(name), semObj(inObj) { }

		void PlatformProcess::Semaphore::acquire() {
			if (!semObj) {
				GC_Error("Semaphore::acquire(): Unable to locate sem object.");
				return;
			}
			DWORD waitRes = WaitForSingleObject(semObj, INFINITE);
			if (waitRes != WAIT_OBJECT_0) {
				GC_Error("Semaphore::acquire(): Failed to acquire semaphore.");
			}
		}

		void PlatformProcess::Semaphore::release() {
			if (!semObj) {
				GC_Error("Semaphore::release(): Unable to locate sem object.");
				return;
			}
			if (!ReleaseSemaphore(semObj, 1, NULL)) {
				GC_Error("Semaphore::release(): Failed to release semaphore.");
			}
		}

		bool PlatformProcess::Semaphore::tryAcquire(U64 nsToWait) {
			if (!semObj) {
				GC_Error("Semaphore::tryAcquire(): Unable to locate sem object.");
				return false;
			}
			//Convert the time to Miliseconds
			DWORD timeToWaitInMS = DWORD(nsToWait / (1000000ULL));
			DWORD waitRes = WaitForSingleObject(semObj, timeToWaitInMS);
			if (waitRes != WAIT_OBJECT_0 && waitRes != WAIT_TIMEOUT) {
				GC_Error("Semaphore::tryAcquire(): Failed to acquire semaphore.");
			}
			return FBOOL(waitRes == WAIT_OBJECT_0);
		}

		/*
		PlatformProcess Definitions
		*/

		U32 PlatformProcess::getProcID() {
			return ::GetCurrentProcessId();
		}

		UTF16 PlatformProcess::getUserDir() {
			//Keep it static so we can "save" the result.
			static String userDir;
			if (userDir.empty()) {
				//Path Limits: http://msdn.microsoft.com/en-us/library/aa365247.aspx
				TCHAR userDirPath[MAX_PATH];
				//Ref: http://msdn.microsoft.com/en-us/library/windows/desktop/bb762181(v=vs.85).aspx
				if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, userDirPath))) {
					// 'Fix' the slashes so they match Windows standards.
					userDir = (UTF8)userDirPath;
					userDir = userDir.replace("\\", "/");
				}
				else {
					GC_Error("PlatformProcess::getUserDir(): Failed to fetch the user directory.");
					userDir.clear();
					return "";
				}
			}
			return userDir.c_str();
		}

		UTF16 PlatformProcess::getAppSetDir(UTF16 append, bool forceUpdate) {
			//Keep it static so we can "save" the result.
			static String appSetDir;
			if (appSetDir.empty() && !forceUpdate) {
				//Path Limits: http://msdn.microsoft.com/en-us/library/aa365247.aspx
				TCHAR appDirPath[MAX_PATH];
				//Ref: http://msdn.microsoft.com/en-us/library/windows/desktop/bb762181(v=vs.85).aspx
				if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_CURRENT, appDirPath))) {
					// 'Fix' the slashes so they match Windows standards.
					appSetDir = (UTF8)appDirPath;
					appSetDir = appSetDir.replace("\\", "/");
					//Append the contents sent to this method. This is for things like: ApplicationSettings/YourGame/X/
					appSetDir += "/";
					appSetDir += append;
					//If they sent the / with append, strip it out :)
					appSetDir = appSetDir.replace("//", "/");
				}
				else {
					GC_Error("PlatformProcess::getAppSetDir(): Failed to fetch the application settings directory.");
					appSetDir.clear();
					return "";
				}
			}
			return appSetDir.c_str();
		}
		
		UTF16 PlatformProcess::getUserSetDir() {
			//Keep it static so we can "save" the result.
			static String userSettingsDir;
			if (userSettingsDir.empty()) {
				//Path Limits: http://msdn.microsoft.com/en-us/library/aa365247.aspx
				TCHAR userSetDirPath[MAX_PATH];
				//Ref: http://msdn.microsoft.com/en-us/library/windows/desktop/bb762181(v=vs.85).aspx
				if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, userSetDirPath))) {
					// 'Fix' the slashes so they match Windows standards.
					userSettingsDir = (UTF8)userSetDirPath;
					userSettingsDir = userSettingsDir.replace("\\", "/");
				}
				else {
					GC_Error("PlatformProcess::getUserSetDir(): Failed to fetch the user settings directory.");
					userSettingsDir.clear();
					return "";
				}
			}
			return userSettingsDir.c_str();
		}

		void PlatformProcess::setAffinityMask(U64 newMask) {
			//Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/ms686247(v=vs.85).aspx
			::SetThreadAffinityMask(::GetCurrentThread(), (DWORD_PTR)newMask);
		}

		UTF16 PlatformProcess::userName() {
			static TCHAR userName[256];
			if (userName[0] == NULL) {
				U32 arrSize = getArrayCount(userName);
				GetUserName(userName, (::DWORD *)&arrSize);
			}
			return ((UTF16)userName);
		}

		UTF16 PlatformProcess::compName() {
			static TCHAR compName[256];
			if (compName[0] == NULL) {
				U32 arrSize = getArrayCount(compName);
				GetComputerName(compName, (::DWORD *)&arrSize);
			}
			return ((UTF16)compName);
		}

		UTF16 PlatformProcess::getExeName(bool includeExtension) {

		}

	};

};

#endif //GALACTIC_WINDOWS