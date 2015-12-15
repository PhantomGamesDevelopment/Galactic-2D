/**
* Galactic 2D
* Source/EngineCore/Files/flags.h
* Defines a list of flags and enumerations used by the file system
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

#ifndef GALACTIC_INTERNAL_FILEFLAGS
#define GALACTIC_INTERNAL_FILEFLAGS

#define GALACTIC_MAX_FILEPATH_LEN (GALACTIC_PLATFORM_MAX_FILEPATH_LEN)

namespace Galactic {

	namespace Core {

		//File Operation Type to use when opening the file
		enum FileOperationOpenType {
			//Read: Operation has read access to this file
			Read = 0x01,
			//Write: Operation has write access to this file (Data will be overriden)
			Write = 0x02,
			//Append: Operation has write/append access to this file (Data will be preserved)
			Append = 0x40,
		};

		//File Flags to be applied to an object during a write operation
		enum FileWriteFlags {
			//WriteOk: Operation is successful
			WriteOk = 0x01,
			//WriteCanAlsoRead: This object has both read and write access
			WriteCanAlsoRead = 0x02,
			//WriteAttemptReadOnly: This object is attempting to write data during a read-only operation
			WriteAttemptReadOnly = 0x04,
			//WriteConserveData: This object is instructed to preserve existing file data
			WriteConserveData = 0x08,
			//WriteAppend: This object is writing data under an append format
			WriteAppend = 0x10,
		};

		//File Flags to be applied to an object during a read operation
		enum FileReadFlags {
			//ReadOk: Operation is successful
			ReadOk = 0x01,
			//ReadSilent: Perform the operation in the background of the engine
			ReadSilent = 0x02,
		};

		//File Flags to be applied to an object during a copy operation
		enum FileCopyFlags {
			//CopyOk: Operation is successful
			CopyOk = 0x01,
			//CopyFailed: The copy operation has failed
			CopyFailed = 0x02,
			//CopyCanceled: The copy operation has been canceled
			CopyCanceled = 0x04,
		};

	};

};

#endif //GALACTIC_INTERNAL_FILEFLAGS