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

		PlatformHandle PlatformProcess::launchProcess(UTF16 path, UTF16 args, bool newWindow, bool minimized, bool hiddenProcess, U32 *resID, S32 threadPriority, UTF16 procWD, any ioWrite) {
			//MSDN briefly discusses this here: http://msdn.microsoft.com/en-us/library/windows/desktop/ms682425(v=vs.85).aspx, we're using something similar.
			String launchedCMD = String::ToStr("\"%s\" %s", path, args);
			PROCESS_INFORMATION pInfo;
			SECURITY_ATTRIBUTES sAttr;
			//Set up sAttr.
			sAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
			sAttr.bInheritHandle = true;
			sAttr.lpSecurityDescriptor = NULL;
			//Now, set up the U16/U32 flags for the launch priority & window settings.
			U16 shWindowFlags = SW_HIDE;
			U32 launchPriority = threadPriority > 0 ? (threadPriority == 1 ? (ABOVE_NORMAL_PRIORITY_CLASS) : (HIGH_PRIORITY_CLASS)) 
				: (threadPriority < 0 ? (threadPriority == -1 ? (BELOW_NORMAL_PRIORITY_CLASS) : (IDLE_PRIORITY_CLASS)) : (NORMAL_PRIORITY_CLASS));
			U32 newWindowFlags = NULL;			
			if (newWindow) {
				launchPriority |= DETACHED_PROCESS;
			}
			//Test additional launch flags
			if (hiddenProcess) {
				newWindowFlags = STARTF_USESHOWWINDOW;
			}
			else if (minimized) {
				shWindowFlags = SW_SHOWMINNOACTIVE;
				newWindowFlags = STARTF_USESHOWWINDOW;
			}
			//If we have a Handle write catcher, load that in.
			if (ioWrite) {
				newWindowFlags |= STARTF_USESTDHANDLES;
			}
			//Now, attempt to launch the process, see http://msdn.microsoft.com/en-us/library/windows/desktop/ms686331(v=vs.85).aspx for struct info.
			STARTUPINFO sInfo = { sizeof(STARTUPINFO), NULL, NULL, NULL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				NULL, NULL, NULL, newWindowFlags, shWindowFlags, NULL, NULL, ::GetStdHandle(STD_INPUT_HANDLE), HANDLE(ioWrite), HANDLE(ioWrite) };
			if (!CreateProcess(NULL, (TCHAR *)launchedCMD.c_str(), &sAttr, &sAttr, true, launchPriority, NULL, (TCHAR *)procWD, &sInfo, &pInfo)) {
				//Something went wrong.
				if (resID) {
					*resID = 0;
				}
				GC_Error("PlatformProcess::launchProcess(): Failed to initialize new process.");
				return PlatformHandle();
			}
			//If we need to fetch the ID, do so.
			if (resID) {
				*resID = pInfo.dwProcessId;
			}
			//Clean up, and return the process.
			::CloseHandle(pInfo.hThread);
			return PlatformHandle(pInfo.hProcess);
		}

		bool PlatformProcess::launchProcess(UTF16 path, UTF16 args, S32 *retCodePtr, String *stdOut, String *stdErr) {
			//Set up some constants
			X32 maxIOCount = 2;
			cbol forkToIO = (stdOut != NULL || stdErr != NULL);
			bool success = false;
			//See the above function, direct launching doesn't need the "x" -args format:
			String launchedCMD = String::ToStr("%s %s", path, args);
			PROCESS_INFORMATION pInfo;
			SECURITY_ATTRIBUTES sAttr;
			//Set up sAttr.
			sAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
			sAttr.bInheritHandle = true;
			sAttr.lpSecurityDescriptor = NULL;
			//Set up the U16/U32 Flags
			U16 shWindowFlags = STARTF_USESHOWWINDOW;
			U32 launchPriority = NORMAL_PRIORITY_CLASS | DETACHED_PROCESS;
			U32 newWindowFlags = SW_SHOWMINNOACTIVE;
			//Set up the Handle Readers
			HANDLE writeIO[maxIOCount] = { NULL };
			HANDLE readIO[maxIOCount] = { NULL };
			if (forkToIO) {
				newWindowFlags |= STARTF_USESTDHANDLES;
				for (S32 i = 0; i < maxIOCount; i++) {
					::CreatePipe(&readIO[i], &writeIO[i], &sAttr, 0);
					::SetHandleInformation(&readIO[i], HANDLE_FLAG_INHERIT, 0);
				}
			}
			//Now, attempt to launch the process, see http://msdn.microsoft.com/en-us/library/windows/desktop/ms686331(v=vs.85).aspx for struct info.
			STARTUPINFO sInfo = { sizeof(STARTUPINFO), NULL, NULL, NULL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				NULL, NULL, NULL, newWindowFlags, shWindowFlags, NULL, NULL, ::GetStdHandle(STD_INPUT_HANDLE), writeIO[0], writeIO[1] };
			if (CreateProcess(NULL, (TCHAR *)launchedCMD.c_str(), &sAttr, &sAttr, true, launchPriority, NULL, NULL, &sInfo, &pInfo)) {
				if (forkToIO) {
					PlatformHandle pHandle(pInfo.hProcess);
					String *outStr[maxIOCount] = { stdOut, stdErr };
					//Keep reading while the process is alive.
					do {
						readFromHandle(maxIOCount, outStr, readIO);
						PlatformProcess::sleep();
					} while (activeProc(pHandle));
					//Read the close command on the auxillary process
					readFromHandle(maxIOCount, outStr, readIO);
				}
				else {
					//If we're not forking, then we're waiting.
					::WaitForSingleObject(pInfo.hProcess, INFINITE);
				}
				//Once we hit here, then we're at the close of the auxillary, let's fetch the exit code.
				if (retCodePtr) {
					//See http://msdn.microsoft.com/en-us/library/windows/desktop/ms683189(v=vs.85).aspx for function usage.
					::GetExitCodeProcess(pInfo.hProcess, (::DWORD *)retCodePtr);
				}
				//Clean up!
				::CloseHandle(pInfo.hProcess);
				::CloseHandle(pInfo.hThread);
				success = true;
			}
			else {
				if (retCodePtr) {
					*retCodePtr = GetLastError();
				}
				if (forkToIO) {
					for (S32 i = 0; i < maxIOCount; i++) {
						::CloseHandle(writeIO[i]);
					}
				}
			}
			if (forkToIO) {
				for (S32 i = 0; i < maxIOCount; i++) {
					::CloseHandle(readIO[i]);
				}
			}
			return success;
		}

		bool PlatformProcess::launchAdminProcess(UTF16 path, UTF16 args, S32 *retCodePtr) {
			//See http://msdn.microsoft.com/en-us/library/windows/desktop/bb776886(v=vs.85).aspx
			bool success = false;
			//Set up the Shell Execute information struct
			SHELLEXECUTEINFO sInfo;
			Memory::gmemset(&sInfo, 0, sizeof(SHELLEXECUTEINFO));
			sInfo.cbSize = sizeof(SHELLEXECUTEINFO);
			sInfo.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_UNICODE;
			sInfo.lpFile = (TCHAR *)path;
			sInfo.lpParameters = (TCHAR *)args;
			sInfo.lpVerb = TEXT("runas");
			sInfo.nShow = SW_SHOW;
			//Attempt to launch
			if (ShellExecuteEx(&sInfo)) {
				::WaitForSingleObject(sInfo.hProcess, INFINITE);
				if (retCodePtr) {
					//See http://msdn.microsoft.com/en-us/library/windows/desktop/ms683189(v=vs.85).aspx for function usage.
					::GetExitCodeProcess(sInfo.hProcess, (::DWORD *)retCodePtr);
				}
				::CloseHandle(sInfo.hProcess);
				success = true;
			}
			return success;
		}

		bool PlatformProcess::activeProc(PlatformHandle &proc) {
			bool running = true;
			U32 res = ::WaitForSingleObject(proc.fetch(), 0);
			if (res != WAIT_TIMEOUT) {
				running = false;
			}
			return running;
		}

		bool PlatformProcess::activeProc(U32 procID) {
			bool running = false;
			HANDLE proc = OpenProcess(SYNCHRONIZE, false, procID);
			if (proc != NULL) {
				U32 res = ::WaitForSingleObject(proc, 0);
				if (res == WAIT_TIMEOUT) {
					running = true;
				}
			}
			return running;
		}

		bool PlatformProcess::activeProc(UTF16 procName) {
			//First we need to make sure the process name is "complete" (w/ extension)
			String process = procName;
			if (process.find(".exe", 0, String::NoCaseSens) != 0) {
				process += ".exe";
			}
			//Now search through the running processes and see if our process is in that list.
			HANDLE procSrc = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (procSrc == INVALID_HANDLE_VALUE || procSrc == NULL) {
				//Something broke... lol...
				::CloseHandle(procSrc);
				return false;
			}
			PROCESSENTRY32 iProc;
			iProc.dwSize = sizeof(PROCESSENTRY32);
			//Run through the list.
			if (::Process32First(procSrc, &iProc) != false) {
				do {
					if (process.compare((UTF16)iProc.szExeFile) == 0) {
						//Bingo!
						::CloseHandle(procSrc);
						return true;
					}
				} while (::Process32Next(procSrc, &iProc) != false);
			}
			::CloseHandle(procSrc);
			return false;
		}

		void PlatformProcess::forceMustStop(PlatformHandle &proc) {
			::WaitForSingleObject(proc.fetch(), INFINITE);
		}

		UTF16 PlatformProcess::getProcName(U32 procID) {
			String result;
			HANDLE proc = OpenProcess(PROCESS_QUERY_INFORMATION, false, procID);
			if (proc == NULL) {
				GC_Error("PlatformProcess::getProcName(): Invalid process ID.");
				return "";
			}
			//Set up some constants...
			X32 bufferSize = 4096; 
			TCHAR processInfoName[bufferSize];
			S32 nonConstSize = bufferSize;
			if (sizeof(S32) != sizeof(::DWORD)) {
				//This shouldn't happen... like, ever, in today's world. Besides, who has a 1990's C++ compiler anymore????
				GC_Error("PlatformProcess::getProcName(): This function don got rekt. It looks like you compiled this engine on some 1990's compiler, and survived?");
				return "";
			}
			#if WINVER == 0x0502
				//Don't worry 1990, we still love you...
				GetProcessImageFileName(proc, processInfoName, nonConstSize);
			#else
				//Image FileName function of... today!!!
				QueryFullProcessImageName(proc, NULL, processInfoName, (PDWORD)(&nonConstSize));
			#endif
			//Got the result, put it in the string...
			result = (UTF16)processInfoName;
			return result.c_str();
		}

		bool PlatformProcess::hasFocus() {
			U32 focusProcID;
			::GetWindowThreadProcessId(GetForegroundWindow(), (::DWORD *)&focusProcID);
			return (focusProcID == getProcID());
		}

		bool PlatformProcess::getReturnCode(PlatformHandle &proc, S32 *retCodePtr) {
			bool result = ::GetExitCodeProcess(proc.fetch(), (::DWORD *)retCodePtr)  && (*(U32 *)retCodePtr != STILL_ACTIVE);
			return result;
		}

		void PlatformProcess::terminateProc(PlatformHandle &proc, bool termSubProc) {
			if (termSubProc) {
				HANDLE procSrc = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
				if (procSrc != INVALID_HANDLE_VALUE) {
					::DWORD pID = ::GetProcessId(proc.fetch());
					PROCESSENTRY32 iProc;
					iProc.dwSize = sizeof(PROCESSENTRY32);
					if (::Process32First(procSrc, &iProc) != false) {
						do {
							if (iProc.th32ParentProcessID == pID) {
								HANDLE subProc = ::OpenProcess(PROCESS_ALL_ACCESS, false, iProc.th32ProcessID);
								if (subProc) {
									PlatformHandle subPlatformProc(subProc);
									terminateProc(subPlatformProc, termSubProc);
								}
							}
						} while (::Process32Next(procSrc, &iProc) != false);
					}
				}
			}
			//Close the specified process.
			TerminateProcess(proc.fetch(), 0);
			proc.close();
		}

		bool PlatformProcess::becomeServiceProcess() {
			//Windows Daemoning (Service) is currently unsupported.
			// We'll come back to this post RC-3. See http://codebrocken.blogspot.com/2012/07/c-create-windows-service.html for examples
			return false;
		}

	};

};

#endif //GALACTIC_WINDOWS