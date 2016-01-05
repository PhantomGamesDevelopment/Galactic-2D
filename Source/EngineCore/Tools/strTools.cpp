/**
* Galactic 2D
* Source/EngineCore/Tools/strTools.cpp
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

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		bool StrTools::fetchCmdLineToken(UTF16 &str, String &result, bool useEscapeChars) {
			//Empty the result out (since this is a cummulative function), then skip over anything that is whitespace
			result.clear();
			bool isInQuote = false;
			while (CharTools::isWSpace(*str)) {
				str++;
			}
			//First thing we're looking for here is the instance of the " char
			if (*str == '"') {
				str++;
				while (*str && *str != '"') {
					C8 currentChar = *str++;
					if (useEscapeChars && currentChar == '\\') {
						//Fetch the escape char.
						currentChar = *str++;
						if (!currentChar) {
							break;
						}
					}
					result += currentChar;
				}
				if (*str == '"') {
					str++;
				}
			}
			else {
				//If the text isn't a ", then we're possibly inside a block of arguments that contains a spaced instance of sub-args
				isInQuote = false;
				//Note: There's probably a better loop option than this out there, but for now, we should be fine.
				while (true) {
					C8 currentChar = *str;
					if (currentChar == NULL || (CharTools::isWSpace(currentChar) && !isInQuote)) {
						//This isn't part of a token, goodbye!
						break;
					}
					str++;
					//Are we using escape chars? If so, those also need to be stored in the result.
					if (isInQuote && useEscapeChars && currentChar == '\\') {
						result += currentChar;
						currentChar = *str;
						if (!currentChar) {
							break;
						}
						str++;
					}
					else if (currentChar == '"') {
						isInQuote = !isInQuote;
					}
					result += currentChar;
				}
			}
			return result.length() > 0;
		}

	};

};