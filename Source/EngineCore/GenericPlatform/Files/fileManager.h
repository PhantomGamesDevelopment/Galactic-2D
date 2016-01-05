/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/Files/fileManager.h
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

#ifndef GALACTIC_INTERNAL_GENERICPLATFORM_FILEMANAGER
#define GALACTIC_INTERNAL_GENERICPLATFORM_FILEMANAGER

namespace Galactic {

	namespace Core {

		/*
		GenericFileManager: Generic implementation of file management functions, serves as a wrapper to the engine's FileManager class
		*/
		class GenericFileManager {
			private:
				/* 
				   Private Class Members  
				   Note: We flip/flop the order of this class instance due to the load order of the header instances, this implementation is
				         required first by the engine, and since GenericFile isn't loaded yet, we need to provide a class stub for it.
				*/
				//Active instance of PlatformFile (Class definition stub)
				class GenericFile *activeFile;

			public:
				/* Public Class Methods */
				//Constructor
				GenericFileManager();
				//Fetch the singleton instance
				static GenericFileManager &fetchInstance();
				//Fetch the currently active instance of PlatformFile
				GenericFile &fetchActiveFile();
				//Set the active file instance
				void setActiveFile(GenericFile &instance);
				//Find a file instance by name, return NULL if none exist.
				GenericFile *fetchByName(UTF16 name);
				//Find a file instance by name in the chain of linked instances, return NULL if none found.
				GenericFile *fetchInChain(UTF16 name);
		};

	};

};

#endif //GALACTIC_INTERNAL_GENERICPLATFORM_FILEMANAGER