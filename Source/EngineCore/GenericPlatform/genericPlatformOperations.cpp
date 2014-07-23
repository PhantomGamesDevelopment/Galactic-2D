/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* genericPlatformOperations.cpp
*
* Defines operatable functions for the platform, excluded from genericPlatform.h to preserve load capabilities with classes.
**/

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		void GenericPlatformOperations::preInitModules() {
			//Stub Function...
		}

		void GenericPlatformOperations::onInitModules() {
			//Stub Function...
		}

		bool GenericPlatformOperations::is64Bit() {
			return FBOOL(GALACTIC_64BIT_SUPPORT);
		}

		void GenericPlatformOperations::blockScreensaver() {
			//Stub Function...
		}

		S32 GenericPlatformOperations::numCores() {
			return 1;
		}

		S32 GenericPlatformOperations::numLogicalCores() {
			return PlatformOperations::numCores();
		}

		S32 GenericPlatformOperations::numThreadsToSpawn() {
			S32 cores = numCores();

			return gMax(gMin(cores - 1, GALACTIC_MAXIMUM_WORKING_THREADS), 1);
		}

		const TCHAR *GenericPlatformOperations::getRootDir() {
			GC_Warn("getRootDir() is not implemented on the generic platform.");
			return (const TCHAR *)("");
		}

		const TCHAR *GenericPlatformOperations::getGameDir() {
			GC_Warn("getGameDir() is not implemented on the generic platform.");
			return (const TCHAR *)("");
		}

		bool GenericPlatformOperations::fetchRegistryItem(const String &Key, const String &Value, bool useUser, String &result) {
			GC_Warn("fetchRegistryItem() is not implemented on the generic platform.");
			return false;
		}

		void GenericPlatformOperations::copyToClipboard(const TCHAR *text) {
			GC_Warn("copyToClipboard() is not implemented on the generic platform.");
		}

		void GenericPlatformOperations::pasteFromClipboard(String &trgStr) {
			GC_Warn("pasteFromClipboard() is not implemented on the generic platform.");
			trgStr = String::emptyStrRef;
		}

		MBDefs::MBReturnType GenericPlatformOperations::OpenPlatformMB(MBDefs::MBTypes mbType, const TCHAR *mbText, const TCHAR *mbCaption) {
			GC_Warn("OpenPlatformMB() is not implemented on the generic platform, returning relevant negative type (If Possible).");
			switch (mbType) {
				case MBDefs::MBTypes::Ok:
					return MBDefs::MBReturnType::RetOk;
				case MBDefs::MBTypes::YesNo:
					return MBDefs::MBReturnType::RetNo;
				case MBDefs::MBTypes::OkCancel:
					return MBDefs::MBReturnType::RetCancel;
				case MBDefs::MBTypes::YesNoCancel:
					return MBDefs::MBReturnType::RetCancel;
				case MBDefs::MBTypes::CancelRetryContinue:
					return MBDefs::MBReturnType::RetCancel;
				case MBDefs::MBTypes::YesNoYesAllNoAll:
					return MBDefs::MBReturnType::RetNoAll;
				case MBDefs::MBTypes::YesNoYesAllNoAllCancel:
					return MBDefs::MBReturnType::RetCancel;
				case MBDefs::MBTypes::YesNoYesAll:
					return MBDefs::MBReturnType::RetNo;
				default:
					GC_Error("OpenPlatformMB(): Unidentified dialog type sent to command, breaking.");
					return MBDefs::MBReturnType::RetCancel;
			}
		}

		void GenericPlatformOperations::preInit() {
			//Stub Function...
		}

		void GenericPlatformOperations::onInit() {
			//Stub Function...
		}

		void GenericPlatformOperations::postInit() {
			//Stub Function...
		}

		void GenericPlatformOperations::requestExit(bool byForce) {
			if (byForce) {
				GC_CError("Application calling requestExit() with byForce=1, this may cause some problems!!!");
				abort();
			}
			//Send a flag to mainLoop that it's time to exit cleanly.
			GC_Print("Application calling requestExit(), beginning shutdown sequence.");
			gWantExit = true;
		}

		any GenericPlatformOperations::fetchWindowObject() {
			GC_Warn("fetchWindowObject() is not implemented on the generic platform.");
			return NULL;
		}

		void GenericPlatformOperations::fetchEnvVar(const TCHAR *varName, TCHAR *result, S32 length) {
			GC_Warn("fetchEnvVar() is not implemented on the generic platform.");
			*result = NULL;
		}

		String GenericPlatformOperations::fetchMACAddr() {
			String result;
			DynArray<U8> macAddr = PlatformOperations::fetchMACRaw();
			for (S32 i = 0; i < macAddr.size(); i++) {
				result += String::ToStr("%02x", macAddr[i]);
			}
			return result;
		}

		DynArray<U8> GenericPlatformOperations::fetchMACRaw() {
			GC_Warn("fetchMACRaw() is not implemented on the generic platform.");
			return DynArray<U8>(0);
		}

		void GenericPlatformOperations::strictMemory() {
			GC_Warn("strictMemory() is not implemented on the generic platform.");
		}

		bool GenericPlatformOperations::platformMessagesAllowed() {
			return true;
		}

		bool GenericPlatformOperations::platformAllowsLocalCaching() {
			return true;
		}

	};

};