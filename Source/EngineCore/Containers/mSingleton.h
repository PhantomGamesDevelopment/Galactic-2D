/**
* Galactic 2D
* Source/EngineCore/Containers/mSingleton.h
* Defines a class instance to define a managed singleton instance
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

#ifndef GALACTIC_INTERNAL_MANAGED_SINGLETON
#define GALACTIC_INTERNAL_MANAGED_SINGLETON

namespace Galactic {

	namespace Core {

		/*
		managedSingleton is a class based on the design of the boost library singleton class (boost::singleton). This class allows
		you to define a single "instance" class that is specific to the entire engine, IE: only one instance of this class can ever
		be defined. To define a managedSingleton, the syntax is: managedSingleton<Class>::createInstance(); It is also recommended 
		to define a static UTF16 getInstanceName() method in managedSingleton classes for organization and identification by name.
		*/
		template <typename T> class managedSingleton {
			public:
				static void createInstance() {
					if(mSingleton != NULL) {
						//ToDo: Throw an assert error here
						return;
					}
					mSingleton = new T();
				}

				static void destroyInstance() {
					if(mSingleton == NULL) {
						return;
					}
					SendToHell(mSingleton);
				}

				static UTF16 getInstanceName() {
					return "UNNAMED_SINGLETON_INSTACE";
				}

				static T* instance() {
					return mSingleton ? mSingleton : NULL;
				}

			private:
				static T* mSingleton;
		
		};
		template <typename T> T* managedSingleton<T>::mSingleton = NULL;

	};

};

#endif //GALACTIC_INTERNAL_MANAGED_SINGLETON