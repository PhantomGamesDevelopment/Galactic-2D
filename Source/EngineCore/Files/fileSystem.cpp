/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* fileSystem.cpp
*
* Defines the FileSystem class which combines the operations of the FileCore class into a direct operation parsing class. This class actually
* performs the file operations and it's virtual methods are overriden by the individual platforms to handle cross-platform file ops.
**/

#include "fileSystem.h" 

namespace Galactic {

	namespace Core {

		namespace Files {

			/* 
			NOTE: Consider putting this in FileCore.cpp? We're basically redeclaring the virtual class that
			 is FileCore in a sense that only FileSystem can use. Only thing in that case is we'll need to use
			 some C++ trickery on the file loading sequence to make FileSystem available to FileCore, hence, I 
			 believe that we should just leave things like this..

			Why? In the future if we add support for things like redirect or update notifications this will make 
			 for an easy pluggin to the engine here.
			*/
			class FileCoreReference : public FileCore {
				public:
					/* Public Class Methods */
					//Default Constructor
					FileCoreReference(FileSystem *fSys, pathRef path) {
						sys = fSys;
						fPath.setActiveRoot(path.getActiveRoot());
						fPath.setActivePath(path.getActivePath());
					}

					//Resolve a path to a File
					FileRef_Ref resolvePath(pathRef p) {
						FilePath trg = __merge(p);
						FileCore_Ref core = sys->getFileCore(trg);
						if (!core.null()) {
							return core->resolvePath(trg);
						}
						return StrongReferencePtr<FileRef>();
					}

					//Create a file/directory, given the path and access mode specified.
					FileRef_Ref createInstance(pathRef p, FileRef::FileMode m) {
						FilePath trg = __merge(p);
						FileCore_Ref core = sys->getFileCore(trg);
						if (!core.null()) {
							return core->createInstance(p, m);
						}
						return StrongReferencePtr<FileRef>();
					}

					//Map a file path to or from the specified path.
					FilePath mapPath(pathRef p, MapMode map = MapPathTo) {
						FilePath trg = __merge(p);
						FileCore_Ref core = sys->getFileCore(trg);
						if (!core.null()) {
							return core->mapPath(p, map);
						}
						return NULL;
					}

					//Remove the specified file or directory.
					bool remove(pathRef p) {
						FilePath trg = __merge(p);
						FileCore_Ref core = sys->getFileCore(trg);
						if (!core.null()) {
							return core->remove(p);
						}
						return false;
					}

					//Rename the specified file or directory to something else.
					bool rename(pathRef trgPath, pathRef newName) {
						FilePath trgA = __merge(trgPath), trgB = __merge(newName);
						FileCore_Ref coreA = sys->getFileCore(trgA), coreB = sys->getFileCore(trgB);
						if (coreA.getPointer() == coreB.getPointer()) {
							return coreA->rename(trgA, trgB);
						}
						return false;
					}

				private:
					/* Private Class Methods */
					//Merge the specified path into the stored fPath.
					FilePath __merge(pathRef p) {
						FilePath ret = fPath;
						ret.setActivePath(FilePath::join(ret.getActivePath(), FilePath::compress(p.getActivePath()), '/'));
						ret.setActiveFileName(p.getActiveFileName());
						ret.setActiveFileExtension(p.getActiveFileExtension());
						return ret;
					}

					/* Private Class Members */
					//The stored path
					FilePath fPath;
					//The reference to the FileSystem object
					FileSystem *sys;
			};

			FileSystem::~FileSystem() {
				//Stub...
			}

			bool FileSystem::setCWD(pathRef p) {
				//CWD needs an active path
				if (p.getActivePath().empty()) {
					return false;
				}
				cwd.setActiveRoot(p.getActiveRoot());
				cwd.setActivePath(p.getActivePath());
				return true;
			}

			pathRef FileSystem::getCWD() const {
				return cwd;
			}

			bool FileSystem::isFile(pathRef p) {
				FileRef::FileAttributes attr;
				if (getAttributes(p, &attr)) {
					return (attr.fFlags & FileRef::File);
				}
				return false;
			}

			bool FileSystem::isDir(pathRef p, FileCore_Ref fcRef) {
				FileRef::FileAttributes attr;
				if (fcRef.null()) {
					if (getAttributes(p, &attr)) {
						return (attr.fFlags & FileRef::Directory);
					}
					return false;
				}
				FileRef_Ref fRef = fcRef->resolvePath(p);
				if (fRef.null()) {
					return false;
				}
				if (fRef->getAttributes(&attr)) {
					return (attr.fFlags & FileRef::Directory);
				}
				return false;
			}

			bool FileSystem::isReadOnly(pathRef p) {
				FileCore_Ref fcRef = getFileCore(p);
				if (fcRef.null()) {
					return false;
				}
				if (fcRef->readOnly()) {
					return true;
				}
				FileRef::FileAttributes attr;
				if (getAttributes(p, &attr)) {
					return ((attr.fFlags & FileRef::ReadOnly) ? true : false);
				}
				return false;
			}

			S32 FileSystem::getSysRefSize() const {
				return fileSysRef.size();
			}

			String FileSystem::getSysRefRoot(S32 index) const {
				return fileSysRef[index].fRoot;
			}

			String FileSystem::getSysRefPath(S32 index) const {
				return fileSysRef[index].fPath;
			}

			FileCore_Ref FileSystem::getFileCore(pathRef p) {
				return __fetchFromFCRef(__adjustToCWD(p));
			}

			FileRef_Ref FileSystem::getFileRef(pathRef p) {
				FilePath adjusted = __adjustToCWD(p);
				FileCore_Ref fcRef = __fetchFromFCRef(adjusted);
				if (!fcRef.null()) {
					return fcRef->resolvePath(adjusted);
				}
				return StrongReferencePtr<FileRef>();
			}

			bool FileSystem::getAttributes(pathRef p, FileRef::FileAttributes *attr) {
				FileRef_Ref fRef = getFileRef(p);
				if (!fRef.null()) {
					return fRef->getAttributes(attr);
				}
				return false;
			}
			
			bool FileSystem::addRef(String root, FileCore_Ref coreRef) {
				FCRef ref;
				ref.fRoot = root;
				ref.fPath = "/";
				ref.coreRef = coreRef;
				fileSysRef.pushToBack(ref);
				return true;
			}

			bool FileSystem::addRef(String root, pathRef p) {
				FileCoreReference *newObj = new FileCoreReference(this, __adjustToCWD(p));
				FileCore_Ref fcRef = StrongReferencePtr<FileCore>(newObj);
				return addRef(root, fcRef);
			}

			FileCore_Ref FileSystem::killRef(String root) {
				//Fetch the first instance.
				FileCore_Ref first = __removeFromFCRef(root);
				//Kill off the remaining
				while (!__removeFromFCRef(root).null());
				//Return the first instance
				return first;
			}

			bool FileSystem::killRef(FileCore_Ref coreRef) {
				if (coreRef.null()) {
					return false;
				}
				//Sotring the result, because, reasons.
				bool referenceKilled = false;
				/*
				 We iterate through the fileSysRef list backwards because there is the possibility
				 that it is storing multiple instances of coreRef. Also, make sure we're not NULL during 
				 each run because fileSysRef stores Strong Reference Pointers.
				*/
				for (S32 i = fileSysRef.size() - 1; !coreRef.null() && i >= 0; i--) {
					if (fileSysRef[i].coreRef.getPointer() == coreRef.getPointer()) {
						//Delete it using erase() to allow for the list to fix itself
						fileSysRef.erase(i);
						referenceKilled = true;
					}
				}
				return referenceKilled;
			}

			File_Ref FileSystem::createFile(pathRef p) {
				//Adjust to CWD, then obtain the FileCore_Ref
				FilePath fixed = __adjustToCWD(p);
				FileCore_Ref cRef = __fetchFromFCRef(p);
				if (!cRef.null()) {
					if (cRef->readOnly()) {
						GC_Error("FileSystem::createFile(): Cannot create %s, the target location is read only.", fixed.getFullPath().c_str());
						return StrongReferencePtr<File>();
					}
					return StrongReferencePtr<File>(cRef, PointerModes::StaticCast);
				}
				return StrongReferencePtr<File>();
			}

			Directory_Ref FileSystem::createDirectory(pathRef p, FileCore_Ref fcRef) {
				//Adjust to CWD, then obtain the FileCore_Ref
				FilePath fixed = __adjustToCWD(p);
				if (fcRef.null()) {
					//fetch it from the list, if possible.
					fcRef = __fetchFromFCRef(fixed);
				}		
				if (!fcRef.null()) {
					if (fcRef->readOnly()) {
						GC_Error("FileSystem::createDirectory(): Cannot create %s, the target location is read only.", fixed.getFullPath().c_str());
						return StrongReferencePtr<Directory>();
					}
					return StrongReferencePtr<Directory>(fcRef, PointerModes::StaticCast);
				}
				return StrongReferencePtr<Directory>();
			}

			bool FileSystem::createPath(pathRef p) {
				/*
				 This is a magical function that is extremely useful when working with multi-directory level
				  structures, and works by creating every directory along the path until it reaches the end.
				  Basically, substitute all of your calls to createDirectory() with createPath() when you're
				  not sure if the target location exists yet, and you absolutely need it to be there.
				*/
				if (p.getActivePath().empty()) {
					return true;
				}
				FilePath trgDir;
				trgDir.setActiveRoot(p.getActiveRoot());
				trgDir.setActivePath(p.getActivePath());
				//Fetch the FileCore
				FileCore_Ref fcRef = getFileCore(trgDir);
				if (isDir(trgDir, fcRef)) {
					return true;
				}
				//Begin working down the directory tree.
				FilePath curDir;
				trgDir.setActivePath(p.absolute() ? String("/") : String(""));
				for (U32 i = 0; i < p.numDirs(); i++) {
					curDir.setActivePath(p.getDir(i));
					trgDir.append(curDir);
					if (!isDir(trgDir, fcRef)) {
						if (createDirectory(trgDir, fcRef).null()) {
							return false;
						}
					}
				}
				return true;
			}

			File_Ref FileSystem::openFile(pathRef p, File::FileAccessMode mode) {
				FileRef_Ref fRef = getFileRef(p);
				if (!fRef.null()) {
					File_Ref tFile = StrongReferencePtr<File>(fRef, PointerModes::DynamicCast);
					if (!tFile.null()) {
						if (tFile->openFile(mode)) {
							return tFile;
						}
						return StrongReferencePtr<File>();
					}
				}
				else {
					if (mode != File::Read) {
						File_Ref tFile = createFile(p);
						if (!tFile.null()) {
							tFile->openFile(mode);
							return tFile;
						}
					}
				}
				return StrongReferencePtr<File>();
			}

			Directory_Ref FileSystem::openDir(pathRef p) {
				FileRef_Ref fRef = getFileRef(p);
				if (!fRef.null()) {
					Directory_Ref tDir = StrongReferencePtr<Directory>(fRef, PointerModes::DynamicCast);
					if (!tDir.null()) {
						tDir->openDirectory();
						return tDir;
					}
				}
				return StrongReferencePtr<Directory>();
			}

			bool FileSystem::rename(pathRef trgPath, pathRef newName) {
				FilePath trgA = __adjustToCWD(trgPath), trgB = __adjustToCWD(newName);
				FileCore_Ref coreA = __fetchFromFCRef(trgA), coreB = __fetchFromFCRef(trgB);
				if (coreA.null() || coreB.null()) {
					return false;
				}
				if (coreA.getPointer() != coreB.getPointer()) {
					GC_Error("FileSystem::rename(): %s cannot be renamed into a different file system.", trgPath.getFullPath().c_str());
					return false;
				}
				if (coreA->readOnly() || coreB->readOnly()) {
					GC_Error("FileSystem::rename(): %s cannot be renamed, the source or target is read only.", trgPath.getFullPath().c_str());
					return false;
				}
				return coreA->rename(trgPath, newName);
			}

			bool FileSystem::remove(pathRef trgPath) {
				FilePath trg = __adjustToCWD(trgPath);
				FileCore_Ref fcRef = __fetchFromFCRef(trg);
				if (!fcRef.null()) {
					if (fcRef->readOnly()) {
						GC_Error("FileSystem::remove(): %s cannot be removed, the target is read only.", trgPath.getFullPath().c_str());
						return false;
					}
					return fcRef->remove(trg);
				}
				return false;
			}

			FileCore_Ref FileSystem::__fetchFromFCRef(pathRef p) const {
				for (const FCRef *itr = fileSysRef.begin(); itr != fileSysRef.end(); itr++) {
					if (itr->fRoot.compare(p.getActiveRoot(), p.getActiveRoot().length(), String::NoCaseSens) == 0) {
						return itr->coreRef;
					}
				}
				return StrongReferencePtr<FileCore>();
			}

			FileCore_Ref FileSystem::__removeFromFCRef(String r) {
				for (FCRef *itr = fileSysRef.begin(); itr != fileSysRef.end(); itr++) {
					if (r.compare(itr->fRoot, itr->fRoot.length(), String::NoCaseSens) == 0) {
						FileCore_Ref fcRef = itr->coreRef;
						fileSysRef.erase(itr);
						return fcRef;
					}
				}
				return StrongReferencePtr<FileCore>();
			}

			FilePath FileSystem::__adjustToCWD(pathRef p) {
				FilePath adjusted = p;
				if (adjusted.getActiveRoot().empty()) {
					adjusted.setActiveRoot(cwd.getActiveRoot());
				}
				//Merge the CWD to the target path in a relative sense
				if (adjusted.getActiveRoot().compare(cwd.getActiveRoot(), cwd.getActiveRoot().length(), String::NoCaseSens) == 0
					&& adjusted.relative()) {
					adjusted.setActivePath(FilePath::compress(FilePath::join(cwd.getActivePath(), adjusted.getActivePath(), '/')));
				}
				return adjusted;
			}

		};

	};

};