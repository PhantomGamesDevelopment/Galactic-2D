/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/platformOperations.h
* Additional platform functions that are kept outside of the function lib for compatibility
* (C) 2014-2016 Phantom Games Development - All Rights Reserved
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

#ifndef GALACTIC_PLATFORM_GENERIC_PLATFORMOPS
#define GALACTIC_PLATFORM_GENERIC_PLATFORMOPS

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		//MAPKEY_fetchStandardKeyMap(): Macro shortcut to add a key mapping to the list, used by function GenericPlatformOperations::fetchStandardKeyMap()
		#define MAPKEY_fetchStandardKeyMap(name, code) if(totalMaps < maxMaps) {\
			keyCodes[totalMaps] = code; \
			keyNames[totalMaps] = name; \
			totalMaps++; \
			}

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
				static void copyToClipboard(UTF16 text);
				//Paste text from the clipboard into the specified string.
				static void pasteFromClipboard(String &trgStr);
				//Create a GUID
				static void createGUID(galacticGUID &inGuid);
				//Open a message box with the specified options
				static MBDefs::MBReturnType OpenPlatformMB(MBDefs::MBTypes mbType, UTF16 mbText, UTF16 mbCaption);
				//Fetch the mapping of a specified key from the code
				SFIN U32 getMappedKey(U16 *keyCodes, U32 maxMaps, String *keyNames);
				//Fetch the mapping of a specified key from a character
				SFIN U32 getMappedChar(U16 *keyCodes, U32 maxMaps, String *keyNames);
				//Get the application root directory
				static UTF16 getRootDir();
				//Fetch the default platform separator
				static UTF16 fetchPlatformSeparator();
				//Normalize the file path based on the platform
				static void normalizePath(String &inPath);
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
				static void fetchEnvVar(UTF16 varName, UTF8 result, S32 length);
				//Fetch the MAC address string
				static String fetchMACAddr();
				//Fetch the raw MAC address
				static Vector<U8> fetchMACRaw();
				//Enforce strict memory loading across the barrier call.
				static void strictMemory();
				//Platform allows direct messenging
				static bool platformMessagesAllowed();
				//Platform allows caching of memory locally
				static bool platformAllowsLocalCaching();
				//Pump OS Messages
				SFIN void pumpMessages(bool fromMainLoop);

			protected:
				/* Protected Class Methods */
				//Get the standard named key mapping for the specified instance, overriden by individual OSs to handle individual instancing
				static U32 fetchStandardKeyMap(U16 *keyCodes, U32 maxMaps, String *keyNames, bool mapUppercase, bool mapLowercase);
		};

	};

};

#endif