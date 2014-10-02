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
			//Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/ms683197(v=vs.85).aspx
			static TCHAR execName[512], execNameExt[512];
			if (!execName[0]) {
				//Fetch the path.
				if (GetModuleFileName(hInstance, execName, getArrayCount(execName)) != 0) {
					String exeName, exeNameExt;
					FilePath execPath((UTF16)execName);
					exeName = execPath.getFilePathMinusExt();
					exeNameExt = execPath.getFullPath();
			        //Convert to TCHAR
					_tcscpy_s(execName, sizeof(execName), (WCHAR *)exeName.c_str());
					_tcscpy_s(execNameExt, sizeof(execNameExt), (WCHAR *)exeNameExt.c_str());
				}
				else {
					Memory::gmemset(execName, 0, sizeof(execName));
					Memory::gmemset(execNameExt, 0, sizeof(execNameExt));
				}
			}
			return includeExtension ? ((UTF16)execNameExt) : ((UTF16)execName);
		}

		any PlatformProcess::getLibHandle(UTF16 filePath) {
			if (!filePath) {
				GC_CError("PlatformProcess::getLibHandle() - Missing path parameter");
				return NULL;
			}
			//For ::LoadLibraryW we need to make sure that the error boxes are turned off to not "potentially kill" the process if it fails.
			// 0x8000 = SEM_NOOPENFILEERRORBOX, http://msdn.microsoft.com/en-us/library/windows/desktop/ms680621(v=vs.85).aspx
			::SetErrorMode(0x8000);
			return ::LoadLibraryW((const TCHAR *)filePath);
		}

		void PlatformProcess::freeLibHandle(any handle) {
			//This function has a built in error check for NULL, so no further calls are needed here.
			::FreeLibrary((HMODULE)handle);
		}

		any PlatformProcess::fetchFunction(any handle, UTF16 procName) {
			//Both of these need to be checked for NULL
			if (!handle) {
				GC_CError("PlatformProcess::fetchFunction() - Missing .DLL Handle Call");
				return NULL;
			}
			if (!procName) {
				GC_CError("PlatformProcess::fetchFunction() - Missing .DLL function name to call");
				return NULL;
			}
			//References: http://msdn.microsoft.com/en-us/library/windows/desktop/ms683212(v=vs.85).aspx, http://msdn.microsoft.com/en-us/library/64tkc9y5.aspx
			//NOTE! 'procName' must be a ANSI compliant constant character array, IE: You MUST convert to UTF16 prior to sending it to this function.
			// Posible To-Do: Enforce 'explicit' on procName, or do a static_cast<UTF16>() on the character to make sure it's compliant. Will look into this later.
			return (any)::GetProcAddress((HMODULE)handle, procName);
		}

		UTF16 PlatformProcess::getLibExtension() {
			//Note: This doesn't handle files with extension of .dll the same. You might want to strupr / strlwr all file extensions before sending it here.
			return ".DLL";
		}

		BinaryVersion PlatformProcess::fetchVersion(UTF16 filePath) {
			if (!filePath) {
				GC_Error("PlatformProcess::fetchVersion() - Missing file path.");
				return BinaryVersion(0, 0, 0, 0);
			}
			/* References: 
			* http://msdn.microsoft.com/en-us/library/windows/desktop/ms647005(v=vs.85).aspx, 
			* http://msdn.microsoft.com/en-us/library/windows/desktop/ms647003(v=vs.85).aspx, 
			* http://msdn.microsoft.com/en-us/library/windows/desktop/ms647464(v=vs.85).aspx,
			* http://stackoverflow.com/questions/940707/how-do-i-programatically-get-the-version-of-a-dll-or-exe-file
			* Basically, the order to use is GetFileVersionInfoSize, GetFileVersionInfo, VerQueryValue
			*/

			//Fetch the size first, if the call fails, return with an error.
			::DWORD versionInfoSize = GetFileVersionInfoSize((const TCHAR *)filePath, NULL);
			if (versionInfoSize == 0) {
				GC_Error("PlatformProcess::fetchVersion() - Failed to fetch version of file %s, size of information is 0.", filePath);
				return BinaryVersion(0, 0, 0, 0);
			}
			//Now fetch the info structure
			U8 *versionInfo = new U8[versionInfoSize];
			if (GetFileVersionInfo((const TCHAR *)filePath, NULL, versionInfoSize, versionInfo) == 0) {
				GC_Error("PlatformProcess::fetchVersion() - Failed to fetch version of file %s, call to getFileVersionInfo failed.", filePath);
				delete[] versionInfo;
				return BinaryVersion(0, 0, 0, 0);
			}
			//Try to pull the version out now...
			U32 VS_FFISize = 0;
			VS_FIXEDFILEINFO *fileInfoStruct = NULL;
			if (VerQueryValue(versionInfo, TEXT("\\"), (LPVOID*)&fileInfoStruct, &VS_FFISize) == 0) {
				GC_Error("PlatformProcess::fetchVersion() - Failed to fetch version of file %s, call to VerQueryValue failed.", filePath);
				delete[] versionInfo;
				return BinaryVersion(0, 0, 0, 0);
			}
			if (VS_FFISize) {
				S32 vers = (fileInfoStruct->dwProductVersionMS >> 16) & 0xffff, 
					major = (fileInfoStruct->dwProductVersionMS >> 0) & 0xffff, 
					minor = (fileInfoStruct->dwProductVersionLS >> 16) & 0xffff, 
					rev = (fileInfoStruct->dwProductVersionLS >> 0) & 0xffff;
				delete[] versionInfo;
				return BinaryVersion(vers, major, minor, rev);
			}
			else {
				GC_Error("PlatformProcess::fetchVersion() - Failed to fetch version of file %s, VS_FFISize is 0.", filePath);
				delete[] versionInfo;
				return BinaryVersion(0, 0, 0, 0);
			}
		}

	};

};

#endif //GALACTIC_WINDOWS