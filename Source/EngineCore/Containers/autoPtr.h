/**
* Galactic 2D
* Source/EngineCore/Containers/autoPtr.h
* Defines an automatic pointer instance, which automatically destroys the internal contents when deleted, but never initializes the contents within
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

#ifndef GALACTIC_INTERNAL_AUTOPOINTER
#define GALACTIC_INTERNAL_AUTOPOINTER

namespace Galactic {

	namespace Core {

		/*
		AutoPtr is a special version of the ScopedPtr instance that follows the same notion of deleting the internal pointer when this object is deleted, however
		 the AutoPtr class will never initialize the internal contents of the stored pointer instance.
		*/
		template <typename T> class AutoPtr {
			typedef AutoPtr<T> self;

			public:
				/* Public Class Methods */
				//Explicit initialization constructor
				explicit AutoPtr(T* inRef = NULL) : ref(inRef) { }
				//Destructor
				~AutoPtr() {
					SendToHell(ref);
				}

				/* Utility Functions */
				//Is this pointer instance valid?
				bool valid() const {
					return (ref != NULL);
				}
				//Fetch the pointer instance contained within
				T *fetchPtrInstance() const {
					return ref;
				}
				//Set the AutoPtr to a new value, release the existing pointer
				void set(T* newPtr = NULL) {
					if (!newPtr || newPtr == ref) {
						GC_Warn("AutoPtr::set(): Cannot set an auto pointer to NULL or use an existing value");
						return;
					}
					SendToPitsOfHell(ref);
					ref = newPtr;
				}
				//Swap contents of two AutoPtr objects
				void swap(self &trg) {
					T* tmp = trg.fetchPtrInstance();
					trg.set(ref);
					set(tmp);
				}

				/* Operators */
				//Assignment Operator (From T* value)
				AutoPtr &operator=(T* ref) {
					set(ref);
					THISREF();
				}
				//Dereference Operator
				T& operator*() const {
					//TO-DO: Insert an assertion clause if ref == NULL
					return *ref;
				}
				//Pointer Dereference Operator
				T* operator->() const {
					//TO-DO: Insert an assertion clause if ref == NULL
					return ref;
				}
				//Conversion Operator
				operator T*() const {
					return ref;
				}

			private:
				/* Private Class Members */
				//What's being stored in this pointer instance
				T* ref;
		};

	};

};

#endif //GALACTIC_INTERNAL_AUTOPOINTER