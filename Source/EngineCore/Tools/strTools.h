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

		//String Tools...
		// Used to do things with strings...

		/**
		getToken() - This allows you to pull a piece of a token deliminated string out.
		EX: getToken("Str1\tStr2\tStr3", "\t", 1) == Str2
		**/
		UTF16 getToken(UTF16 str, UTF16 token, S32 index) {
			UTF8 result = strtok(const_cast<UTF8>(str), token);
			while(result != NULL) {
				if(index-- < 0) {
					return result;
				}
				result = strtok(NULL, token); //<--- First param NULL tells the function to use the existing string buffer.
			}
			return NULL;
		}

		/**
		getTokenCount() - Returns the amount of token deliminated strings exist in a parameter given
		EX: getTokenCount("Str1\tStr2\tStr3", "\t") == 3
		**/
		S32 getTokenCount(UTF16 str, UTF16 token) {
			S32 counter = 0;
			UTF8 result = strtok(const_cast<UTF8>(str), token);
			while(result != NULL) {
				counter++;
				result = strtok(NULL, token);
			}
			return counter;
		}

	};

};

#endif //GALACTIC_INTERNAL_STRING_TOOLS