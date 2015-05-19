/**
* Galactic 2D
* Source/EngineCore/Tools/string.cpp
* Defines a standardized String class instance
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
#include "string.h"

namespace Galactic {

	namespace Core {

		Z32 String::maxStringSize = 2048;

		Z32 String::NOTFOUND = U32(~0);

		/**
			StringFormat:
			This class is used by the numerous ToStr() functions down below to convert the va_list parameters and relevant pointer information
			into their proper string counterparts.
		**/
		class String::StringFormat {
			typedef va_list* valptr;

			public:
				//Fixed Buffer (Only place in String where maxStringSize is currently enforced, someone with more C++ knowledge could possibly get around this limit)
				C8 _strBuff[maxStringSize]; 
				//Temporary Formatting Buffer
				UTF8 _dynBuff;
				//Size of _dynBuff
				U32 _dynLen;
				//size of _strBuff
				U32 _strLen;

				StringFormat() : _dynBuff(NULL), _dynLen(0), _strLen(0) {
					_strBuff[0] = '\0';
				}

				StringFormat(UTF16 str, any args) : _dynBuff(NULL), _dynLen(0), _strLen(0) {
					format(str, args);
				}

				~StringFormat() {
					if(_dynBuff) {
						SendToGatesOfHeaven(_dynBuff);
					}
				}

				S32 format(UTF16 str, any args) {
					_strLen = 0;
					return formatAppend(str, args);
				}
				
				S32 formatAppend(UTF16 str, any args) {
					//This is a two step process, first we need to format the string into the fixed buffer, in the event
					// of a failure at the second step, we'll at least have the fixed string to reference.
					S32 firstLength = _strLen;
					if(_dynBuff == NULL) {
						_strLen += _vsnprintf(_strBuff + _strLen, sizeof(_strBuff) - _strLen, str, *(valptr)args);
						if(_strLen >= 0 && _strLen < sizeof(_strBuff)) {
							return _strLen;
						}
						//Now that we've got our fixed buffer, we can begin construction of the dynamic buffer, we'll start with a size two times
						// larger than that of the fixed buffer to prevent anything from going wrong with out-of-bounds sizing later.
						_strLen = firstLength;
						_dynLen = sizeof(_strBuff) * 2;
						_dynBuff = (UTF8)malloc(_dynLen);
						memcpy(_dynBuff, _strBuff, _strLen+1);
					}
					//At this point, if the dynamic buffer wasn't empty, we can now safely use the same formatting step to format into the dynamic buffer.
					// to ensure we're ok on size, we'll keep doubling the buffer until we have a working case.
					_strLen += _vsnprintf(_dynBuff + _strLen, _dynLen - _strLen, str, *(valptr)args);
					while(_strLen < 0 || _strLen >= _dynLen) {
						_strLen = firstLength;
						_dynBuff = (UTF8)realloc(_dynBuff, _dynLen *= 2); //Note the multiplicative operator here to catch the change as well.
						_strLen += _vsnprintf(_dynBuff + _strLen, _dynLen - _strLen, str, *(valptr)args);
					}
					return _strLen;
				}
				
				S32 append(UTF16 str, S32 len) {
					//This function is here to append to the current formatting buffer. We take care of all of the 
					// re-sizing and such throughout this function.
					if(_dynBuff == NULL) {
						if(_strLen + len >= 0 && _strLen + len < sizeof(_strBuff)) {
							memcpy(_strBuff + _strLen, str, len);
							_strLen += len;
							_strBuff[_strLen] = '\0';
							return _strLen;
						}
						_dynLen = sizeof(_strBuff) * 2;
						_dynBuff = (UTF8)malloc(_dynLen);
						memcpy(_dynBuff, _strBuff, _strLen + 1);
					}
					//Validation step...
					U32 newSize = _dynLen;
					while(newSize < _strLen + len) {
						newSize *= 2;
					}
					if(newSize != _dynLen) {
						_dynBuff = (UTF8)realloc(_dynBuff, newSize);
					}
					_dynLen = newSize;
					memcpy(_dynBuff + _strLen, str, len);
					_strLen += len;
					_dynBuff[_strLen] = '\0';
					return _strLen;
				}
				
				S32 append(UTF16 str) {
					return append(str, (U32)strlen(str));
				}

				String becomeString() {
					return String(c_str(), _strLen);
				}

				UTF16 c_str() {
					return _dynBuff ? _dynBuff : _strBuff;
				}

				void reset() {
					_strBuff[0] = '\0';
					_strLen = 0;
				}

				UTF8 copyBuffer(UTF8 dest) const {
					memcpy(dest, _dynBuff ? _dynBuff : _strBuff, _strLen+1);
					return dest;
				}

				U32 length() const { 
					return _strLen; 
				}
		};

		/**
			StringData:
			This class is more or less a storage container, since there's actually quite a bit going on here, this cuts down on the actual amount
			of redundant code in the actual class, not to mention it helpsto pin down any problems with the String class itself.
		**/
		class String::StringData {
			public:
				StringData() {}

				StringData(UTF16 data) {
					refCount = 1;
					numChars = U32(0xffffffff);
					if(data) {
						//see operator new for initialization of length
						memcpy(sData, data, sizeof(UTF8) * length);
						sData[length] = '\0';
					}
				}

				~StringData() {
				}

				bool hasMultipleReferences() const {
					return (refCount > 1);
				}

				void addRef() {
					//Kind of redundant, but you know, someday, someone's going to do this just for a laugh.
					if(refCount != U32(0xffffffff)) {
						refCount++;
					}
				}

				void killRef() {
					if(refCount != U32(0xffffffff)) {
						refCount--;
						if(refCount == 0) {
							delete this;
						}
					}
				}

				U32 getLength() {
					return length;
				}

				U32 getSize() {
					return getLength() + 1;
				}

				U32 getNumChars() const {
					if(numChars == U32(0xffffffff)) {
						numChars = (U32)strlen((UTF16)sData);
					}
					return numChars;
				}

				C8 operator[](U32 index) {
					if(index >= length) {
						return NULL;
						//push an error here?
					}
					return sData[index];
				}

				UTF8 utf8() {
					return sData;
				}

				UTF16 utf16() {
					return sData;
				}

				static StringData *emptyStrRef() {
					static StringData empty;
					empty.refCount = U32(0xffffffff);
					empty.length = 0;
					empty.numChars = 0;
					empty.sData[1] = 0;

					return (StringData *)&empty;
				}
				
				//Allows length defining a la: new (length) StringData(x)
				any operator new(size_t size, U32 len) {
					if(len == 0) {
						GC_Error("StringData::StringData(): Cannot create a String of length 0, use StringData::emptyStrRef()");
						return NULL;
					}
					StringData *data = reinterpret_cast<StringData *>(malloc(size + len * sizeof(UTF8)));
					data->length = len;
					return data;
				}

				//This definition of delete is used to match the above new operator, stops C4291
				void operator delete(any ptr, U32 len) {
					StringData* sub = static_cast<StringData *>(ptr);
					if(sub->refCount != 0) {
						GC_Error("StringData::delete() - Attempting to delete a String containing multiple references attached (%i).", sub->refCount);
						return;
					}
					SendToGatesOfHeaven(ptr);
				}

				void operator delete(any ptr) {
					StringData* sub = static_cast<StringData *>(ptr);
					if(sub->refCount != 0) {
						GC_Error("StringData::delete() - Attempting to delete a String containing multiple references attached (%i).", sub->refCount);
						return;
					}
					SendToGatesOfHeaven(ptr);
				}

			protected:
				//amount of references to the StringData
				U32 refCount;
				//length of the StringData, not including NULL
				U32 length;
				//character count, mutable for usage through const functions
				mutable U32 numChars;
				//This is the actual data of the string.
				C8 sData[1];
		};

		String::String() {
			_str = StringData::emptyStrRef();
		}

		String::String(strRef str) {
			_str = str._str;
			_str->addRef();
		}

		String::String(UTF16 str) {
			if(str && *str) {
				U32 len = (U32)strlen(str);
				_str = new (len) StringData(str);
			}
			else {
				_str = StringData::emptyStrRef();
			}
		}

		String::String(UTF16 str, U32 size) {
			if(str && *str && size != 0) {
				if(size > strlen(str)) {
					//push an error here for invalid size.
					_str = NULL;
				}
				else {
				   _str = new (size) StringData(str);
				}
			}
			else {
				_str = StringData::emptyStrRef();
			}
		}

		String::~String() {
			_str->killRef();
		}

		UTF16 String::c_str() const {
			return _str->utf16();
		}

		U32 String::length() const {
			return _str->getLength();
		}

		U32 String::size() const {
			return _str->getSize();
		}

		U32 String::numChrs() const {
			return _str->getNumChars();
		}

		bool String::empty() const {
			return (_str == StringData::emptyStrRef());
		}

		void String::clear() {
			_str->killRef();
			_str = NULL;
			_str = StringData::emptyStrRef();
		}

		S32 String::compare(UTF16 str, U32 len, U32 mode) const {
			if(!str) {
				GC_Error("String::compare(NULL, %i, %i): Cannot use compare on the target string. It contains a NULL Ptr.", len, mode);
				return -1;
			}
			UTF16 s1 = _str->utf16();
			UTF16 s2 = str;
			//Compare the strings right away, if they match, we're done
			if(s1 == s2) {
				return 0;
			}
			//Right Search Property
			if(mode & String::Right) {
				U32 l = len;
				if(l > length()) {
					l = length();
				}
				s1 += length() - l;
				s2 += strlen(str) - l;
			}
			//No Case Sensitivity
			if(mode & String::NoCaseSens) {
				if(len) {
					//If we have a stored length, we can use a for loop to make this easy.
					for( ; len--; s1++, s2++) {
						if(tolower(*s1) != tolower(*s2) || !*s1) {
							//mismatch, we're done here.
							break;
						}
					}
				}
				else {
					//If we don't have a stored length, we use a while loop to run through each char. This time however, we check to see if the strings
					// match, and we run until we hit the end of s1.
					while(tolower(*s1) == tolower(*s2) && *s1) {
						s1++;
						s2++;
					}
				}
				//Return the integer result of the strcmp.
				return tolower(*s1) - tolower(*s2);
			}
			//If we were not in no-case mode, it's time to finish up the compare work.
			if(len) {
				//If we have a stored length, we can use memcmp to get a result on the fly.
				return memcmp(s1, s2, len);
			}
			else {
				//Otherwise, do a quick loop through the strings to get a result.
				while(*s1 == *s2 && *s1) {
					s1++;
					s2++;
				}
				return *s1 - *s2;
			}
		}

		S32 String::compare(strRef str, U32 len, U32 mode) const {
			if(_str == str._str) {
				return 0;
			}
			return compare(str.c_str(), len, mode);
		}

		U32 String::find(C8 needle, U32 startPos, U32 mode) const {
			UTF16 ourStr = _str->utf16();
			if(mode & Right) {	
				if(startPos) {
					ourStr += startPos - 1;
				}
				else {
					while(*ourStr) {
						ourStr++;
					}
				}
				if(mode & NoCaseSens) {
					needle = tolower(needle);
					for(; ourStr >= _str->utf16(); ourStr--) {
						if(tolower(*ourStr) == needle) {
							//got a match
							return U32(ourStr - _str->utf16());
						}
					}
				}
				else {
					for(; ourStr >= _str->utf16(); ourStr--) {
						if(*ourStr == needle) {
							//got a match
							return U32(ourStr - _str->utf16());
						}
					}					
				}
				return NOTFOUND;
			}
			else {
				if(mode & NoCaseSens) {
					needle = tolower(needle);
					for(ourStr += startPos; *ourStr && tolower(*ourStr) != needle;) {
						ourStr++;
					}
				}
				else {
					for(ourStr += startPos; *ourStr && *ourStr != needle;) {
						ourStr++;
					}
				}

				return *ourStr ? U32(ourStr - _str->utf16()) : NOTFOUND;
			}
		}

		U32 String::find(UTF16 needle, U32 startPos, U32 mode) const {
			UTF16 ourStr = _str->utf16();
			if(mode & Right) {
				UTF16 copy = ourStr; //Copy of the original for manipulation purposes.
				if(startPos) {
					copy += startPos - 1;
				}
				else {
					while(*copy) {
						copy++;
					}
				}
				if(mode & NoCaseSens) {
					UTF16 lcs = _strlwr(_strdup(needle));
					for(; copy >= ourStr; copy--) {
						if(tolower(*copy) == *lcs) {
							U32 index = 0;
							while(lcs[index] && lcs[index] == tolower(copy[index])) {
								index++;
							}
							if(!copy[index]) {
								free((char *)lcs);
								return U32(copy - _str->utf16());
							}
							if(!ourStr[index]) {
								free((char *)lcs);
								return NOTFOUND;
							}
						}
					}
				}
				else {
					for(; copy >= ourStr; copy--) {
						if(*copy == *needle) {
							U32 index = 0;
							while(needle[index] && needle[index] == copy[index]) {
								index++;
							}
							if(!needle[index]) {
								return U32(copy - _str->utf16());
							}
							if(!ourStr[index]) {
								return NOTFOUND;
							}
						}
					}
				}
				return NOTFOUND;
			}
			else {
				if(mode & NoCaseSens) {
					UTF16 lcs = _strlwr(_strdup(needle));
					for(ourStr += startPos; *ourStr; ourStr++) {
						if(tolower(*ourStr) == *lcs) {
							U32 index = 0;
							while(lcs[index] && lcs[index] == tolower(ourStr[index])) {
								index++;
							}
							if(!lcs[index]) {
								free((char *)lcs);
								return U32(ourStr - _str->utf16());
							}
							if(!ourStr[index]) {
								free((char *)lcs);
								return NOTFOUND;
							}
						}
					}
				}
				else {
					for(ourStr += startPos; *ourStr; ourStr++) {
						if(*ourStr == *needle) {
							U32 index = 0;
							while(needle[index] && needle[index] == ourStr[index]) {
								index++;
							}
							if(!needle[index]) {
								return U32(ourStr - _str->utf16());
							}
							if(!ourStr[index]) {
								return NOTFOUND;
							}
						}
					}
				}			
			}
			return NOTFOUND;
		}

		U32 String::find(strRef needle, U32 startPos, U32 mode) const {
			return find(needle.c_str(), startPos, mode);
		}

		String &String::insert(U32 position, UTF16 str) {
			if(!str) {
				GC_Error("String::insert(%i, NULL): Cannot insert NULL Ptr references into a String", position);
				THISREF();
			}
			U32 len[3] = { (U32)strlen(str), length(), (U32)strlen(str) + length() }; 
			if(position > len[1]) {
				GC_Error("String::insert(%i, %s): The specified position is outside of the String bounds", position, str);
				THISREF();
			}
			//Create the new string
			StringData *newStr;
			if(!len[2]) {
				newStr = StringData::emptyStrRef();
			}
			else {
				newStr = new (len[2]) StringData(NULL);
				copy(_str->utf16(), newStr->utf8(), position);
				copy(str, newStr->utf8() + position, len[0]);
				copy(_str->utf16(), newStr->utf8() + position + len[0], len[1] - position - 1);
			}
			_str->killRef();
			_str = newStr;
			THISREF();
		}

		String &String::insert(U32 position, strRef ref) {
			return insert(position, ref.c_str());
		}

		String &String::erase(U32 position, U32 len) {
			if(!len) {
				GC_Error("String::erase(%i, %i): Cannot erase 0 length from the string.", position, len);
				THISREF();
			}
			if((position + len) > length()) {
				GC_Error("String::erase(%i, %i): The specified values lie outside of the String's Length [%i]", position, len, length());
				THISREF();
			}
			U32 cLen = length();
			U32 nLen = cLen - len;
			//Create the new String
			StringData *newStr;
			if(!nLen) {
				newStr = StringData::emptyStrRef();
			}
			else {
				newStr = new (nLen) StringData(NULL);
				if(position > 0) {
					copy(_str->utf16(), newStr->utf8(), position);
				}
				copy(_str->utf16() + position + len, newStr->utf8() + position, cLen - (position - len) + 1);
			}
			_str->killRef();
			_str = newStr;
			THISREF();
		}

		String &String::replace(strRef search, strRef replace) {
			//Get our numerical values ready...
			Z32 &lenSrc = search.length(), &lenRep = replace.length();
			U32 cPos = 0;
			DynArray<U32> found_indicies;
			//Grab a copy of our string, and begin looping through, finding all instances of &search
			U32 findRes;
			do {
				findRes = find(search, cPos, CaseSens | Left);
				if(findRes != NOTFOUND) {
					cPos = findRes;
					found_indicies.pushToBack(cPos);
					cPos += lenSrc;
				}
			}while(findRes != NOTFOUND);
			//Test if we have entires to replace
			if(found_indicies.isEmpty()) {
				THISREF();
			}
			//And start the replacing
			U32 newSize = size() - (found_indicies.size() * lenSrc) + (found_indicies.size() * lenRep);
			StringData *newStr;
			if(newSize == 1) {
				//Unlike prior cases, this time a size value of 1 refers to empty (Null Terminator)
				newStr = StringData::emptyStrRef();
			}
			else {
				U32 nPos = 0, chrCt = 0;
				cPos = 0;
				newStr = new (newSize - 1) StringData(NULL);			
				for(U32 i = 0; i < (U32)found_indicies.size(); i++) {
					Z32 &index = found_indicies[i];
					//IF we have any chars to copy over before our next string to replace, this will keep the count.
					chrCt = index - cPos;
					if(chrCt > 0) {
						memcpy(newStr->utf8() + nPos, _str->utf8() + cPos, chrCt * sizeof(C8));
						nPos += chrCt;
					}
					//Copy the replacement.
					if(lenRep > 0) {
						memcpy(newStr->utf8() + nPos, replace._str->utf8(), lenRep * sizeof(C8));
					}
					nPos += lenRep;
					cPos = index + lenSrc;
				}
				//If there was some stuff after the last replacement, we need to put it back, do so now.
				// Note: We're safe to use .last without try-catch(DYNARRAYEMPTY) here because this is handled above already.
				chrCt = length() - found_indicies.last() - lenSrc;
				if(chrCt != 0) {
					memcpy(newStr->utf8() + nPos, _str->utf8() + cPos, chrCt * sizeof(C8));
				}
				newStr->utf8()[newSize - 1] = NULL;
			}
			_str->killRef();
			_str = newStr;
			THISREF();
		}

		String &String::replace(U32 startPos, U32 len, strRef str) {
			if(len == 0) {
				GC_Error("String::replace(%i, [%i], X): Cannot use replace operation with len == 0.", startPos, len);
				THISREF();				
			}
			if((startPos + len) > length()) {
				GC_Error("String::replace(%i, %i, X): Specified start position and length are outside string bounds.", startPos, len);
				THISREF();				
			}

			U32 lenV[3] = { length(), str.length(), (length() - len + str.length()) };
			StringData *strDat;
			if(!lenV[2]) {
				strDat = StringData::emptyStrRef();
			}
			else {
				strDat = new (lenV[2]) StringData(NULL);
				//Populate...
				copy(_str->utf16(), strDat->utf8(), startPos);
				copy(str.c_str(), strDat->utf8() + startPos, lenV[1]);
				copy(_str->utf16() + startPos + len, strDat->utf8() + startPos + lenV[1], lenV[0] - startPos - len + 1);
			}
			_str->killRef();
			_str = strDat;

			THISREF();
		}

		String String::trim() const {
			if(empty()) {
				THISREF();
			}
			//Start trimming at the beginning
			UTF16 begin = _str->utf16();
			while(*begin && isspace(*begin)) {
			   begin++;
			}
			//Next, trim from the end.
			UTF16 end = _str->utf16() + length() - 1;
			while(end > begin && isspace(*end)) {
				end--;
			}
			//Add one position to the end.
			end++;
			//Length Test
			SIZE_T len = end - begin;
			if((U32)len == length()) {
				THISREF();
			}
			//Build the new string
			StringData *strDat;
			if(!len) {
				strDat = StringData::emptyStrRef();
			}
			else {
				strDat = new ((U32)len) StringData(begin);
			}
			return strDat;
		}

		String String::substr(U32 startPosition, U32 len) const {
			if(startPosition > length()) {
				GC_Error("String::substr(%i, %i): The requested starting position is outside of the String Length [%i]", startPosition, len, length());
				return String("");
			}
			if(len == -1) {
				//-1 argument: pull to end.
				len = length() - startPosition;
			}
			if(len + startPosition > length()) {
				GC_Error("String::substr(%i, %i): The requested position & length lie outside of the String Length [%i]", startPosition, len, length());
				return String("");
			}
			StringData *subst;
			if(!len) {
				subst = StringData::emptyStrRef();
			}
			else {
				subst = new (len) StringData(_str->utf16() + startPosition);
			}
			return subst;
		}

		void String::split(UTF16 token, DynArray<String> &ref) const {
			UTF16 chrs = _str->utf16(), copy = chrs;
			while(*chrs) {
				if(*chrs != token[0]) {
					chrs++;
				}
				else {
					//Check for a matching case
					UTF16 end = chrs, tokenCpy = token;
					while(*tokenCpy && *tokenCpy == *chrs) {
						chrs++;
						tokenCpy++;
					}
					//This will trigger if we don't match a case completely.
					if(*tokenCpy != '\0') {
						continue;
					}
					//If we get here, then we've got a full match, so let's extract our string.
					String newStr(copy, (U32)(end - copy));
					ref.pushToBack(newStr);
					copy = chrs;
				}
			}
			//If we have anything left over, add it to the end.
			if(copy != chrs) {
				ref.pushToBack(copy);
			}
		}

		String String::VoidToStr(UTF16 format, any args) {
			StringFormat strFormat(format, &args);
			U32 formatLength = strFormat.length();
			StringData *output;
			if(formatLength == 0) {
				output = StringData::emptyStrRef();
			}
			else {
				output = new (formatLength) StringData(NULL);
				strFormat.copyBuffer(output->utf8());
				output->utf8()[formatLength] = NULL;
			}
			return output;
		}

		String String::ToStr(UTF16 format, ...) {
			if(!format) {
				GC_Error("String::ToStr(NULL, ...): Cannot convert NULL type to a String.");
				return StringData::emptyStrRef();
			}
			va_list args;
			_crt_va_start(args, format);
			String result = VoidToStr(format, args);
			_crt_va_end(args);
			return result;
		}

		String String::ToStr(bool v) {
			if(v) {
				return "true";
			}
			return "false";
		}

		String String::ToStr(U32 v) {
			return ToStr("%u", v);
		}

		String String::ToStr(S32 v) {
			return ToStr("%d", v);
		}

		String String::ToStr(F32 v) {
			return ToStr("%g", v);
		}

		String String::ToStr(F64 v) {
			return ToStr("%Lg", v);
		}

		String String::ToLwr(strRef string) {
			if(string.empty()) {
				return StringData::emptyStrRef();
			}
			StringData *out = new (string.length()) StringData(string.c_str());
			_strlwr(out->utf8());
			return out;
		}

		String String::ToUpr(strRef string) {
			if(string.empty()) {
				return StringData::emptyStrRef();
			}
			StringData *out = new (string.length()) StringData(string.c_str());
			_strupr(out->utf8());
			return out;
		}

		String& String::operator=(C8 c) {
			_str->killRef();
			_str = new (2) StringData(NULL);
			_str->utf8()[0] = c;
			_str->utf8()[1] = '\0';

			THISREF();
		}

		String& String::operator+=(C8 c) {
			U32 currentLength = _str->getLength();
			StringData *newStr = new (currentLength + 1) StringData(NULL);
			//Copy existing contents into the new string and construct the end.
			copy(_str->utf16(), newStr->utf8(), currentLength);
			newStr->utf8()[currentLength] = c;
			newStr->utf8()[currentLength+1] = '\0';
			_str->killRef();
			_str = newStr;

			THISREF();
		}

		String& String::operator=(UTF16 str) {
			if(_str->utf16() == str) {
				//If the string we're assigning to is the one we already have, then stop the function here.
				// This prevents the string data reference from being deleted when we actually still need it.
				THISREF();
			}

			_str->killRef();
			if(str && *str) {
				//Only proceed if there's actually something to put in the String
				U32 length = (U32)strlen(str);
				_str = new (length) StringData(str);
			}
			else {
				_str = StringData::emptyStrRef();
			}
			THISREF();
		}

		String& String::operator+=(UTF16 str) {
			if(str == NULL && !*str) {
				//If there's nothing to add, just stop.
				THISREF();
			}
			//Three length values to calculate for.
			U32 length[3] = { _str->getLength(), (U32)strlen(str), _str->getLength() + (U32)strlen(str) };
			//Construct the new String
			StringData *newStr;
			if(length[2] == 0) {
				newStr = StringData::emptyStrRef();
			}
			else {
				newStr = new (length[2]) StringData(NULL);
				copy(_str->utf16(), newStr->utf8(), length[0]);
				copy(str, newStr->utf8() + length[0], length[1]+1);
			}
			_str->killRef();
			_str = newStr;
			THISREF();
		}

		String& String::operator=(strRef ref) {
			ref._str->addRef();
			_str->killRef();
			_str = ref._str;
			THISREF();
		}

		String& String::operator+=(strRef ref) {
			if(ref.empty()) {
				//If the string we're adding from is empty, stop here.
				THISREF();
			}
			//Three length values to calculate for.
			U32 len[3] = { _str->getLength(), ref._str->getLength(), _str->getLength() + ref._str->getLength() };
			//Construct the new string.
			StringData *newStr;
			if(len[2] == 0) {
				newStr = StringData::emptyStrRef();
			}
			else {
				newStr = new (len[2]) StringData(NULL);
				copy(_str->utf16(), newStr->utf8(), len[0]);
				copy(ref._str->utf16(), newStr->utf8() + len[0], len[1]+1);
			}
			_str->killRef();
			_str = newStr;
			THISREF();
		}

		String operator+(strRef s1, strRef s2) {
			if(s1.empty()) {
				return s2;
			}
			else if(s2.empty()) {
				return s1;
			}
			//Perform addition
			U32 len[2] = { s1.length(), s2.length() };
			//Declare new StringData
			String::StringData *data = new (len[0] + len[1]) String::StringData( NULL );
			//Populate it.
			String::copy(s1._str->utf16(), data->utf8(), len[0]);
			String::copy(s2._str->utf16(), data->utf8() + len[0], len[1] + 1);

			return String(data);
		}

		String operator+(strRef s, C8 chr) {
			U32 length = s.length();
			//Declare new StringData
			String::StringData *data = new (length + 1) String::StringData( NULL );
			//Populate.
			String::copy(s._str->utf16(), data->utf8(), length);
			//Add the chr to the end
			data->utf8()[length] = chr;
			data->utf8()[length + 1] = NULL;

			return String(data);
		}

		String operator+(C8 chr, strRef s) {
			U32 length = s.length();
			//Declare new StringData
			String::StringData *data = new (length + 1) String::StringData( NULL );
			//Populate.
			String::copy(s._str->utf16(), data->utf8() + 1, length + 1);
			//Add the chr to the beginning
			data->utf8()[0] = chr;

			return String(data);			
		}

		String operator+(strRef s, UTF16 str) {
			if(!str) {
				GC_Error("String::operator+(strRef, UTF16): The secondary argument (UTF16) is a NULL ptr, breaking operation.");
				return s;
			}
			if(s.empty()) {
				return String(str);
			}
			//Define length params
			U32 len[2] = { s.length(), (U32)strlen(str) };
			if(!len[1]) {
				//str is empty.
				return s;
			}
			//Declare new StringData
			String::StringData *data = new (len[0] + len[1]) String::StringData( NULL );
			//Populate.
			String::copy(s._str->utf16(), data->utf8(), len[0]);
			String::copy(str, data->utf8() + len[0], len[1] + 1);

			return String(data);
		}

		String operator+(UTF16 str, strRef s) {
			if(!str) {
				GC_Error("String::operator+(UTF16, strRef): The primary argument (UTF16) is a NULL ptr, breaking operation.");
				return s;
			}
			if(s.empty()) {
				return String(str);
			}
			//Define length params
			U32 len[2] = { (U32)strlen(str), s.length() };
			if(!len[0]) {
				//str is empty.
				return s;
			}
			//Declare new StringData
			String::StringData *data = new (len[0] + len[1]) String::StringData( NULL );
			//Populate.
			String::copy(str, data->utf8(), len[0]);
			String::copy(s._str->utf16(), data->utf8() + len[0], len[1] + 1);		

			return String(data);		
		}

		bool String::operator==(strRef ref) const {
			if(_str == ref._str) {
				return true;
			}
			else if(length() != ref.length()) {
				return false;
			}
			else {
				return memcmp(_str->utf8(), ref._str->utf8(), _str->getLength()) == 0;
			}
		}

		bool String::operator==(C8 c) const {
			if(!_str || _str->getLength() != 1) {
				return false;
			}
			else {
				return (_str->utf8()[0] == c);
			}
		}

		C8 String::operator[](S32 index) const {
			return c_str()[index];
		}

		C8 String::operator[](U32 index) const {
			return c_str()[index];
		}

		void String::copy(UTF16 source, UTF8 destination, U32 size) {
			memcpy(destination, source, size * sizeof(C8));
		}

	};

};