/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/Files/file.cpp
* Defines a generic class instance for working directly with file instances
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

#include "../../engineCore.h"

namespace Galactic {

	namespace Core {

		/* RecursiveVisitor */

		bool GenericFile::RecursiveVisitor::explore(UTF16 path, bool isDir) {
			bool result = ptrToV->access(path, isDir);
			if (result == true && isDir == true) {
				result = ptrToFMO->explore(path, *this);
			}
			return result;
		}

		bool GenericFile::RecursiveVisitor::copy(UTF16 path, bool isDir) {
			String newLoc(path);
			newLoc.replace(srcDir, trgDir);
			//Are we copying a full directory, or just a file?
			if (isDir) {
				//Attempt to create the tree
				if (!ptrToFMO->makeDirTree(newLoc.c_str()) && !ptrToFMO->doesDirExist(newLoc.c_str())) {
					//Failed...
					return false;
				}
			}
			else {
				bool copyError = false;
				//Does the file already exist? Can we overwrite it?
				if (ptrToFMO->exists(newLoc.c_str()) && shouldOverwrite) {
					copyError = true;
					ptrToFMO->deleteFile(newLoc.c_str());
				}
				//Try to copy the source file.
				if (!ptrToFMO->copyFile(path, newLoc.c_str())) {
					if (copyError) {
						GC_CError("GenericFile::RecursiveVisitor::copy(%s): Copy operation failed with the overwrite flag on, file in parameter has been deleted.", newLoc.c_str());
					}
					return false;
				}
			}
			return true;
		}

		bool GenericFile::RecursiveVisitor::purge(UTF16 path, bool isDir) {
			if (isDir) {
				//Ensure the directory is completely empty before deleting...
				ptrToFMO->explore(path, *this);
				ptrToFMO->deleteDir(path);
			}
			else {
				//Flip off the read only flag if needed, then delete
				if (ptrToFMO->isReadOnly(path)) {
					GC_Warn("GenericFile::RecursiveVisitor::purge(%s): File is read-only, flag has been disabled");
					ptrToFMO->setReadOnly(path, false);
				}
				ptrToFMO->deleteFile(path);
			}
		}

		/* GenericFile */

		bool GenericFile::copyFile(UTF16 currentPath, UTF16 newLocation) {
			//Start by validating the source and destination
			const S64 maxSize = 1048576;
			AutoPtr<FileHandle> from(openForRead(currentPath));
			if (!from.valid()) {
				GC_Error("GenericFile::copyFile(%s, []): Failed to open the specified file instance.", currentPath);
				return false;
			}
			AutoPtr<FileHandle> to(openForWrite(newLocation));
			if (!to.valid()) {
				GC_Error("GenericFile::copyFile([], %s): Failed to open the destination file instance, it may already exist and be read-only.", newLocation);
				return false;
			}
			//Test the size...
			S64 fSize = from->fetchSize();
			if (fSize < 1) {
				//Do we have a size 0 file? If so, don't copy it, and tell the engine everything is ok.
				return true;
			}
			//Now proceed to write the data to the new file, do it in chunks
			S64 allocSize = gMin(maxSize, fSize);
			if (allocSize <= 0) {
				//Well, there's your problem...
				GC_Error("GenericFile::copyFile(%s, %s): Failed to copy file, contents are providing negative size values, check for corruption.", currentPath, newLocation);
				return false;
			}
			UTX8 buffer = (UTX8)Memory::gmalloc((S32)allocSize);
			if (!buffer) {
				GC_Error("GenericFile::copyFile(%s, %s): Failed to copy file, cannot allocate storage, the engine may be out of available memory to use.", currentPath, newLocation);
				return false;
			}
			//Perform the copy...
			while (fSize) {
				S64 sizeNow = gMin(maxSize, fSize);
				from->read(buffer, sizeNow);
				to->write(buffer, sizeNow);
				fSize -= sizeNow;
			}
			Memory::gfree(buffer);
			return true;
		}

		bool GenericFile::exploreRecursive(UTF16 path, Visitor &accessCallback) {
			RecursiveVisitor V(this, &(accessCallback));
			return explore(path, V);
		}

		bool GenericFile::makeDirTree(UTF16 path) {

		}

	};

};