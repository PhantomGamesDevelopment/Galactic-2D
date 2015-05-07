/**
* Galactic 2D
* Source/EngineCore/Tools/guid.cpp
* Defines a platform independant wrapper for "Globally Unique IDs" (GUIDs) that can be used throughout the engine
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

		galacticGUID galacticGUID::createGUID() {
			galacticGUID outGuid;
			PlatformOperations::createGUID(outGuid);
			return outGuid;
		}

		U32& galacticGUID::operator[](S32 index) {
			if (index < 0 || index >= 4) {
				//ToDo: Assert Here
				GC_CError("galacticGUID[%i]: Attempting to access invalid GUID index.", index);
			}
			switch (index) {
			case 0:
				return A;
			case 1:
				return B;
			case 2:
				return C;
			case 3:
				return D;
			}
			return A;
		}

		Z32& galacticGUID::operator[](S32 index) const {
			if (index < 0 || index >= 4) {
				//ToDo: Assert Here
				GC_CError("galacticGUID[%i]: Attempting to access invalid GUID index.", index);
			}
			switch (index) {
			case 0:
				return A;
			case 1:
				return B;
			case 2:
				return C;
			case 3:
				return D;
			}
			return A;
		}

		String& galacticGUID::operator>>(String inStr) {
			return toStr();
		}

		galacticGUID& galacticGUID::operator<<(String inStr) {
			galacticGUID g;
			strToGUID(inStr, g);
			return g;
		}

		String galacticGUID::toStr(guidFormatTypes t) const {
			// See http://en.wikipedia.org/wiki/Globally_unique_identifier for information regarding how to form the string...
			switch (t) {
				case NumericalString:
					return String::ToStr("%08X%08X%08X%08X", A, B, C, D);
				case HyphenatedBlock:
					return String::ToStr("%08X-%04X-%04X-%04X-%04X%08X", A, B >> 16, B & 0xFFFF, C >> 16, C & 0xFFFF, D);
				case OSHexBlock:
					//NOTE: We add the spaces to make things look neater, the 'True' format doesn't have spaces, our functions compensate for this before parsing.
					return String::ToStr("{0x%08X, 0x%04X, 0x%04X, {0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X}}",
						A, B >> 16, B & 0xFFFF, C >> 24, (C >> 16) & 0xFF, (C >> 8) & 0xFF, C & 0xFF, D >> 24, (D >> 16) & 0xFF, (D >> 8) & 0xFF, D & 0xFF);

			}
		}

		bool galacticGUID::isInCorrectFormat(String &inStr, guidFormatTypes inFormat) {
			//Fetch a copy of the string, empty the spaces...
			String strCopy(inStr);
			strCopy.replace(" ", "");
			switch (inFormat) {
				case NumericalString:
					//As long as we have 32 characters.. we're ok
					if (strCopy.length() != 32) {
						return false;
					}
					return true;

				case HyphenatedBlock:
					//The length should be 36 characters long.
					if (strCopy.length() != 36) {
						return false;
					}
					//If we have 36 characters, make sure it's in the correct block format
					if ((strCopy[8] != '-') || (strCopy[13] != '-') || (strCopy[18] != '-') || (strCopy[23] != '-')) {
						return false;
					}
					//All good!
					return true;

				case OSHexBlock:
					//The length should be 68 characters long.
					if (strCopy.length() != 68) {
						return false;
					}
					//Again, we look for the block format. 
					if ((strCopy[0] != '{') || (strCopy[1] != '0') || (strCopy[2] != 'x') || (strCopy[11] != ',') || (strCopy[12] != '0') || 
						(strCopy[13] != 'x') || (strCopy[18] != ',') || (strCopy[19] != '0') || (strCopy[20] != 'x') || (strCopy[25] != ',') || 
						(strCopy[26] != '{') || (strCopy[27] != '0') || (strCopy[28] != 'x') || (strCopy[31] != ',') || (strCopy[32] != '0') ||
						(strCopy[33] != 'x') || (strCopy[36] != ',') || (strCopy[37] != '0') || (strCopy[38] != 'x') || (strCopy[41] != ',') ||
						(strCopy[42] != '0') || (strCopy[43] != 'x') || (strCopy[46] != ',') || (strCopy[47] != '0') || (strCopy[48] != 'x') || 
						(strCopy[51] != ',') || (strCopy[52] != '0') || (strCopy[53] != 'x') || (strCopy[56] != ',') || (strCopy[57] != '0') ||
						(strCopy[58] != 'x') || (strCopy[61] != ',') || (strCopy[62] != '0') || (strCopy[63] != 'x') || (strCopy[66] != '}') ||
						(strCopy[67] != '}')) {
						return false;
					}
					//Passed, therefore good!
					return true;

				default:
					GC_Error("galacticGUID::isInCorrectFormat(): Unknown format sent to function, breaking...");
			}
			//Call fell through, something went wrong...
			return false;
		}

		bool galacticGUID::strToGUID(String &inStr, galacticGUID &outGuid) {
			//This is simply a utility tool to bypass the third argument, we'll do the test here...
			String strCopy(inStr);
			strCopy.replace(" ", "");
			if (strCopy.length() == 32) {
				return strToGUID(strCopy, outGuid, NumericalString);
			}
			else if (strCopy.length() == 36) {
				return strToGUID(strCopy, outGuid, HyphenatedBlock);
			}
			else if (strCopy.length() == 68) {
				return strToGUID(strCopy, outGuid, OSHexBlock);
			}
			else {
				GC_Error("galacticGUID::strToGUID(str, guid): Invalid format sent to this function.");
				return false;
			}
		}

		bool galacticGUID::strToGUID(String &inStr, galacticGUID &outGuid, guidFormatTypes inFormat) {
			//If we're not in the correct format, then there's no need to continue...
			if (!isInCorrectFormat(inStr, inFormat)) {
				return false;
			}
			String strCopy(inStr), strResult;
			strCopy.replace(" ", "");
			switch (inFormat) {
				case NumericalString:
					strResult = strCopy;
					break;

				case HyphenatedBlock:
					strResult = strCopy.substr(0, 8);
					strResult += strCopy.substr(9, 4);
					strResult += strCopy.substr(14, 4);
					strResult += strCopy.substr(19, 4);
					strResult += strCopy.substr(24, 12);
					break;

				case OSHexBlock:
					strResult = strCopy.substr(3, 8);
					strResult += strCopy.substr(14, 4);
					strResult += strCopy.substr(21, 4);
					strResult += strCopy.substr(29, 2);
					strResult += strCopy.substr(34, 2);
					strResult += strCopy.substr(39, 2);
					strResult += strCopy.substr(44, 2);
					strResult += strCopy.substr(49, 2);
					strResult += strCopy.substr(54, 2);
					strResult += strCopy.substr(59, 2);
					strResult += strCopy.substr(64, 2);
					break;

				default:
					GC_Error("galacticGUID::strToGUID(str, guid, format): Invalid format sent to this function.");
			}
			//Validate that the GUID resultant contains only hex digits
			for (S32 i = 0; i < strResult.length(); i++) {
				if (!CharTools::isHex(strResult[i])) {
					return false;
				}
			}
			//Once we've validated the hex, we can actually convert the string to a GUID, which is simply converting the hexadecimal into a U32...
			outGuid = galacticGUID(StrTools::hexToU32((strResult.substr(0, 8).c_str())),
				StrTools::hexToU32((strResult.substr(8, 8).c_str())),
				StrTools::hexToU32((strResult.substr(16, 8).c_str())),
				StrTools::hexToU32((strResult.substr(24, 8).c_str())));
			return true;
		}

	};

};