/**
* Galactic 2D
* Source/EngineCore/Tools/string.h
* Defines a standardized String class instance
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

#ifndef GALACTIC_INTERNAL_STRING
#define GALACTIC_INTERNAL_STRING

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		Galactic Engine String Class. This is a widely used class throughout the engine as it provides a full String
		module outside that of the C++ STL, the functioning of it is very similar to that of std::string, as well as some extended
		functioning not included in the std::string class.
		*/
		class String {
			public:
				//String formatting class used by all of the ToString operations
				class StringFormat;

				//StringData contains all of the String's information, and is used to actually "build" the string.
				class StringData;

				//String Utility Enumeration, This is used in numerous places for find functions, and compare functions
				enum StrMode {
					CaseSens = 0,   /* String searching will be case sensitive */
					NoCaseSens = 1, /* String searching will not be case sensitive */
					Left = 0,       /* String searching starts on the left (Standard Function, Shares value w/ CaseSens) */
					Right = 2,      /* String searching starts on the right. */
				};

				//This is a constant value for string find functions specifying "not found" in string, defined as U32(~0)
				static Z32 NOTFOUND;
				//Empty String Reference.
				static const String emptyStrRef;

				/* General String Functions */
				//Generic Constructor
				String();
				//Construct a String by copying another string instance
				String(const String &str);
				//Construct a string from a const char *.
				String(UTF16 str);
				//Construct a string using a pre-defined size from a const char * instance
				String(UTF16 str, U32 size);
				//Destructor.
				~String();

				/*Converts String to standard C/C++ UTF16 type, for those of you who actually want to use std::string 
				  this function can be used here to convert: String sample = "My String"; std::string myStr(sample.c_str()); */
				UTF16 c_str() const;
				//Returns the length of the string in bytes.
				U32 length() const;
				//Returns the full size of the string, including the /0 terminator.
				U32 size() const;
				//Returns the character length of the string.
				U32 numChrs() const;
				//Is the string empty?
				bool empty() const;

				//Delete the entire string.
				void clear();

				/* String Tools */
				//Compare two strings using a UTF16 reference.
				S32 compare(UTF16 str, U32 len = 0, U32 mode = CaseSens | Left) const;
				//Compare two strings using a String reference.
				S32 compare(const String &str, U32 len = 0, U32 mode = CaseSens | Left) const;
				//Find an instance of a Character in our string
				U32 find(C8 needle, U32 startPos = 0, U32 mode = CaseSens | Left) const; 
				//Find an instance of a UTF16 in our string
				U32 find(UTF16 needle, U32 startPos = 0, U32 mode = CaseSens | Left) const; 
				//Find an instance of a String in our string
				U32 find(const String &needle, U32 startPos = 0, U32 mode = CaseSens | Left) const; 
				//Insert a UTF16 into the current string at a specified position
				String &insert(U32 position, UTF16 str);
				//Insert a String into the current string at a specified position
				String &insert(U32 position, const String &ref);
				//Erase a section of the string
				String &erase(U32 position, U32 len);
				//Replace all instances contained in the string with another.
				String &replace(const String &search, const String &replace);
				//Replace current string contents with another's contents in the specified area
				String &replace(U32 startPos, U32 len, const String &str);
				//Extract a portion of the current string
				String substr(U32 startPosition, U32 len = -1) const;
				//Test if the string starts with the specified string
				bool startsWith(const String &testStr, U32 mode = NoCaseSens) const;
				//Test if the string starts with the specified string (UTF16 variant)
				bool startsWith(UTF16 testStr, U32 mode = NoCaseSens) const;
				//Test if the string ends with the specified string
				bool endsWith(const String &testStr, U32 mode = NoCaseSens) const;
				//Test if the string ends with the specified string (UTF16 variant)
				bool endsWith(UTF16 testStr, U32 mode = NoCaseSens) const;
				//Trim whitespace from the string.
				String trim() const;
				//Split string into numerous delimitors based on input token
				void split(UTF16 token, Vector<String> &ref) const;

				//Utility function used to convert pointer arguments into a String.
				static String VoidToStr(UTF16 format, void* args);
				//Converts a standard C++ string format w/ args into a String
				static String ToStr(UTF16 format, ...);
				//Converts a boolean into a String
				static String ToStr(bool v);
				//Convert a U32 into a String
				static String ToStr(U32 v);
				//Convert a S32 into a String
				static String ToStr(S32 v);
				//Convert a F32 into a String
				static String ToStr(F32 v);
				//Convert a F64 into a String
				static String ToStr(F64 v);

				//Converts all string characters to lowercase
				static String ToLwr(const String &str);
				//Converts all string characters to uppercase
				static String ToUpr(const String &str);

				/* String Operators */
				//Set string equal to a single character.
				String& operator=(C8 c);
				//Add a single character to the end of a string.
				String& operator+=(C8 c);
				//Set string equal to the contents of a UTF16.
				String& operator=(UTF16 s);
				//Add a UTF16's contents to the end of a string.
				String& operator+=(UTF16 s);
				//Set a string equal to another string.
				String& operator=(const String &s);
				//Add the contents of one string to another.
				String& operator+=(const String &s);
				/* Specials. These next five are defined specially such to allow addition syntax in other C++ files. */
				//Add String to String
				friend String operator+(const String &s1, const String &s2);
				//Add C8 to String
				friend String operator+(const String &s, C8 chr);
				//Add String to C8
				friend String operator+(C8 chr, const String &s);
				//Add UTF16 to String
				friend String operator+(const String &s, UTF16 str);
				//Add String to UTF16
				friend String operator+(UTF16 str, const String &s);
				/* Normal Operators Cont. */
				//Check to see if two strings are equal.
				bool operator==(const String &s) const;
				//Check to see if two strings are not equal
				bool operator!=(const String& r) const { return !(*this == r); }
				//Check to see if our string is equal to a single character
				bool operator==(C8 c) const;
				//Check to see if our string is not equal to a single character
				bool operator!=(C8 r) const { return !(*this == r); }
				//Get a single character
				C8 operator[](S32 index) const;
				//See above, use a U32 index
				C8 operator[](U32 index) const;
		
			private:
				//Private String Constructor, Used to pre-define the internal StringData pointer
				String(StringData *s) : _str(s) {}
				//String copy function.
				static void copy(UTF16 source, UTF8 destination, U32 size);
				//Internal StringData pointer, holds all of the String information for usage by String
				StringData *_str;
				//Maximum string size
				static Z32 maxStringSize;
		};

		//Some useful typedefs
		//Constant Reference String
		typedef const String &strRef;

	};

};

#endif //GALACTIC_INTERNAL_STRING