/**
* Galactic 2D
* Source/EngineCore/Files/fileTools.h
* Defines a group of asset class definitions as needed by the file system
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

#ifndef GALACTIC_INTERNAL_FILETOOLS
#define GALACTIC_INTERNAL_FILETOOLS

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		fileCopyProgress: A basic structure that polls the current status of a file copy operation
		*/
		struct fileCopyProgress {
			virtual bool poll(F32 dt) = 0;
		};

		/*
		FileWriter: A stream instance built to write data to files
		*/
		class FileWriter : public Stream {

		};

		/*
		FileReader: A stream instance built to read data from files
		*/
		class FileReader : public Stream {

		};

	};

};

#endif //GALACTIC_INTERNAL_FILETOOLS