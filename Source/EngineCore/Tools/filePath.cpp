/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* filePath.cpp
*
* Defines the filePath class which is used by the file system to handle things such as converting relative and absolute file paths as well as a few
*  other things.
**/

#include "filePath.h"

namespace Galactic {

	namespace Core {

		FilePath::FilePath() {
			fileNameDirty = true;
			filePathDirty = true;
		}

		FilePath::FilePath(UTF16 path) {
			fileNameDirty = true;
			filePathDirty = true;
			__split(path);
		}

		FilePath::FilePath(strRef path) {
			fileNameDirty = true;
			filePathDirty = true;
			__split(path);
		}

		bool FilePath::empty() const {
			return getFullPath().empty();
		}

		bool FilePath::directory() const {
			//If there's no file name & extension, it's a directory
			return fName.empty() && fExt.empty();
		}

		bool FilePath::absolute() const {
			//A absolute path is one that contains a full path to the file, ex: c:/path/to/file.ext
			// The actPath variable contains the beginning of the path after the root, in our above example: /path/to/file.ext
			return !actPath.empty() && actPath.c_str()[0] == '/';
		}

		bool FilePath::relative() const {
			//A relative path is a path that is relative to the current working directory. Example, the following: c:/mygame/myfolder/file.ext,
			// in this example /myfolder/file.ext will be relative when the working directory is mygame/
			return actPath.empty() && actPath.c_str()[0] != '/';
		}

		U32 FilePath::numDirs() const {
			if(actPath.empty()) {
				return 0;
			}
			U32 dirCount = 0, dirDepth = 0;
			if(actPath.c_str()[0] == '/') {
				//Absolute, increase the depth
				dirDepth++;
			}
			while(dirDepth < actPath.length()) {
				if(actPath[dirDepth++] == '/') {
					dirCount++;
				}
			}
			return dirCount + 1;
		}

		String FilePath::getDir(U32 level) const {
			String result = "";
			if(actPath.empty()) {
				return result;
			}
			U32 dirOffset = 0, lastOffset = 0;
			//Offset for relative paths
			if(actPath.c_str()[0] == '/') {
				dirOffset++;
			}
			//Loop through level
			while(level && dirOffset < actPath.length()) {
				if(actPath[dirOffset++] == '/') {
					level--;
				}
			}
			lastOffset = dirOffset;
			//Loop backwards now.
			while(actPath[lastOffset] != '/' && lastOffset < actPath.length()) {
				lastOffset++;
			}
			result = actPath.substr(dirOffset, lastOffset - dirOffset);
			return result;
		}

		String FilePath::getNonRootPath() const {
			return join(getActivePath(), getFileName(), '/');
		}

		String FilePath::getFullPath() const {
			//If the path has been recently adjusted, perform the join operation
			if(filePathDirty) {
				filePath = __join();
				filePathDirty = false;
			}
			return filePath;
		}

		String FilePath::getFileName() const {
			//If the file has been recently adjusted, we need to perform the append operation
			if(fileNameDirty) {
				fileName = fName;
				if(!fExt.empty()) {
					fileName += '.';
					fileName += fExt;
				}

				fileNameDirty = false;
			}
			return fileName;
		}

		String FilePath::getFilePathMinusExt() const {
			//If the path has been recently adjusted, perform the join operation
			if (filePathDirty) {
				filePath = __join();
				filePathDirty = false;
			}
			//Substr out the stuff we need.
			String result = filePath.substr(0, filePath.find("."));
			return result;
		}

		bool FilePath::append(pathRef path) {
			actPath = compress(join(actPath, path.getActivePath(), '/'));
			//Changes have been made, alert __join / __split.
			filePathDirty = true;
			return true;
		}

		String FilePath::join(strRef p1, strRef p2, C8 sep) {
			if(sep == '/') {
				if(p2.empty() || (p2.length() == 1 && (p2.c_str()[0] == '/'))) {
					return p1;
				}
				if(p1.empty()) {
					return p2;
				}
				//Grab the last char from p1.
				C8 tmp = p1[p1.length() - 1];
				//Test for special cases.
				// We perform an xOR operation here to test and toggle the boolean status
				if(tmp == ':' || ((tmp == '/') ^ (p2.c_str()[0] == '/'))) {
					//If this is the case, then we can skip the separator.
					return p1 + p2;
				}
				if(tmp == '/' && p2.c_str()[0] == '/') {
					//Another example is if we're adding a absolute to a relative. We simply chop off the last char from p1 and add p2 to it.
					return p1.substr(0, p1.length() - 1) + p2;
				}
			}
			else if(sep == ':') {
				if(p1.empty()) {
					return p2;
				}
				if(p2.empty()) {
					return p1 + ':';
				}
			}
			else if(sep == '.') {
				if(p2.empty()) {
					return p1;
				}
				if(p1.empty()) {
					return '.' + p2;
				}					
			}
			else {
				//Do nothing..
			}
			return p1 + sep + p2;
		}

		String FilePath::fixSeparators(String path) {
			String s1, s2;
			s1 = '\\';
			s2 = '/';
			return path.replace(s1, s2);
		}

		String FilePath::compress(String path) {
			//Remove all relative directory paths and convert it to the proper absolute form. This function assumes that
			// the separators have been fixed prior to being called, but in safe case, we'll fix it anyways ;)
			path = fixSeparators(path);
			//We'll use two position values for arrays here, consider pos[0] to be the source position and pos[1] to be the destination position
			U32 pos[2] = { 0, 0 };
			//Temporary String for holding path data
			String tempStr;
			while(path[pos[0]]) {
				if(path[pos[0]] == '/' && path[pos[0] + 1] == '/') {
					// We have a // here, skip to the next index.
					pos[0] += 1;
					continue;
				}
				else if(path[pos[0]] == '.') {
					//Test for relative path flags (./ & ../).
					if(path[pos[0] + 1] == NULL) {
						//End of the path?
						if(pos[1] && path[pos[1] - 1] == '/') {
							pos[1]--;
						}
						//We're done here...
						pos[0]++;
						break;
					}
					else if(path[pos[0] + 1] == '/') {
						//Relative ./, continue through loop
						pos[0] += 2;
						continue;
					}
					else if(path[pos[0] + 1] == '.') {
						//Two dots (..), check for relative flag or other possibilities here.
						if(path[pos[0] + 2] == NULL) {
							//Empty?
							if(pos[1] && path[pos[1] - 1] == '/') {
								pos[1] = path.find('/', pos[1] - 1, String::Right);
							}
							pos[0] += 2;
							break;
						}
						//Do some final tests.
						if(pos[1] && path[pos[1] - 1] == '/') {
							pos[1] = path.find('/', pos[1] - 1, String::Right) + 1;
						}
						else {
							//Skip over it.
							pos[1] += 3;
						}
						pos[0] += 3;
						continue;
					}
				}
				//Now, we actually run through the string and perform the compression (if we need to)
				if(pos[0] != pos[1]) {
					tempStr = path.substr(pos[0], path.length() - pos[0]);
					if(pos[1] > 0 && tempStr[0] == '/' && path[pos[1] - 1] == '/') {
						tempStr = tempStr.substr(1, tempStr.length() - 1);
					}
					//Replace contents
					path.replace(pos[1], path.length() - pos[1], tempStr);
					pos[0] = pos[1];
				}
				else {
					pos[0]++;
					pos[1]++;
				}
			}
			//Check if we still need to perform any last minute stuff.
			if(pos[0] - pos[1] > 0) {
				path.erase(pos[1], pos[0] - pos[1]);
			}
			//And we're done!
			return path;
		}

		FilePath FilePath::createRelative(pathRef make, pathRef to, U32 strSrcMode) {
			//What we're storing
			String thePath;
			//Store some numerical parameters we'll need for this function
			U32 indxVls[3] = { (make.numDirs() > to.numDirs() ? to.numDirs() : make.numDirs()), 0, 0 };
			for(indxVls[1] = 0; indxVls[1] < indxVls[0]; indxVls[1]++) {
				//If they don't match then we've found where the directories change
				if(make.getDir(indxVls[1]).compare(to.getDir(indxVls[1]), make.getDir(indxVls[1]).length(), strSrcMode)) {
					break;
				}
			}
			//Count the amount of offsets (../) we need to add.
			indxVls[2] = to.numDirs() - indxVls[1];
			for(U32 i = 0; i < indxVls[2]; i++) {
				thePath += "../";
			}
			//Fetch the directory path up to the point where they change.
			for(U32 i = indxVls[1]; i < make.numDirs(); i++) {
				thePath += make.getDir(i) + "/";
			}
			//Add the remainder.
			thePath += make.getFileName();
			//Return.
			return thePath;
		}

		strRef FilePath::setActiveRoot(strRef r) {
			if(actRoot != r) {
				actRoot = r;
				filePathDirty = true;
			}
			return actRoot;
		}

		strRef FilePath::setActivePath(strRef p) {
			String clean = fixSeparators(p);
			if(actPath != clean) {
				actPath = clean;
				filePathDirty = true;
			}
			return actPath;
		}

		strRef FilePath::setActiveFileName(strRef n) {
			if(fName != n) {
				fName = n;
				filePathDirty = true;
				fileNameDirty = true;
			}
			return fName;
		}

		strRef FilePath::setActiveFileExtension(strRef e) {
			if(fExt != e) {
				fExt = e;
				filePathDirty = true;
				fileNameDirty = true;
			}
			return fExt;
		}

		strRef FilePath::getActiveRoot() const {
			return actRoot;
		}

		strRef FilePath::getActivePath() const {
			return actPath;
		}

		strRef FilePath::getActiveFileName() const {
			return fName;
		}

		strRef FilePath::getActiveFileExtension() const {
			return fExt;
		}

		FilePath &FilePath::operator=(strRef file) {
			__split(file);
			filePathDirty = true;
			fileNameDirty = true;
			return *this;
		}

		bool FilePath::operator==(pathRef f) const {
			return getFullPath().compare(f.getFullPath()) == 0;
		}

		bool FilePath::operator!=(pathRef f) const {
			return !(*this == f);
		}

		String FilePath::__join() const {
			String fullPath;
			//Check the root of the path
			if(getActiveRoot() != '/') {
				fullPath = join(actRoot, actPath, ':');
			}
			else {
				fullPath = getActivePath();
			}
			//Join the rest of it
			fullPath = join(fullPath, fName, '/');
			fullPath = join(fullPath, fExt, '.');
			return fullPath;
		}

		void FilePath::__split(String path) {
			//Define some numerical parameters for later use.
			U32 indxVals[3] = { 0, 0, 0 };
			//Flip the path to proper platform separators
			path = FlipToPlatform(path);
			//Alright, let's start by trying to locate and extract the directory root (:)
			indxVals[0] = path.find(':');
			if(indxVals[0] >= 0) {
				//split the root
				actRoot = path.substr(0, indxVals[0]);
				indxVals[1] = indxVals[0] + 1;
			}
			else if(path[0] == '/') {
				actRoot = "/";
			}
			else {
				actRoot = "";
			}
			//Extract the file path
			indxVals[0] = path.find('/', 0, String::Right);
			if(indxVals[0] >= indxVals[1]) {
				indxVals[2] = indxVals[0] - indxVals[1];
				actPath = path.substr(indxVals[1], indxVals[2] ? indxVals[2] : 1);
				actPath = fixSeparators(actPath);
				indxVals[1] = indxVals[0] + 1;
			}
			else {
				actPath = "";
			}
			//Extract the file name and file extension
			indxVals[0] = path.find('.', 0, String::Right);
			if(indxVals[0] >= indxVals[1]) {
				fName = path.substr(indxVals[1], indxVals[0] - indxVals[1]);
				fExt = path.substr(indxVals[0] + 1, path.length() - indxVals[0] - 1);
			}
			else {
				fName = path.substr(indxVals[1], path.length() - indxVals[1]);
				fExt = "";				
			}
		}

	};

};