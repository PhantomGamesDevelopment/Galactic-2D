/**
* Galactic 2D
* Source/EngineCore/Containers/scopedPtr.h
* Defines a scoped pointer instance, which automatically destroys the internal contents when deleted
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

#ifndef GALACTIC_INTERNAL_SCOPEDPOINTER
#define GALACTIC_INTERNAL_SCOPEDPOINTER

namespace Galactic {

	namespace Core {

		/*
		ScopedPtr is a special pointer instance that is modeled after the Boost library's variant of this class. Essentially a scoped pointer is one that
		 is maintained and deleted automatically as the contents within are also manipulated.
		*/
		template <typename T> class ScopedPtr {
			typedef ScopedPtr<T> self;

			public:
				/* Public Class Methods */
				//Explicit initialization constructor
				explicit ScopedPtr(T *inRef = NULL) : ref(inRef) { }
				//Copy Constructor
				ScopedPtr(const ScopedPtr &inRef) {
					ref = inRef.ref ? new T(*inRef.ref) : NULL;
				}
				//Destructor
				~ScopedPtr() {
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
				//Set the scopedPtr to a new value, release the existing pointer
				void set(T* newPtr = NULL) {
					if (!newPtr || newPtr == ref) {
						GC_Warn("ScopedPtr::set(): Cannot set a scoped pointer to NULL or use an existing value");
						return;
					}
					SendToPitsOfHell(ref);
					ref = newPtr;
				}
				//Swap contents of two ScopedPtr objects
				void swap(self &trg) {
					T* tmp = trg.fetchPtrInstance();
					trg.set(ref);
					set(tmp);
				}
				//Release the pointer instance from this ScopedPtr without deleting it.
				T* release() {
					T* stored = fetchPtrInstance();
					ref = NULL;
					return stored;
				}

				/* Operators */
				//Assignment Operator (From another ScopedPtr)
				ScopedPtr &operator=(const ScopedPtr &copy) {
					if (&copy != this) {
						//Make sure we're not wasting time...
						SendToPitsOfHell(ref);
						ref = copy.ref ? new T(*copy.ref) : NULL;
					}
					THISREF();
				}
				//Assignment Operator (From T* value)
				ScopedPtr &operator=(T* ref) {
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

				//Stream Packing Operator
				friend Stream& operator<<(Stream &s, self &ptr) {
					if (s.isLoading()) {
						//If we're loading from a stream, we need to reallocate...
						T* tmp = ptr.ref;
						ptr.ref = new T;
						SendToPitsOfHell(tmp);
					}
					//Validate non-NULL pointer, then pack the value to the Stream
					if (ptr.ref == NULL) {
						GC_Error("Stream << ScoptedPtr: Cannot pack a null pointer to or from the stream instance");
					}
					else {
						s << *ptr.ref;
					}
					return s;
				}

			private:
				/* Private Class Members */
				//What's being stored in this pointer instance
				T* ref;
		};

	};

};

#endif //GALACTIC_INTERNAL_SCOPEDPOINTER