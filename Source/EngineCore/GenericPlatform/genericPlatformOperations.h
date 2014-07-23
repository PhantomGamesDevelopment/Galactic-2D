/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* genericPlatformOperations.h
*
* Defines operatable functions for the platform, excluded from genericPlatform.h to preserve load capabilities with classes.
**/

#ifndef GALACTIC_PLATFORM_GENERIC_PLATFORMOPS
#define GALACTIC_PLATFORM_GENERIC_PLATFORMOPS

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		MBDefs: A struct used to declare some properties used by message box operations
		*/
		struct MBDefs {
			/*
			Struct Members
			*/
			//MBTypes: Enumerate message dialog types allowed by the platform in the engine
			enum MBTypes {
				//OK: Message Dialog with an OK option
				Ok,
				//YesNo: Message Dialog with yes and no options
				YesNo,
				//OkCancel: Message Dialog with ok and cancel options 
				OkCancel,
				//YesNoCancel: Message Dialog with Yes, No, and cancel options
				YesNoCancel,
				//CancelRetryContinue: Message Dialog with Cancel, Retry, and continue options
				CancelRetryContinue,
				//YesNoYesAllNoAll:Message Dialog with options for Yes, No, Yes to All, and no to all (Usually mass file operations)
				YesNoYesAllNoAll,
				//YesNoYesAllNoAllCancel: Message Dialog with options for Yes, No, Yes to All, No to All, and cancel.
				YesNoYesAllNoAllCancel,
				//YesNoYesAll: Message Dialog with options for Yes, No, and Yes to All
				YesNoYesAll,
			};

			//MBReturnType: Enumerate return types for message dialogs
			enum MBReturnType {
				//RetOk: Single option for exiting out of the box with no action
				RetOk,
				//RetYes: Option for comfirming a requested action
				RetYes,
				//RetNo: Option for denying a requested action
				RetNo,
				//RetYesAll: Option for accepting multiple actions be done
				RetYesAll,
				//RetNoAll: Option for denying multiple actions be done
				RetNoAll,
				//RetCancel: Option for breaking out of a current action
				RetCancel,
				//RetRetry: Option for attempting the requested action again
				RetRetry,
				//RetContinue: Option for continuing the operation without any changes 
				RetContinue,
			};
		};

		/*
		GenericPlatformOperations: Declares a set of platform specific methods and operations. These are mainly used to gate each platform into the cross
		compatibility nature of the engine.
		*/
		class GenericPlatformOperations {
			public:
				/* Public Class Methods */
				//Load pre-init modules, such as platformFile, platformRender, etc.
				static void preInitModules();
				//load modules during initialization of the platform
				static void onInitModules();
				//Are we on a 64 Bit platform?
				static inline bool is64Bit();
				//Block the screensaver from opening by moving the mouse 0 pixels.
				static void blockScreensaver();
				//Return the number of cores on the computer
				static S32 numCores();
				//Return the number of cores specified as 'logical cores' (See Hyperthreading http://www.codeproject.com/Articles/9462/Counting-Physical-and-Logical-Processors)
				static S32 numLogicalCores();
				//Returns the recommended thread count to be used for game threads
				static S32 numThreadsToSpawn();
				//Fetch an item from the registry (on non-windows OS's, use their relative system for a registry)
				static bool fetchRegistryItem(const String &Key, const String &Value, bool useUser, String &result);
				//Copy text to the system clipboard.
				static void copyToClipboard(const TCHAR *text);
				//Paste text from the clipboard into the specified string.
				static void pasteFromClipboard(String &trgStr);
				//Open a message box with the specified options
				static MBDefs::MBReturnType OpenPlatformMB(MBDefs::MBTypes mbType, const TCHAR *mbText, const TCHAR *mbCaption);

			private:
				/* Private Class Methods */
				//Called prior to initialization
				static void preInit();
				//Called at initialization
				static void onInit();
				//Called after onInit();
				static void postInit();
				//Request application exit, use byForce to terminate immediately (this could have consequences if not used carefully)
				static void requestExit(bool byForce = false);
				//Fetch the window object.
				static any fetchWindowObject();
				//Fetch an environment variable and store it.
				static void fetchEnvVar(const TCHAR *varName, TCHAR *result, S32 length);
				//Fetch the MAC address string
				static String fetchMACAddr();
				//Fetch the raw MAC address
				static DynArray<U8> fetchMACRaw();
				//Enforce strict memory loading across the barrier call.
				static void strictMemory();
				//Platform allows direct messenging
				static bool platformMessagesAllowed();
				//Platform allows caching of memory locally
				static bool platformAllowsLocalCaching();
		};

	};

};

#endif