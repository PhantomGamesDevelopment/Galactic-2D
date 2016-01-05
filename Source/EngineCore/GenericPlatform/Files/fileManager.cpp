/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/Files/fileManager.cpp
* Platform based implementation of file management systems, generic module
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

		GenericFileManager::GenericFileManager() : activeFile(NULL) {

		}

		GenericFileManager &GenericFileManager::fetchInstance() {
			if (managedSingleton<GenericFileManager>::instance() == NULL) {
				managedSingleton<GenericFileManager>::createInstance();
			}
			return *(managedSingleton<GenericFileManager>::instance());
		}

		GenericFile &GenericFileManager::fetchActiveFile() {
			if (activeFile == NULL) {
				activeFile = &GenericFile::fetchPhysicalInstance();
			}
			return *activeFile;
		}

		void GenericFileManager::setActiveFile(GenericFile &instance) {
			activeFile = &instance;
			//Some platforms require some additional functioning before we can begin to work with a file instance, handle it now.
			activeFile->postInit();
		}

		GenericFile *GenericFileManager::fetchByName(UTF16 name) {
			GenericFile *returnFile = NULL;
			if (strcmp(LoggedFile::getTypeName(), name) == 0) {
				static ScopedPtr<GenericFile> tempInstance(new LoggedFile());
				returnFile = tempInstance.fetchPtrInstance();
			}
			else {
				//To-Do: When installing other platforms into the engine, if they require modules that differ from the standard name of
				//        PhysicalFile, it will need to be looked up through this process.
			}
			return returnFile;
		}

		GenericFile *GenericFileManager::fetchInChain(UTF16 name) {
			if (activeFile == NULL) {
				GC_Error("GenericFileManager::fetchInChain(): Cannot initialize chain-search without base object");
				return NULL;
			}
			for (GenericFile *topLink = activeFile; topLink; topLink = topLink->fetchWrappedInstance()) {

			}
		}

	};

};