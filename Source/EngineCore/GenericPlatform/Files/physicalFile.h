/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/Files/physicalFile.h
* Defines a platform wrapper for physical file I/O functions on the low level
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

#ifndef GALACTIC_INTERNAL_GENERICPLATFORM_PHYSICALFILE
#define GALACTIC_INTERNAL_GENERICPLATFORM_PHYSICALFILE

namespace Galactic {

	namespace Core {

		/*
		GenericPhysicalFile: A platform independant file I/O wrapper interface. Mainly consistent of template functions that are overwritten by individual platform
		 instances in their respective platform folders.
		*/
		class GenericPhysicalFile : public GenericFile {
			public:
				/* Public Class Members */
				//Initialize this file instance
				virtual bool init(GenericFile *file);
				//Fetch the typename of this physical instance
				static UTF16 fetchName();
				//Fetch the PlatformFile object wrapped by this instance at the lower level
				virtual GenericFile *fetchWrappedInstance();
				//Should we use this specific file instance?
				virtual bool useInstance(GenericFile *lowerLevel) const;
		};

	};

};

#endif //GALACTIC_INTERNAL_GENERICPLATFORM_PHYSICALFILE