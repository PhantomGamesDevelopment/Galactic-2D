/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* strTools.h
*
* Defines support functions for Strings
**/

#ifndef GALACTIC_INTERNAL_STRING_TOOLS
#define GALACTIC_INTERNAL_STRING_TOOLS

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		StrTools: A Global instance of methods and operations to work with and manipulate strings and instances of strings.
		*/
		struct StrTools {

			//isWSpace(): Returns true if the specified character is a whitespace char.
			SFIN bool isWSpace(C8 c) {
				return (c == ' ' || c == '\t');
			}

			//fetchCmdLineToken(): Fetches a portion of a string based on a token deliminator for the command line
			// Note: Command line params are formatted as such: -param:"args"
			static bool fetchCmdLineToken(UTF16 &str, String &result, bool useEscapeChars);

		};

	};

};

#endif //GALACTIC_INTERNAL_STRING_TOOLS