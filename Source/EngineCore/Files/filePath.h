/**
* Galactic 2D
* Source/EngineCore/Files/filePath.h
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

#ifndef GALACTIC_INTERNAL_FILEPATH
#define GALACTIC_INTERNAL_FILEPATH

namespace Galactic {

	namespace Core {

		/*
		FilePath: A class containing useful functions and tools for working with and manipulating file paths
		*/
		class FilePath {
			public:
				/* Public Class Methods */
				/* Primary Utility Functions */
				//Fetch the application root directory
				static String rootDir();

				/* Testing Functions */
				//Test if the specified path points to an active file
				static bool fileExists(strRef path);
				//Test if the specified path is a drive (X:/)
				static bool isDrive(strRef path);
				//Test if the specified path is a relative file path
				static bool isRelative(strRef path);

				/* Fetch Functions */
				//Fetch the path up to the file name
				static String fetchFilePath(strRef path);
				//Fetch the file base (file name without the extension)
				static String fetchFileBase(strRef path, bool stripPath = true);
				//Fetch the file name (file name and extension)
				static String fetchFileName(strRef path);
				//Fetch the file extension
				static String fetchFileExtension(strRef path, bool withDot = false);

				/* Secondary Utility Functions */
				//Strip duplicate slashing from the string instance
				static void stripDuplicates(String &inPath);
				//Generate a temporary filename
				static String makeTemporary(UTF16 path, UTF16 prefix = "", UTF16 extension = ".tmp");
				//Normalize the filename by removing all instances of / and \\ and replacing them with the engine standard '/'
				static void normalizePath(String &inPath);
				//Normalize the directory tree list provided
				static void normalizeDirectoryTree(String &inPath);
				//Strip out relative directories from a path
				static bool stripRelativeDirs(String &inPath);
				//Create a relative file path given the current path and the desired relative base
				static bool makeRelativePath(String &inPath, UTF16 relativeBase);
				//Convert a relative file path back to the base path
				static String makeAbsolutePath(strRef inRelPath);
				//Convert a relative file path to a base file path relative to a specified base
				static String makeAbsolutePath(strRef inRelPath, strRef base);
				//Convert the specified file path to an engine standard path
				static void toEnginePath(String &inPath);
				//Convert the specified file path to a platform standard path
				static void toPlatformPath(String &inPath);
				//Validate the provided path to ensure it's engine compliant
				static bool validatePath(strRef path);
				//Split a path into it's individual components
				static void split(strRef inPath, String &basePath, String &fileName, String &extension);
				//Join a group of paths together (external function)
				static String join(DynArray<String> paths);
				//Join a group of paths together (external function, uses UTF16)
				static String join(DynArray<UTF16> paths);

			protected:
				/* Protected Class Methods */
				//Join a specified number of paths together
				static void __join(String &result, UTF16 *individualPaths, S32 numPaths);

		};

	};

};

#endif //GALACTIC_INTERNAL_FILEPATH