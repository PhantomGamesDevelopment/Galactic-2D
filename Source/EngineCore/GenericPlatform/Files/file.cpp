/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/Files/file.cpp
* Defines a generic class instance for working directly with file instances
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

#include "../../engineCore.h"

namespace Galactic {

	namespace Core {

		/* CopyVisitor */

		bool GenericFile::CopyVisitor::access(UTF16 path, bool isDir) {
			String newLoc(path);
			newLoc.replace(sourceRoot, destinationRoot);
			//Are we copying a full directory, or just a file?
			if (isDir) {
				//Attempt to create the tree
				if (!fileInstance.makeDirTree(newLoc.c_str()) && !fileInstance.doesDirExist(newLoc.c_str())) {
					//Failed...
					return false;
				}
			}
			else {
				bool copyError = false;
				//Does the file already exist? Can we overwrite it?
				if (fileInstance.exists(newLoc.c_str()) && shouldOverwrite) {
					copyError = true;
					fileInstance.deleteFile(newLoc.c_str());
				}
				//Try to copy the source file.
				if (!fileInstance.copyFile(path, newLoc.c_str())) {
					if (copyError) {
						GC_CError("GenericFile::CopyVisitor::access(%s): Copy operation failed with the overwrite flag on, file in parameter has been deleted.", newLoc.c_str());
					}
					return false;
				}
			}
			return true;
		}

		/* PurgeVisitor */

		bool GenericFile::PurgeVisitor::access(UTF16 path, bool isDir) {
			if (isDir) {
				//Ensure the directory is completely empty before deleting...
				fileInstance.explore(path, *this);
				fileInstance.deleteDir(path);
			}
			else {
				//Flip off the read only flag if needed, then delete
				if (fileInstance.isReadOnly(path)) {
					GC_Warn("GenericFile::PurgeVisitor::access(%s): File is read-only, flag has been disabled", path);
					fileInstance.setReadOnly(path, false);
				}
				fileInstance.deleteFile(path);
			}
		}

		/* RecursiveVisitor */

		bool GenericFile::RecursiveVisitor::access(UTF16 path, bool isDir) {
			bool result = visitorInstance.access(path, isDir);
			if (result == true && isDir == true) {
				result = fileInstance.explore(path, *this);
			}
			return result;
		}

		/* GenericFile */

		UTF16 GenericFile::fetchPhysicalInstanceTypeName() const {
			return "PhysicalFile";
		}

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
			RecursiveVisitor Visitor(*this, accessCallback);
			return explore(path, Visitor);
		}

		bool GenericFile::makeDirTree(UTF16 path) {
			S32 dirsCreated = 0;
			String localFile(path);
			FilePath::normalizePath(localFile);
			UTF16 pathCSTR = localFile.c_str();
			for (C8 fullPath[GALACTIC_MAX_FILEPATH_LEN] = (""), *pathPtr = fullPath; ; *pathPtr++ = *pathCSTR++) {
				if (((*pathCSTR) == '/') || (*pathCSTR == NULL)) {
					//Do we need a new directory here?
					*pathPtr = NULL;
					if ((pathPtr != fullPath) && !FilePath::isDrive(fullPath)) {
						if (!makeDir(fullPath) && !doesDirExist(fullPath)) {
							break;
						}
						dirsCreated++;
					}
				}
				if (*pathCSTR == NULL) {
					break;
				}
			}
			return doesDirExist(localFile.c_str());
		}

		bool GenericFile::copyDirTree(UTF16 srcTree, UTF16 dstTree, bool overwriteExisting) {
			if (dstTree == NULL) {
				GC_Error("GenericFile::copyDirTree(): Failed to initialize method, destination is NULL.");
				return false;
			}
			if (srcTree == NULL) {
				GC_Error("GenericFile::copyDirTree(): Failed to initialize method, source tree is NULL.");
				return false;
			}
			//Stringify and Normalize
			String source(srcTree);
			String destination(dstTree);
			FilePath::normalizePath(source);
			FilePath::normalizePath(destination);
			//Verify existence and attempt to make the directory.
			if (!doesDirExist(source.c_str())) {
				GC_Error("GenericFile::copyDirTree([%s], %s): Failed to run method, source directory does not exist", srcTree, dstTree);
				return false;
			}
			if (doesDirExist(destination.c_str()) && !makeDir(destination.c_str())) {
				GC_Error("GenericFile::copyDirTree(%s, [%s]): Failed to run method, destination already exists or failed to create the directory", srcTree, dstTree);
				return false;
			}
			//Initialize a Visitor instance
			CopyVisitor Visitor(*this, source.c_str(), destination.c_str(), overwriteExisting);
			return exploreRecursive(source.c_str(), Visitor);
		}

		bool GenericFile::purgeDir(UTF16 path) {
			PurgeVisitor Visitor(*this);
			Visitor.access(path, true);
			return !doesDirExist(path);
		}

		bool GenericFile::useInstance(GenericFile *lowerLevel) const {
			return false;
		}

		String GenericFile::makeAbsFP(UTF16 filePath) {
			return FilePath::makeAbsolutePath(filePath);
		}

	};

};