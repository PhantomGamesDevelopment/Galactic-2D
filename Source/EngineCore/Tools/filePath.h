/**
* Galactic 2D
* Source/EngineCore/Tools/filePath.h
* Tools for working with relative & absolute file paths
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

#ifndef GALACTIC_INTERNAL_FILES_PATH
#define GALACTIC_INTERNAL_FILES_PATH

#include "../platform.h"
#include "../Tools/string.h"

namespace Galactic {

	namespace Core {

		/*
		FilePath: Defines a set of functions and attributes to allow conversions between relative and absolute file paths as well as handling the different
			OS Path string types
		*/
		class FilePath {
			public:
				/* Constructors & Destructor */
				//Default (Empty) Constructor
				FilePath();
				//Create from UTF16
				FilePath(UTF16 path);
				//Create from String
				FilePath(strRef path);

				/* Class Functions */
				//Check if the path is empty
				bool empty() const;
				//Check if the path is pointing to a directory
				bool directory() const;
				//Check if the path is absolute
				bool absolute() const;
				//Check if the path is relative
				bool relative() const;
				//Count the number of directories to the path
				U32 numDirs() const;
				//Return the directory at the specified level, 0 being the disk
				String getDir(U32 level) const;
				//Obtain the filePath without the root of the path
				String getNonRootPath() const;
				//Obtain the full path
				String getFullPath() const;
				//Obtain the full file name
				String getFileName() const;
				//Obtain the file path minus the extension
				String getFilePathMinusExt() const;
				//Appen a path
				bool append(const FilePath &path);

				/* Static Methods */
				//Join Two Paths
				static String join(strRef p1, strRef p2, C8 sep);
				//Fix the separators to a platform accepted form
				static String fixSeparators(String path);
				//Remove relative paths
				static String compress(String path);
				//Create a Relative Path
				static FilePath createRelative(const FilePath &make, const FilePath &to, U32 strSrcMode = String::NoCaseSens);

				/* Special Methods */
				//This method sets the active root
				strRef setActiveRoot(strRef r);
				//This method sets the active path
				strRef setActivePath(strRef p);
				//This method sets a new file name
				strRef setActiveFileName(strRef n);
				//This method sets a new file extension
				strRef setActiveFileExtension(strRef e);
				//This method gets the active root
				strRef getActiveRoot() const;
				//This method gets the active path
				strRef getActivePath() const;
				//This method gets a new file name
				strRef getActiveFileName() const;
				//This method gets a new file extension
				strRef getActiveFileExtension() const;

				/* Operators */
				//Copy / Application Operator
				FilePath &operator=(strRef file);
				//Equality Operator
				bool operator==(const FilePath &f) const;
				//Inequality Operator
				bool operator!=(const FilePath &f) const;

				/* Public Class Members */
				//Define the static String containing the separator, this is OS specific
				enum FileSeparator {
					#ifdef GALACTIC_WIN32
						Sep = '\\',
					#else
						Sep = '/',
					#endif
				};

			private:
				/* Private Class Methods */
				//Join fileName & filePath.
				String __join() const;
				//split path into the class variables (actRoot, actPath, fName, fExt)
				void __split(String path);

				/* Private Class Members */
				//The file name, mutable to allow access through const function defs.
				mutable String fileName;
				//The file path, mutable to allow access through const function defs.
				mutable String filePath;
				//Boolean flag to test if fileName has been adjusted recently, mutable to allow access through const function defs.
				mutable bool fileNameDirty;
				//Boolean flag to test if filePath has been adjusted recently, mutable to allow access through const function defs.
				mutable bool filePathDirty;
				//This variable contains the active root
				String actRoot;
				//This variable contains the active path
				String actPath;
				//This variable contains the file name
				String fName;
				//This variable contains the file extension
				String fExt;
		};

		//const FilePath & is used quite a bit in the fileSystem of the engine, this shortcuts it.
		typedef const FilePath &pathRef;

		/* Asset Inline Functions used to convert between the platform separators */
		//This operation flips instances of \\ with /
		FINLINE String FlipToPlatform(String filepath) {
			if(FilePath::Sep == '\\') {
				String temp, temp2;
				temp = '\\';
				temp2 = '/';
				filepath.replace(temp, temp2);
			}
			return filepath;
		}

		//And this is the reverse of FlipToPlatform
		FINLINE String FlipToPath(String filepath) {
			if(FilePath::Sep == '\\') {
				String temp, temp2;
				temp = '\\';
				temp2 = '/';
				filepath.replace(temp2, temp);
			}
			return filepath;			
		}

	};

};

#endif //GALACTIC_INTERNAL_FILES_PATH