/**
* Galactic 2D
* charTools.h
* Defines support functions for character types
* (C) 2014 Phantom Games Development - All Rights Reserved
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

#ifndef GALACTIC_INTERNAL_CHARACTER_TOOLS
#define GALACTIC_INTERNAL_CHARACTER_TOOLS

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		UTX8ToChar: Convert a byte array string to a recognizable format for common String applications. This tool is mainly used by the platform applications
		 that directly access memory by means of HANDLE based objects to convert bytes of various types to a common standard.
		*/
		class UTX8ToChar {
			private:
				/* Private Class Members */
				//The type we're converting from
				typedef C8 from;
				//The type we're converting to
				typedef TCHAR to;

				//Convert the encoded UTF format to charaters, clean up bad bits.
				static U32 validateByteOctets(const from **in) {
					//For those of you looking into why we're doing this, we're trying to keep compliance with UTF16/UTF8 formats as defined by
					// rfc-3629 (http://tools.ietf.org/html/rfc3629)
					UTF16 strResult = *in;
					U32 octet1 = (U32)((U8)*in), octet2, octet3, octet4;
					U32 returnValue = 0;
					if (octet1 <= 127) {
						//One octet character 0-127, fits in standard ASCII table, nothing needed?
						(*in)++;
						return octet1;
					}
					else if (octet1 <= 191) {
						//These are illegal characters that have 10xxxxxx byte ranges. We want to convert it to the Bad Literal to prevent "problems" from 
						// happening...
						(*in)++;
						return BadLiteralConvert;
					}
					else if (octet1 <= 223) {
						//Two octets used by this byte. Break off each piece and test for validity
						//Grab the first octet.
						octet1 -= (192);
						//Grab the second octet.
						octet2 = (U32)((U8)*(in++));
						//Validate the second octet
						if ((octet2 & (192)) != 128) {
							//10xxxxxx... bad
							(*in)++;
							return BadLiteralConvert;
						}
						//If both of the bytes are valid, we check to ensure the values fit within that of the extended ASCII Table (0x80 - 0x7FF)
						// Anything outside of these values is considered illegal for two octets.
						returnValue = ((octet1 << 6) | (octet2 - 128));
						if (returnValue >= 0x80 && returnValue <= 0x7FF) {
							//Looks good, move the byte array to the next group.
							(*in) += 2;
							return returnValue;
						}
					}
					else if (octet1 <= 239) {
						//Three octets used by this byte. Again, we need to validate each piece.
						//Grab the first octet.
						octet1 -= (224);
						//Grab the second octet.
						octet2 = (U32)((U8)*(in++));
						//Validate the second octet
						if ((octet2 & (192)) != 128) {
							//10xxxxxx... bad
							(*in)++;
							return BadLiteralConvert;
						}
						//Grab the third octet.
						octet3 = (U32)((U8)*(in++));
						//Validate the third octet
						if ((octet3 & (192)) != 128) {
							//10xxxxxx... bad
							(*in)++;
							return BadLiteralConvert;
						}
						//For three octets we need to check for "UTF16 Surrogates" that are illegal in the UTX-8 definition, we also need to filter out
						// 0xFFFE and 0xFFFF as they are illegal as well, everything else is ok.
						returnValue = ((octet1 << 12) | (octet2 << 6) | (octet3 - 128));
						if (returnValue == 0xD800 || returnValue == 0xDB7F || returnValue == 0xDB80 || returnValue == 0xDBFF || returnValue == 0xDC00 ||
							returnValue == 0xDF80 || returnValue == 0xDFFF) {
							//This contains a UTF16 Surrogate and is therefore illegal, fix it.
							(*in)++;
							return BadLiteralConvert;
						}
						//Check the range.
						if (returnValue >= 0x800 && returnValue <= 0xFFFD) {
							//Looks good, move the byte array to the next group.
							(*in) += 3;
							return returnValue;
						}
					}
					else if (octet1 <= 247) {
						//Four Octets used by this byte
						//Grab the first octet.
						octet1 -= (240);
						//Grab the second octet.
						octet2 = (U32)((U8)*(in++));
						//Validate the second octet
						if ((octet2 & (192)) != 128) {
							//10xxxxxx... bad
							(*in)++;
							return BadLiteralConvert;
						}
						//Grab the third octet.
						octet3 = (U32)((U8)*(in++));
						//Validate the third octet
						if ((octet3 & (192)) != 128) {
							//10xxxxxx... bad
							(*in)++;
							return BadLiteralConvert;
						}
						//Grab the fourth octet.
						octet4 = (U32)((U8)*(in++));
						//Validate the fourth octet
						if ((octet4 & (192)) != 128) {
							//10xxxxxx... bad
							(*in)++;
							return BadLiteralConvert;
						}
						//Four octets is easy, since we just need to validate the standard range. The checks above filter the bad stuff out.
						returnValue = ((octet1 << 18) | ((octet2 - 128) << 12) | ((octet3 - 128) << 6) | (octet4 - 128));
						if (returnValue >= 0x10000 && returnValue <= 0x10FFFF) {
							//Looks good, move the byte array to the next group.
							(*in) += 4;
							return returnValue;
						}
					}
					//Five and Six octet UTX8's are illegal now in rfc-3629, but we still need to validate the octets to ensure the conversion doesn't fail
					else if (octet1 <= 251) {
						//Five Octets
						for (S32 i = 0; i < 5; i++) {
							octet1 = (U32)((U8)*(in++));
							//Validate the second octet
							if ((octet1 & (192)) != 128) {
								//10xxxxxx... bad
								(*in)++;
								return BadLiteralConvert;
							}
						}
						(*in) += 5;
						return BadLiteralConvert;
					}
					else {
						//Six+ Octets
						for (S32 i = 0; i < 6; i++) {
							octet1 = (U32)((U8)*(in++));
							//Validate the second octet
							if ((octet1 & (192)) != 128) {
								//10xxxxxx... bad
								(*in)++;
								return BadLiteralConvert;
							}
						}
						(*in) += 6;
						return BadLiteralConvert;
					}
					//This sequence does not contain valid UTX8 characters, move forward a byte and filter it out.
					(*in)++;
					return BadLiteralConvert;
				}

			public:
				/* Public Class Methods */
				//Perform the conversion
				SFIN void fetch(to *dest, const from *src, S32 fromLen) {
					const from *srcEnd = src + fromLen;
					while (src < srcEnd) {
						U32 converted = validateByteOctets(&src);
						if (converted > 0xFFFF) {
							converted = BadLiteralConvert;
						}
						*dest++ = converted;
					}
				}

		};

	};

};

#endif //GALACTIC_INTERNAL_CHARACTER_TOOLS