/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/platformOperations.cpp
* Additional platform functions that are kept outside of the function lib for compatibility
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

		bool GenericPlatformOperations::fetchRegistryItem(const String &Key, const String &Value, bool useUser, String &result) {
			GC_Warn("fetchRegistryItem() is not implemented on the generic platform.");
			return false;
		}

		void GenericPlatformOperations::copyToClipboard(UTF16 text) {
			GC_Warn("copyToClipboard() is not implemented on the generic platform.");
		}

		void GenericPlatformOperations::pasteFromClipboard(String &trgStr) {
			GC_Warn("pasteFromClipboard() is not implemented on the generic platform.");
			trgStr = String::emptyStrRef;
		}

		void GenericPlatformOperations::createGUID(galacticGUID &inGuid) {
			TimeVars tV;
			PlatformTime::sysTime(tV);
			inGuid = galacticGUID(tV.dayNum | (tV.hours << 16), 
				tV.hours | (tV.minutes << 16), 
				tV.minutes | (tV.seconds << 16), 
				tV.miliseconds ^ PlatformTime::fetchCycles());
		}

		MBDefs::MBReturnType GenericPlatformOperations::OpenPlatformMB(MBDefs::MBTypes mbType, UTF16 mbText, UTF16 mbCaption) {
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

		U32 GenericPlatformOperations::getMappedKey(U16 *keyCodes, U32 maxMaps, String *keyNames) {
			GC_Warn("getMappedKey() is not implemented on the generic platform.");
			return 0;
		}

		U32 GenericPlatformOperations::getMappedChar(U16 *keyCodes, U32 maxMaps, String *keyNames) {
			GC_Warn("getMappedChar() is not implemented on the generic platform.");
			return 0;
		}

		UTF16 GenericPlatformOperations::getRootDir() {
			GC_Warn("getRootDir(): This method is not implemented on the generic platform.");
			return "";
		}

		UTF16 GenericPlatformOperations::fetchPlatformSeparator() {
			return "/";
		}

		void GenericPlatformOperations::normalizePath(String &inPath) {
			GC_Warn("normalizePath(): This method is not implemented on the generic platform.");
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

		void GenericPlatformOperations::fetchEnvVar(UTF16 varName, UTF8 result, S32 length) {
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

		void GenericPlatformOperations::pumpMessages(bool fromMainLoop) {
			//Stub Function...
		}

		U32 GenericPlatformOperations::fetchStandardKeyMap(U16 *keyCodes, U32 maxMaps, String *keyNames, bool mapUppercase, bool mapLowercase) {
			U32 totalMaps = 0;
			/* Map Numerical Keys */
			MAPKEY_fetchStandardKeyMap("Zero", '0');
			MAPKEY_fetchStandardKeyMap("One", '1');
			MAPKEY_fetchStandardKeyMap("Two", '2');
			MAPKEY_fetchStandardKeyMap("Three", '3');
			MAPKEY_fetchStandardKeyMap("Four", '4');
			MAPKEY_fetchStandardKeyMap("Five", '5');
			MAPKEY_fetchStandardKeyMap("Six", '6');
			MAPKEY_fetchStandardKeyMap("Seven", '7');
			MAPKEY_fetchStandardKeyMap("Eight", '8');
			MAPKEY_fetchStandardKeyMap("Nine", '9');
			/* Map Other Standard Keys */
			MAPKEY_fetchStandardKeyMap("Tilde", '`');
			MAPKEY_fetchStandardKeyMap("Underscore", '-');
			MAPKEY_fetchStandardKeyMap("Equals", '=');
			MAPKEY_fetchStandardKeyMap("Left Bracket", '[');
			MAPKEY_fetchStandardKeyMap("Right Bracket", ']');
			MAPKEY_fetchStandardKeyMap("Backslash", '\\'); //<- Don't forget that '\' is an escape sequence terminator...
			MAPKEY_fetchStandardKeyMap("Semicolon", ';');
			MAPKEY_fetchStandardKeyMap("Quote", '\''); //<- The ' character requres a terminator sequence...
			MAPKEY_fetchStandardKeyMap("Comma", ',');
			MAPKEY_fetchStandardKeyMap("Period", '.');
			MAPKEY_fetchStandardKeyMap("Slash", '/');
			MAPKEY_fetchStandardKeyMap("Spacebar", ' ');
			/* Map Characters */
			//Do we need to map the uppercase letters?
			if (mapUppercase) {
				MAPKEY_fetchStandardKeyMap("A", 'A');
				MAPKEY_fetchStandardKeyMap("B", 'B');
				MAPKEY_fetchStandardKeyMap("C", 'C');
				MAPKEY_fetchStandardKeyMap("D", 'D');
				MAPKEY_fetchStandardKeyMap("E", 'E');
				MAPKEY_fetchStandardKeyMap("F", 'F');
				MAPKEY_fetchStandardKeyMap("G", 'G');
				MAPKEY_fetchStandardKeyMap("H", 'H');
				MAPKEY_fetchStandardKeyMap("I", 'I');
				MAPKEY_fetchStandardKeyMap("J", 'J');
				MAPKEY_fetchStandardKeyMap("K", 'K');
				MAPKEY_fetchStandardKeyMap("L", 'L');
				MAPKEY_fetchStandardKeyMap("M", 'M');
				MAPKEY_fetchStandardKeyMap("N", 'N');
				MAPKEY_fetchStandardKeyMap("O", 'O');
				MAPKEY_fetchStandardKeyMap("P", 'P');
				MAPKEY_fetchStandardKeyMap("Q", 'Q');
				MAPKEY_fetchStandardKeyMap("R", 'R');
				MAPKEY_fetchStandardKeyMap("S", 'S');
				MAPKEY_fetchStandardKeyMap("T", 'T');
				MAPKEY_fetchStandardKeyMap("U", 'U');
				MAPKEY_fetchStandardKeyMap("V", 'V');
				MAPKEY_fetchStandardKeyMap("W", 'W');
				MAPKEY_fetchStandardKeyMap("X", 'X');
				MAPKEY_fetchStandardKeyMap("Y", 'Y');
				MAPKEY_fetchStandardKeyMap("Z", 'Z');
			}
			//Do we need to map the lowercase letters?
			if (mapLowercase) {
				MAPKEY_fetchStandardKeyMap("a", 'a');
				MAPKEY_fetchStandardKeyMap("b", 'b');
				MAPKEY_fetchStandardKeyMap("c", 'c');
				MAPKEY_fetchStandardKeyMap("d", 'd');
				MAPKEY_fetchStandardKeyMap("e", 'e');
				MAPKEY_fetchStandardKeyMap("f", 'f');
				MAPKEY_fetchStandardKeyMap("g", 'g');
				MAPKEY_fetchStandardKeyMap("h", 'h');
				MAPKEY_fetchStandardKeyMap("i", 'i');
				MAPKEY_fetchStandardKeyMap("j", 'j');
				MAPKEY_fetchStandardKeyMap("k", 'k');
				MAPKEY_fetchStandardKeyMap("l", 'l');
				MAPKEY_fetchStandardKeyMap("m", 'm');
				MAPKEY_fetchStandardKeyMap("n", 'n');
				MAPKEY_fetchStandardKeyMap("o", 'o');
				MAPKEY_fetchStandardKeyMap("p", 'p');
				MAPKEY_fetchStandardKeyMap("q", 'q');
				MAPKEY_fetchStandardKeyMap("r", 'r');
				MAPKEY_fetchStandardKeyMap("s", 's');
				MAPKEY_fetchStandardKeyMap("t", 't');
				MAPKEY_fetchStandardKeyMap("u", 'u');
				MAPKEY_fetchStandardKeyMap("v", 'v');
				MAPKEY_fetchStandardKeyMap("w", 'w');
				MAPKEY_fetchStandardKeyMap("x", 'x');
				MAPKEY_fetchStandardKeyMap("y", 'y');
				MAPKEY_fetchStandardKeyMap("z", 'z');
			}
			return totalMaps;
		}

	};

};