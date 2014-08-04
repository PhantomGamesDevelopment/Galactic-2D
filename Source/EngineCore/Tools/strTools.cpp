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
			while (isWSpace(*str)) {
				str++;
			}
			//First thing we're looking for here is the instance of the " char
			if (*str == '"') {
				str++;
				while (*str && *str != '"') {
					C8 currentChar = *str++;
					if (useEscapeChars && currentChar == '\\') {

					}
				}
			}
		}

	};

};