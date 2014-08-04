/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* strTools.cpp
*
* Defines support functions for Strings
**/

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		bool StrTools::fetchCmdLineToken(UTF16 &str, String &result, bool useEscapeChars) {
			//Empty the result out (since this is a cummulative function), then skip over anything that is whitespace
			result.clear();
			bool isInQuote = false;
			while (isWSpace(*str)) {
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
					if (currentChar == NULL || (isWSpace(currentChar) && !isInQuote)) {
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