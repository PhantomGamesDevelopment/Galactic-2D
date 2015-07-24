/**
* Galactic 2D
* Source/EngineCore/Files/filePath.cpp
* Tools and helpers for working with absolute and relative file paths
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

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		String FilePath::rootDir() {
			return PlatformOperations::getRootDir();
		}

		bool FilePath::fileExists(strRef path) {
			return FileManager::fetchInstance().fileExists(path.c_str());
		}

		bool FilePath::isDrive(strRef path) {
			String testStr = path;
			testStr = testStr.replace("/", "\\");
			//Perform a series of tests to see if we're at the drive level
			if (stricmp(testStr.c_str(), "") == 0) {
				return true;
			}
			else if (CharTools::toUpper(testStr[0]) != CharTools::toLower(testStr[0]) && testStr[1] == ':' && testStr[2] == NULL) {
				return true;
			}
			else if (stricmp(testStr.c_str(), "\\") == 0) {
				return true;
			}
			else if (stricmp(testStr.c_str(), "\\\\") == 0) {
				return true;
			}
			else if (testStr[0] == '\\' && testStr[1] == '\\' && strchr(testStr.c_str() + 2, '\\') == 0) {
				return true;
			}
			else {		
				//If none of the above cases match, then we need to perform a set of additional tests
				// mainly dealing with search result cases where they may contain a set of drive roots without
				// an actual file path.
				String tmp1(testStr), tmp2;
				//Handle cases of X:\A\..\..\ 
				if (tmp1.find("\\", 0, String::Right | String::CaseSens) != (tmp1.length() - 1)) {
					tmp1 += "\\";
				}
				S32 findIndex = tmp1.find(":\\");
				if (findIndex != -1) {
					tmp2 = tmp1.substr(tmp1.length() - findIndex - 2);
				}
				else {
					//Networked Path?
					if (tmp1.startsWith("\\\\")) {
						tmp2 = tmp1.substr(tmp1.length() - 2);
						//Grab the index of the slash (should be -1)
						S32 slashIndx = tmp2.find("\\");
						if (slashIndx != -1) {
							//We have a remaining slash index, clean it up...
							tmp2 = tmp2.substr(tmp2.length() - slashIndx - 1);
						}
						else {
							//Empty the remaining path, we don't need it...
							tmp2 = "";
						}
					}
				}
				//Normalize the test path, then validate it
				if (tmp2.length() > 0) {
					tmp2.replace("\\\\", "\\");
					S32 dirCount = 0;
					S32 slashIndex = tmp2.find("\\");
					while (slashIndex != -1) {
						//compact directories until we have nothing left.
						String name = tmp2.substr(0, slashIndex);
						if (name == "..") {
							//Relative path
							dirCount--;
						}
						else {
							//Absolute path
							dirCount++;
						}
						//Update the string & counts
						tmp2 = tmp2.substr(tmp2.length() - slashIndex - 1);
						slashIndex = tmp2.find("\\");
					}
					//Test the final count
					if (dirCount <= 0) {
						//If we have more relative than real, or they even out to 0, then we're at the drive level (root)
						return true;
					}
				}
			}
			//All tests failed, not a drive
			return false;
		}

		String FilePath::join(DynArray<String> paths) {
			DynArray<UTF16> utf16Paths;
			for (S32 i = 0; i < paths.size(); i++) {
				utf16Paths.pushToBack(paths[i].c_str());
			}
			return join(utf16Paths);
		}

		String FilePath::join(DynArray<UTF16> paths) {
			String result;
			__join(result, paths.begin(), paths.size());
			return result;
		}

		void FilePath::__join(String &result, UTF16 *individualPaths, S32 numPaths) {
			if (!individualPaths || numPaths < 1) {
				GC_Error("FilePath::join(): Unable to perform join operation, NULL pointer or zero provided to path amount parameter.");
				return;
			}
			result.clear();
			result += individualPaths[0];
			for (S32 i = 1; i < numPaths; i++) {
				//Add the slashes between the paths, make sure that this step is necessary before proceeding...
				if (result.size() > 1 && result[result.size() - 2] != '/' && result[result.size() - 2] != '\\') {
					result += "/";
				}
				result += individualPaths[i];
			}
		}

	};

};