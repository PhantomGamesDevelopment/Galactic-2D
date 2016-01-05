/**
* Galactic 2D
* Source/EngineCore/Tools/strTools.h
* Defines a list of tools and functions to help with string data processing
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

#ifndef GALACTIC_INTERNAL_STRING_TOOLS
#define GALACTIC_INTERNAL_STRING_TOOLS

namespace Galactic {

	namespace Core {

		/*
		StrTools: A Global instance of methods and operations to work with and manipulate strings and instances of strings.
		*/
		struct StrTools {

			//fetchCmdLineToken(): Fetches a portion of a string based on a token deliminator for the command line
			// Note: Command line params are formatted as such: -param:"args"
			static bool fetchCmdLineToken(UTF16 &str, String &result, bool useEscapeChars);

			//strnicmp is one of those MSVS depricated thingies, however, it's fully safe for use still, so ignore the annoying C4996 warn.
			#pragma warning( push )
			#pragma warning( disable : 4996 )
			//find(): Find an instance of a string within another string
			static UTF16 find(UTF16 str, UTF16 wantToFind) {
				if (!str || !wantToFind) {
					return NULL;
				}
				S32 findLength = (S32)strlen(wantToFind++) - 1;
				C8 findChar = *wantToFind;
				C8 currChar = *str++;
				while (currChar) {
					if (findChar == currChar && !strnicmp(str, wantToFind, findLength)) {
						return str - 1;
					}
					currChar = *str++;
				}
				return NULL;
			}
			#pragma warning( pop )

			static U32 hexToU32(UTF16 hexStr) {
				U32 res = 0;
				while (*hexStr) {
					res *= 16;
					res += CharTools::hexToDigit(*hexStr++);
				}
				return res;
			}

		};

	};

};

#endif //GALACTIC_INTERNAL_STRING_TOOLS