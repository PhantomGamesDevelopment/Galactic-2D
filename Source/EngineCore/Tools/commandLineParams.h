/**
* Galactic 2D
* Source/EngineCore/Tools/commandLineParams.h
* Class & tools for fetching and testing for command line parameters
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

#ifndef GALACTIC_PLATFORM_GENERIC_CMDLINEPRMS
#define GALACTIC_PLATFORM_GENERIC_CMDLINEPRMS

#include "../engineCore.h"

namespace Galactic {

	namespace Core {
		
		//There are quite a few 'depricated' function warnings that can be generated by this file, but we're ignoring them.
		#pragma warning( push )
		#pragma warning( disable : 4996 )

		/*
		ProcessCommandLine: A singleton instance that stores the command line of the executed G2D instance.
		*/
		class ProcessCommandLine {
			public:
				/* Public Class Methods */
				//Default Constructor
				ProcessCommandLine::ProcessCommandLine() { }
				//Fetch the singleton instance of this class
				static ProcessCommandLine &fetchInstance() {
					if (managedSingleton<ProcessCommandLine>::instance() == NULL) {
						managedSingleton<ProcessCommandLine>::createInstance();
					}
					return *(managedSingleton<ProcessCommandLine>::instance());
				}
				//Set the command line to a specific value
				void set(UTF16 newLine) {
					strcpy(cmdLine, newLine);
				}
				//Append a string to the command line
				void append(UTF16 toAppend) {
					strncat(cmdLine, toAppend, getArrayCount(cmdLine));
				}
				//Split the command line parameters into a Vector of string token instances for individual parsing.
				void splitToTokens(UTF16 cmdLineTxt, Vector<String> &tokens) {
					String nextTokenInst;
					while (StrTools::fetchCmdLineToken(cmdLineTxt, nextTokenInst, false)) {
						if (*(nextTokenInst.c_str()) == '-') {
							tokens.pushToBack(nextTokenInst);
						}
					}
				}
				//Fetch the text stored in the command line
				UTF16 fetch() {
					return cmdLine;
				}
				//Test if a parameter exists in the command line
				bool hasParam(UTF16 param) {
					UTF16 start = fetch();
					UTF16 inst = fetch();
					if (*inst) {
						while ((start = StrTools::find(start+1, param)) != NULL) {
							if (start > inst && (start[-1] == '-')) {
								UTF16 end = start + strlen(param);
								if (end == NULL || *end == NULL || CharTools::isWSpace(*end)) {
									//Got a match!
									return true;
								}
							}
						}
					}
					return false;
				}

			private:
				/* Private Class Members */
				//How much can be written to the buffer
				static X32 maxLength = 16384;
				//The character array of the stored command line
				static C8 cmdLine[maxLength];
		};

		#pragma warning( pop )

	};

};

#endif //GALACTIC_PLATFORM_GENERIC_CMDLINEPRMS