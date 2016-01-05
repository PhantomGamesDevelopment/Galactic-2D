/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/Files/fileHandle.h
* Defines a HANDLE style object for working with file instances
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

#ifndef GALACTIC_INTERNAL_GENERICPLATFORM_FILEHANDLE
#define GALACTIC_INTERNAL_GENERICPLATFORM_FILEHANDLE

namespace Galactic {

	namespace Core {

		/*
		FileHandle: A Generic HANDLE Style Object that is used throughout the file system in the engine to pass around useful information
		 regarding FILE instances. This can be substituted for a platform based HANDLE instance when needed.
		*/
		class FileHandle {
			public:
				/* Public Class Methods */
				//Destructor
				virtual ~FileHandle() { }

				//Fetch the size of the file
				virtual S64 fetchSize();
				//Fetch the current position of the read/write operation
				virtual S64 tell() = 0;
				//Set the position of the current read/write operation, providing a number that is < 0 will move from the end
				// NOTE: If you provide zero and would like to position at the end, set the second parameter to true.
				virtual bool seek(S64 newPos = 0, bool fromEnd = false) = 0;
				//Write to the file
				virtual bool write(const UTX8 src, S64 bitsToWrite) = 0;
				//Read from the file
				virtual bool read(UTX8 dst, S64 bitsToRead) = 0;
		};

	};

};

#endif //GALACTIC_INTERNAL_GENERICPLATFORM_FILEHANDLE