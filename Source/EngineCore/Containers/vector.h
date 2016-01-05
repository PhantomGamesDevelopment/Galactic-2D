/**
* Galactic 2D
* Source/EngineCore/Containers/vector.h
* Defines a dynamically allocated array instance, more commonly refered to as a Vector
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

#ifndef GALACTIC_INTERNAL_VECTOR
#define GALACTIC_INTERNAL_VECTOR

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		Vector is a template array class, you can create a definition of a dynamically adjusting array of objects by means of
		 Vector<class> x; Numerous arrayObj operations are provided in the class definition below, however the application of the Vector
		 class behaves quite similarly to that of std::Vector, thus granting std::Vector capabilities without needing the STL.
		*/
		template <class T> class Vector {	
			typedef T& ref;
			typedef const T* X;
			typedef T* Y;
			typedef const T& Z;

			public:
				//Vector Constructor: initial size definition 
				Vector(Z32 initialSize = 0);
				//Vector Constructor: Clone existing array definition
				Vector(const Vector & c);
				//Vector Destructor.
				~Vector();

				//Standard STD::Vector function list.
				//Returns a pointer to the first element in the arrayObj.
				Y begin();
				//Returns a constant pointer to the first element in the arrayObj.
				X begin() const;
				//Returns a pointer to the last element in the arrayObj.
				Y end();
				//Returns a constant pointer to the last element in the arrayObj.
				X end() const;

				//Returns the amount of arrayObj elements in the arrayObj.
				S32 size() const;
				//Tests to see if the arrayObj is currently empty
				bool isEmpty() const;
				//Tests the arrayObj to check is an element is within the arrayObj
				bool contains(Z e) const;

				//Insets an element at the position defined by T* i.
				void insert(Y i, Z n);
				//Erases the first element with the instance of T* i.
				void erase(Y i);

				//De-referenced version of begin();
				ref front();
				//De-referenced version of const begin();
				Z front() const;
				//De-referenced version of end();
				ref back();
				//De-referenced version of const end();
				Z back() const;

				//Pushes an element to the front of the arrayObj
				void pushToFront(Z e);
				//Pushes an element to the back of the arrayObj
				void pushToBack(Z e);
				//Removes the front element from the arrayObj
				void popFront();
				//Removes the back element from the arrayObj
				void popBack();

				//Finds the first instance of ref found from startPosition
				S32 findNext(Z e, U32 startPosition = 0) const;
				//Obtain an element by position using the standard arrayObj operator
				ref operator[](U32);
				//Alternate definition of operator [], using const ref
				Z operator[](U32) const;

				/* Memory Functions */
				//Reserves space in the arrayObj for future definitions
				void reserve(U32 size);
				//Returns the current capacity (maximum element count) of the arrayObj
				U32 capacity() const;
				//Returns the memory used by the arrayObj
				U32 memSize() const;
				//Sets the maximum capacity of the arrayObj
				U32 setSize(U32 s);
				//Returns a constant pointer instance of the arrayObj
				Y addr() const;

				/* Additional Functions */
				//Creates a single new allocated reference at the end of the arrayObj
				void inc();
				//Removes the last entry from the arrayObj, if it is allocated, this function will remove the reference to it.
				void dec();
				//Creates a defined amount of allocated references at the end of the arrayObj
				void inc(U32 amount);
				//Removes a defied amount of references from the end of the arrayObj and deallocated memory to any direct object references.
				void dec(U32 amount);
				//Inserts a blank class T reference at position pos.
				void insert(U32 pos);
				//Inserts a pre-defined object into the arrayObj at position pos.
				void insert(U32 pos, Z e);
				//Removes a reference from the arrayObj at a specified position.
				void erase(U32 pos);
				//Removes multiple references from the arrayObj starting at a specified position.
				void erase(U32 startPos, U32 amount);
				//Deletes everything from the arrayObj
				void clear();
				//Clears all empty (deallocated) instances from the arrayObj
				void compact();
				//Fills the entire arrayObj (allocated space) with instances of const T& Value
				void fill(Z value);
				//Removes all instances of const T& found from the arrayObj.
				U32 eraseSpecific(Z value);
				//Memory aid function.
				void set(any addr, U32 size);

				/* More Refs */
				//Returns the first element in the arrayObj
				ref first();
				//Re-definition of first() using a const T& reference
				Z first() const;
				//Returns the last element in the arrayObj
				ref last();
				//Re-definition of last() using a const T& reference
				Z last() const;

			protected:
				/* Array Item Info */
				//The amount of allocated elements the arrayObj is using
				U32 elementCount;
				//The amount of elements the arrayObj can use, containing both allocated and un-allocated elements
				U32 arrayObjSize;
				//The pointer instance to each element within the arrayObj
				Y arrayObj;

				/* Standard Array Functions (Protected) */
				//resize the memory space of the arrayObj for allocation
				bool resize(U32 count);
				//remove (destruct) all instances between start and end
				void remove(U32 start, U32 end);
				//construct all instances between start and end
				void constr(U32 start, U32 end);
				//construct, using an existing arrayObj-element instance all instances between start and end
				void constr(U32 start, U32 end, X element);
		};

		/*
		VectorPtr is used for arrayObjs of pointer objects.
		*/
		template <class T> class VectorPtr : public Vector<any> {
			public:
				//Parent Class Definition
				typedef Vector<any> Parent;

				//Constructor.
				VectorPtr() { }

				T* begin() { return (T*)Parent::begin(); }
				const T* begin() const { return (const T*)Parent::begin(); }
				T* end() { return (T*)Parent::end(); }
				const T* end() const { return (const T*)Parent::end(); }

				void insert(T* p, const T& i) { Parent::insert((Parent::Y)p, (Parent::ref)i); }
				void insert(S32 pos) { Parent::insert(pos) }
				void erase(T* i) { Parent::erase((Parent::Y)i); }

				T& front() { return *begin(); }
				const T& front() const { return *begin(); }
				T& back() { if(elementCount == 0) { return NULL; } return (*(end()-1)); }
				const T& back() const { if(elementCount == 0) { return NULL; } return (*(end()-1)); }

				void pushToFront(const T& e) { Parent::pushToFront((Parent::Z)e); }
				void pushToBack(const T& e) { Parent::pushToBack((Parent::Z)e); }

				T& operator[](U32 i) { return (T&)Parent::operator[](i); }
				const T& operator[](U32 i) const { return (const T&)Parent::operator[](i); }

				T& first() { return (T&)Parent::first(); }
				const T& first() const { (const T&)Parent::first(); }
				T& last() { return (T&)Parent::last(); }
				const T& last() const { (const T&)Parent::last(); }

		};

		/**
		**/
		template <class T> Vector<T>::Vector(Z32 initialSize) {
			arrayObj = NULL;
			elementCount = 0;
			arrayObjSize = 0;

			if(initialSize > 0) {
				reserve(initialSize);
			}
		}

		template <class T> Vector<T>::Vector(const Vector & c) {
			//Copy one Vector into another.
			arrayObj = NULL;
			resize(c.elementCount);
			constr(0, p.elementCount, p.arrayObj);
		}

		template <class T> Vector<T>::~Vector() {
			clear();
			//Compiler is bitching with C2146 if you use SendToHeaven() Here.
			free(arrayObj);
			arrayObj = NULL;
		}

		template <class T> T* Vector<T>::begin() {
			return arrayObj;
		}

		template <class T> const T* Vector<T>::begin() const {
			return arrayObj;
		}

		template <class T> T* Vector<T>::end() {
			return arrayObj + elementCount;
		}

		template <class T> const T* Vector<T>::end() const {
			return arrayObj + elementCount;
		}

		template <class T> S32 Vector<T>::size() const {
			return (S32)elementCount;
		}

		template <class T> bool Vector<T>::isEmpty() const {
			return (elementCount == 0);
		}

		template <class T> bool Vector<T>::contains(const T& e) const {
			const T* iterator = begin();
			while(iterator != end()) {
				if(*iterator == e) {
					return true;
				}
				iterator++;
			}
			return false;
		}

		template <class T> void Vector<T>::insert(T* position, const T& newItem) {
			U32 indexPosition = (U32)(position - arrayObj);
			insert(indexPosition);
			arrayObj[index] = newItem;
		}

		template <class T> void Vector<T>::erase(T* position) {
			erase(U32(position - arrayObj));
		}

		template <class T> T& Vector<T>::front() {
			if(elementCount == 0) {
				//ToDo: Throw an assert error here
			}
			return *begin();
		}

		template <class T> const T& Vector<T>::front() const {
			if(elementCount == 0) {
				//ToDo: Throw an assert error here
			}
			return *begin();
		}

		template <class T> T& Vector<T>::back() {
			if(elementCount == 0) {
				//ToDo: Throw an assert error here
			}
			return *(end() - 1);
		}

		template <class T> const T& Vector<T>::back() const {
			if(elementCount == 0) {
				//ToDo: Throw an assert error here
			}
			return *(end() - 1);
		}

		template <class T> void Vector<T>::pushToFront(const T& e) {
			insert(0);
			arrayObj[0] = e;
		}

		template <class T> void Vector<T>::pushToBack(const T& e) {
			inc();
			arrayObj[elementCount - 1] = e;
		}

		template <class T> void Vector<T>::popFront() {
			if(elementCount == 0) {
				//No element to pop.
				return;
			}
			erase(U32(0));
		}

		template <class T> void Vector<T>::popBack() {
			if(elementCount == 0) {
				//No element to pop.
				return;
			}
			dec(); //dec() handles deletion of the back element.
		}

		template <class T> S32 Vector<T>::findNext(const T& e, U32 startPos) const {
			if(start >= elementCount) {
				return -1;
			}
			for(U32 i = startPos; i < elementCount; i++) {
				if(arrayObj[i] == x) {
					return S32(i);
				}
			}
			return -1;
		}

		template <class T> T& Vector<T>::operator[](U32 index) {
			if(index < 0 || index >= elementCount) {
				//ToDo: Throw an assert error here
			}
			return arrayObj[index];
		}

		template <class T> const T& Vector<T>::operator[](U32 index) const {
			if(index < 0 || index >= elementCount) {
				//ToDo: Throw an assert error here
			}
			return arrayObj[index];
		}

		template <class T> void Vector<T>::reserve(U32 size) {
			if(size <= arrayObjSize) {
				//cannot de-allocate space using reserve
				return;
			}
			Z32 eCount = elementCount;
			if(resize(size)) {
				//resize adjusts the element count, however it remains unchanged, we simply are "reserving" new space.
				elementCount = eCount; 
			}
		}

		template <class T> U32 Vector<T>::capacity() const {
			return arrayObjSize;
		}

		template <class T> U32 Vector<T>::memSize() const {
			return capacity() * sizeof(T);
		}

		template <class T> U32 Vector<T>::setSize(U32 s) {
			Z32 oldSize = elementCount;
			if(s > elementCount) {
				//growing.
				if(s > arrayObjSize) {
					resize(s);
				}
				elementCount = s;
				constr(oldSize, s);
			}
			else {
				//shrinking.
				remove(s, oldSize);
				elementCount = s;
			}
			return elementCount;
		}

		template <class T> T* Vector<T>::addr() const {
			return arrayObj;
		}

		template <class T> void Vector<T>::inc() {
			if(elementCount == arrayObjSize) {
				resize(elementCount + 1);
			}
			else {
				elementCount++;
			}
			//Create the new reference.
			createRef(&arrayObj[elementCount - 1]);
		}

		template <class T> void Vector<T>::dec() {
			if(elementCount == 0) {
				//No elements to delete.
				return;
			}
			elementCount--;
			//Delete the reference.
			killRef(&arrayObj[elementCount]);
		}

		template <class T> void Vector<T>::inc(U32 amount) {
			U32 currentCount = elementCount;
			if((elementCount += amount) >= arrayObjSize) {
				resize(elementCount);	
			}
			constr(currentCount, elementCount);
		}

		template <class T> void Vector<T>::dec(U32 amount) {
			if(elementCount == 0) {
				//Cannot decrement with 0 elements
				return;
			}
			Z32 currentCount = elementCount;
			U32 countNow = elementCount;
			if(elementCount > amount) {
				countNow -= amount;
			}
			else {
				countNow = 0;
			}

			remove(countNow, currentCount);
			elementCount = countNow;
		}

		template <class T> void Vector<T>::insert(U32 pos) {
			if(pos < 0 || pos >= elementCount) {
				if(GALACTIC_DONT_REPORT_INTERNAL_ERRORS != 0) {
					GC_Error("Vector::insert(%i): Cannot insert an element outside of the array bounds [0 - %i].", pos, elementCount);
				}
				return;
			}
			if(elementCount == arrayObjSize) {
				resize(elementCount + 1);
			}
			else {
				elementCount++;
			}
			//Adjust nearby elements
			memmove(&arrayObj[pos+1], &arrayObj[pos], (elementCount - pos - 1) * sizeof(T));
			//Create the reference.
			createRef(&arrayObj[pos]);
		}

		template <class T> void Vector<T>::insert(U32 pos, const T& e) {
			insert(pos);
			arrayObj[pos] = e;
		}

		template <class T> void Vector<T>::erase(U32 pos) {
			if(pos < 0 || pos >= elementCount) {
				if(GALACTIC_DONT_REPORT_INTERNAL_ERRORS != 0) {
					GC_Error("Vector::erase(%i): Cannot erase an element outside of the array bounds [0 - %i].", pos, elementCount);
				}
				return;
			}
			//Delete the reference.
			killRef(&arrayObj[pos]);
			if(pos < (elementCount - 1)) {
				//Move existing memory into the correct position
				memmove(&arrayObj[pos], &arrayObj[pos+1], (elementCount - pos - 1) * sizeof(T)); 
			}
			elementCount--;
		}

		template <class T> void Vector<T>::erase(U32 start, U32 amount) {
			if(start < 0 || start >= elementCount) {
				if(GALACTIC_DONT_REPORT_INTERNAL_ERRORS != 0) {
					GC_Error("Vector::erase(%i, %i): Cannot erase elements outside of the array bounds [0 - %i].", start, amount, elementCount);
				}
				return;
			}
			if(amount <= 0) {
				if(GALACTIC_DONT_REPORT_INTERNAL_ERRORS != 0) {
					GC_Error("Vector::erase(%i, %i): Cannot erase an element count less than 0.", start, amount);
				}
				return;
			}
			if(start+amount >= elementCount) {
				if(GALACTIC_DONT_REPORT_INTERNAL_ERRORS != 0) {
					GC_Error("Vector::erase(%i, %i): Cannot erase elements that are outside of the array bounds [0 - %i (Attempted %i)].", start, amount, elementCount, start + amount);
				}
				return;
			}
			remove(start, start + amount);
			memmove(&arrayObj[start], &arrayObj[start+amount], (elementCount - start - amount) * sizeof(T));
			elementCount -= amount;
		}

		template <class T> void Vector<T>::clear() {
			remove(0, elementCount);
			elementCount = 0;
		}

		template <class T> void Vector<T>::compact() {
			resize(elementCount);
		}

		template <class T> void Vector<T>::fill(const T& value) {
			for(U32 i = 0; i < size() i++) {
				arrayObj[i] = value;
			}
		}

		template <class T> U32 Vector<T>::eraseSpecific(const T& value) {
			U32 count = 0;
			T* iterator = begin();
			while(iterator != end()) {
				if(*iterator == value) {
					erase(iterator);
					count++;
				}
				iterator++;
			}
			return count;
		}

		template <class T> void Vector<T>::set(any addr, U32 size) {
			if(!addr) {
				size = 0;
			}
			setSize(size);
			if(addr && size > 0) {
				memcpy(addr(), addr, size * sizeof(T));
			}
		}

		template <class T> T& Vector<T>::first() {
			if(elementCount == 0) {
				//ToDo: Throw an assert error here
			}
			return arrayObj[0];
		}

		template <class T> const T& Vector<T>::first() const {
			if(elementCount == 0) {
				//ToDo: Throw an assert error here
			}
			return arrayObj[0];
		}

		template <class T> T& Vector<T>::last() {
			if(elementCount == 0) {
				//ToDo: Throw an assert error here
			}
			return arrayObj[elementCount - 1];
		}

		template <class T> const T& Vector<T>::last() const {
			if(elementCount == 0) {
				//ToDo: Throw an assert error here
			}
			return arrayObj[elementCount - 1];
		} 
		 
		template <class T> bool Vector<T>::resize(U32 count) {
			any *arrayObjPtr = (any *) &arrayObj;

			X32 VectorBlockSize = GALACTIC_DYNARRAY_RESIZE_BLOCK_SIZE;
			if(count > 0) {
				U32 arrayObjBlocks = count / VectorBlockSize;
				if(count % VectorBlockSize) {
					arrayObjBlocks++;
				}
				S32 arrayObjMemSize = arrayObjBlocks * VectorBlockSize * sizeof(T);
				*arrayObjPtr = *arrayObjPtr ? realloc(*arrayObjPtr, arrayObjMemSize) : malloc(arrayObjMemSize);
				elementCount = count;
				arrayObjSize = arrayObjBlocks * VectorBlockSize;
				return true;
			}

			if(*arrayObjPtr) {
				//Compiler is bitching with C2146 if you use SendToHeaven() Here.
				free(*arrayObjPtr);
				arrayObjPtr = NULL;
			}
			arrayObjSize = 0;
			elementCount = 0;
			return true;
		}

		template <class T> void Vector<T>::remove(U32 start, U32 end) {
			if(start < 0 || end < 0 || start >= elementCount || end >= elementCount) {
				if(GALACTIC_DONT_REPORT_INTERNAL_ERRORS != 0) {
					GC_Error("Vector::remove(%i, %i): Cannot remove elements outside of the array bounds [0 - %i].", start, end, elementCount);
				}
				return;
			}
			while(start < end) {
			   killRef(&arrayObj[start++]);	
			}
		}

		template <class T> void Vector<T>::constr(U32 start, U32 end) {
			if(start < 0 || end < 0 || start >= elementCount || end >= elementCount) {
				if(GALACTIC_DONT_REPORT_INTERNAL_ERRORS != 0) {
					GC_Error("Vector::constr(%i, %i): Cannot construct elements outside of the array bounds [0 - %i].", start, end, elementCount);
				}
				return;
			}
			while(start < end) {
				createRef(&arrayObj[start]);
				start++;
			}
		}

		template <class T> void Vector<T>::constr(U32 start, U32 end, const T* element) {
			if(start < 0 || end < 0 || start >= elementCount || end >= elementCount) {
				if(GALACTIC_DONT_REPORT_INTERNAL_ERRORS != 0) {
					GC_Error("Vector::constr(%i, %i, x): Cannot construct elements outside of the array bounds [0 - %i].", start, end, elementCount);
				}
				return;
			}
			while(start < end) {
				createRef(&arrayObj[start], &element[start]);
				start++;
			}
		}

	};

};

#endif //GALACTIC_INTERNAL_VECTOR