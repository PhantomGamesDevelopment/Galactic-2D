/**
* Galactic 2D
* Source/EngineCore/Tools/reference.h
* Defines a list of standard & advanced pointer reference templates
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

/**
* References:
* http://www.boost.org/doc/libs/1_55_0/libs/smart_ptr/shared_ptr.htm (Heavily Used)
* http://stackoverflow.com/questions/5370938/weak-strong-reference-pointer-relationship
* http://stackoverflow.com/questions/441814/fully-thread-safe-shared-ptr-implementation
* http://en.cppreference.com/w/cpp/language/auto
**/

#ifndef GALACTIC_INTERNAL_REFERENCE
#define GALACTIC_INTERNAL_REFERENCE

namespace Galactic {

	namespace Core {

		/*
		* Galactic 2D Advanced Reference Pointer Library.
		*  Dependancies: (../engineCore.h => ../platform.h, ../x/xAtomics.h, ../../Galactic::Console/Galactic::Console.h)
		*
		* reference.h declares a set of "reference" pointers that can be used throughout the engine. Theese references allow for one object to
		*  share multiple pointer instances throughout the engine, granting advanced funtionality to methods and systems that need to take 
		*  advantage of this form of system. The engine gives you the following classes to use:
		*
		* StrongReference<T>: A strong reference is a non-NULL pointer instance to a specified object. As long as there are one or more strong references
		*  on the object, the object is not allowed to be destroyed. If all strong references are destroyed, the object is also destroyed.
		*
		* StrongReferencePtr<T>: Expands on the functioning of StrongReference, however, it allows the pointer to be NULL for backwards C++ compatability.
		*
		* WeakReferencePtr<T>: A weak reference pointer is a pointer instance to a specified object with lenient object rules. The object is allowed to be 
		*  deleted at any time, if this is the case, the weak pointer is also deleted. Unlike the strong references, if all weak references are
		*  destroyed, the object is not destroyed.
		*
		* makeRefPtr<T>: This is a special template class that is overloaded by a secondary class. Whenever the secondary class is instanced by
		*  another method, it automatically creates a StrongReference<T> to the object.
		*
		* All of these classes have a secondary template parameter to declare thread-safety rules. These rules are specified under PointerModes::TSRules as
		*  * NonThreadSafe: The pointer instance is not thread safe.
		*  * ThreadSafe: The pointer instance is thread safe by means of atomic locking methods.
		*  * Determine: Select NonThreadSafe or ThreadSafe based on the setting GALACTIC_THREADSAFE_SHAREDPTRS. (Default)
		*/

		/****************************************************************************************************************************
		*****************************************************************************************************************************
		*****************************************************************************************************************************
		*****************************************************************************************************************************
		* The first half of this source file declares properties and mechanics used by our pointer template classes. You shouldn't  *
		*  have to directly work with any of these methods when working on your project, but in the event you're looking to         *
		*  properly document or follow the innerworkings of the reference system in the engine, this is a great place to start.     *
		*****************************************************************************************************************************
		*****************************************************************************************************************************
		****************************************************************************************************************************/

		/*
		PointerModes: This struct contains a define used for our system. Basically it defines a few modes that our shared pointers have access to.
		*/
		struct PointerModes {
			//TSMode: Declares the thread-safety mode of the shared pointer
			enum TSMode {
				//NonThreadSafe: Fastest form of the shared pointer, however, it cannot be safely used in threads
				NonThreadSafe = 0,
				//ThreadSafe: Slower than NonThreadSafe, however all functioning is completely thread safe
				ThreadSafe = 1,
				//Determine: Use this define to have the engine automatically determine which one of these modes to use
				Determine = GALACTIC_THREADSAFE_STRONGPTRS ? 1 : 0,
			};

			//Tags: Declares a list of pointer tags that may be used throughout the engine
			enum Tags {
				//Null: Pointer is tagged as NULL
				Null = 0,
				//ConstCast: Pointer is being tagged for a const_cast operation
				ConstCast = 1,
				//StaticCast: Pointer is being tagged for a static_cast operation
				StaticCast = 2,
				//DynamicCast: Pointer is being tagged for a dynamic_cast operation
				DynamicCast = 3,
			};
		};

		/* Start with forward declarations for all of the classes and objects we define */
		//Forward declaration for StrongReference
		template <class T, PointerModes::TSMode tsMode = PointerModes::Determine> class StrongReference;
		//Forward declaration for StrongReferencePtr
		template <class T, PointerModes::TSMode tsMode = PointerModes::Determine> class StrongReferencePtr;
		//Forward declaration for WeakReferencePtr
		template <class T, PointerModes::TSMode tsMode = PointerModes::Determine> class WeakReferencePtr;
		//Forward declaration for makeRefPtr conversion class
		template <class T, PointerModes::TSMode tsMode = PointerModes::Determine> class makeRefPtr;
		//Forward declaration for WeakObject
		template <PointerModes::TSMode tsMode> class WeakObject;
		//Forward declaration for Reference
		template <PointerModes::TSMode tsMode> class Reference;

		/*
		RawProxy: This is a template class used to convert non-referenced pointer objects to a reference pointer.
		*/
		template <class T> class RawProxy {
			public:
				/* Constructor / Destructor */
				//Default Constructor
				FINLINE RawProxy(T* newObj) : obj(newObj) { }

				/* Public Class Members */
				//The stored object pointer
				T* obj;
		};

		/*
		ReferenceController: This class controls the object itself by defining what types of references are attached to it. Note! All objects spawn with one weak
		 reference attahced to it, and that is the reference to this ReferenceController instance. When all other instances are deleted, the referenceController 
		 will also be deleted.
		*/
		class ReferenceController {
			public:
				/* Constructor / Destructor */
				//Default Constructor
				FINLINE ReferenceController(any trgObj, void (*trgDeleteParams)(any)) :
					strongRefCount(1),
					weakRefCount(1),
					obj(trgObj),
					deleteObj(trgDeleteParams) { }

				/* Public Class Members */
				//The stored object pointer
				any obj;
				//Shortcut to void deleteObj() specified below.
				void (*deleteObj)(any);
				//How many strong references are on this object
				S32 strongRefCount;
				//How many weak references are on this object
				S32 weakRefCount;

			private:
				/* Private Class Methods */
				//Copy Constructor
				ReferenceController(const ReferenceController &c) :
					strongRefCount(c.strongRefCount),
					weakRefCount(c.weakRefCount),
					obj(c.obj),
					deleteObj(c.deleteObj) { }

				//Assignment Operator
				ReferenceController &operator=(const ReferenceController& c) {
					strongRefCount = c.strongRefCount;
					weakRefCount = c.weakRefCount;
					obj = c.obj;
					deleteObj = c.deleteObj;
				}
		};

		/*
		Reference <NonThreadSafe>: Defines functions and parameters for a non-thread safe reference class.
		*/
		template<> class Reference <PointerModes::TSMode::NonThreadSafe> {
			public:
				/* Public Class Methods */
				//Fetch weak reference count
				SFIN X32 fetchWeakRefCount(ReferenceController *store) {
					return store->weakRefCount;
				}

				//Fetch strong reference count
				SFIN X32 fetchStrongRefCount(ReferenceController *store) {
					return store->strongRefCount;
				}

				//Add a weak reference
				SFIN void addWeakRef(ReferenceController *store) {
					store->weakRefCount++;
				}

				//Add a strong reference
				SFIN void addStrongRef(ReferenceController *store) {
					store->strongRefCount++;
				}

				//Add a strong reference only if the pointer still exists.
				static bool addStrongRef_Safe(ReferenceController *store) {
					if (store->strongRefCount > 0) {
						store->strongRefCount++;
						return true;
					}
					return false;
				}

				//Remove a weak reference
				static void killWeakRef(ReferenceController *store) {
					if (store->weakRefCount <= 0) {
						//GC_Error("killWeakRef: Cannot release any more weak references.");
						return;
					}
					store->weakRefCount--;
					if (store->weakRefCount == 0) {
						SendToPitsOfHell(store);
					}
				}

				//Remove a strong reference
				static void killStrongRef(ReferenceController *store) {
					if (store->strongRefCount <= 0) {
						//GC_Error("killStrongRef: Cannot release any more strong references.");
						return;
					}
					store->strongRefCount--;
					if (store->strongRefCount == 0) {
						store->deleteObj(store->obj);
						//If we're the last strong ref, release the weak ref, which will delete the reference pointer.
						killWeakRef(store);
					}
				}
		};

		/*
		Reference <ThreadSafe>: Defines functions and parameters for a thread safe reference class.
		*/
		template<> class Reference <PointerModes::TSMode::ThreadSafe> {
			public:
				/* Public Class Methods */
				//Fetch weak reference count
				SFIN X32 fetchWeakRefCount(ReferenceController *store) {
					//Since this method can be accessed by multiple threads at once, we need to ensure the value is updated for these threads.
					return static_cast<volatile X32&>(store->weakRefCount);
				}

				//Fetch strong reference count
				SFIN X32 fetchStrongRefCount(ReferenceController *store) {
					//Since this method can be accessed by multiple threads at once, we need to ensure the value is updated for these threads.
					return static_cast<volatile X32&>(store->strongRefCount);
				}

				//Add a weak reference
				SFIN void addWeakRef(ReferenceController *store) {
					PlatformAtomics::increment(&store->weakRefCount);
				}

				//Add a strong reference
				SFIN void addStrongRef(ReferenceController *store) {
					PlatformAtomics::increment(&store->strongRefCount);
				}

				//Add a strong reference only if the pointer still exists.
				static bool addStrongRef_Safe(ReferenceController *store) {
					//We keep looping through to ensure the thread-safe counter is at the absolute value we need for determining if we're adding one or not.
					while (true) {
						X32 origStrongs = static_cast<volatile X32 &>(store->strongRefCount);
						if (origStrongs > 0) {
							X32 currentCount = PlatformAtomics::compareExchange(&store->strongRefCount, origStrongs+1, origStrongs);
							if (currentCount == origStrongs) {
								//We've successfully added.
								return true;
							}
							//If the statement falls down here, then the loop will run again since another thread has interrupted the counter.
						}
						else {
							return false;
						}
					}
				}

				//Remove a weak reference
				static void killWeakRef(ReferenceController *store) {
					if (fetchWeakRefCount(store) <= 0) {
						//GC_Error("killWeakRef: Cannot release any more weak references.");
						return;
					}
					PlatformAtomics::decrement(&store->weakRefCount);
					if (fetchWeakRefCount(store) == 0) {
						SendToPitsOfHell(store);
					}
				}

				//Remove a strong reference
				static void killStrongRef(ReferenceController *store) {
					if (fetchStrongRefCount(store) <= 0) {
						//GC_Error("killStrongRef: Cannot release any more strong references.");
						return;
					}
					PlatformAtomics::decrement(&store->strongRefCount);
					if (fetchStrongRefCount(store) == 0) {
						store->deleteObj(store->obj);
						//If we're the last strong ref, release the weak ref, which will delete the reference pointer.
						killWeakRef(store);
					}
				}
		};

		/* 
		deleteParam(): Shortcut function to delete a template object by safe-casting it to the correct pointer before deleting
		*/
		template <typename T> void deleteObj(any trg) {
			SendToPitsOfHell((T *)trg);
		}

		/*
		StrongObject: Wrapper to a pointer object which tracks a strong object throughout it's lifetime in the engine.
		*/
		template <PointerModes::TSMode tsMode> class StrongObject {
			//Shortcut to Reference<tsMode>
			typedef Reference<tsMode> ref;

		public:
			/* Constructor / Destructor */
			//Default Constructor
			FINLINE StrongObject() : controller(NULL) { }
			//Direct Creation (From Object) Contructor
			template <class T> FINLINE explicit StrongObject(T* obj) : controller(new ReferenceController(obj, &deleteObj<T>)) { }
			//Copy Constructor (Copy From Strong)
			FINLINE StrongObject(const StrongObject &c) : controller(c.controller) {
				//Since we already have a controller and an object, simply add one to the strong reference count
				if (controller != NULL) {
					ref::addStrongRef(controller);
				}
			}
			//Copy Constructor (Copy From Weak)
			FINLINE StrongObject(const WeakObject<tsMode>& c) : controller(c.controller) {
				//Adding a weak reference requires that a pointer already be present, we can validate that here
				if (controller != NULL) {
					//Now, attempt to add the strong reference, this will only work is another reference is present to keep the object alive.
					if (!ref::addStrongRef_Safe(controller)) {
						//If the operation failed, then it's just a pointer waiting to be deleted, cancel out.
						controller = NULL;
					}
				}
			}
			//Destructor
			FINLINE ~StrongObject() {
				//If the controller is still alive, release the reference, the controller will handle the rest.
				if (controller != NULL) {
					ref::killStrongRef(controller);
				}
			}

			/* Public Class Methods */
			//Is the object valid?
			FINLINE const bool valid() const {
				return controller != NULL;
			}
			//Is the object unique, IE: only one reference?
			FINLINE const bool unique() const {
				return (fetchStrongRefCount() == 1);
			}
			//Fetch the number of strong references on the object
			FINLINE X32 fetchStrongRefCount() const {
				return controller != NULL ? ref::fetchStrongRefCount(controller) : 0;
			}

			/* Operators */
			//Assignment operator
			FINLINE StrongObject &operator=(const StrongObject &c) {
				//'auto' is used here to ensure the controller keeps the correct PointerModes::TSMode setting
				auto newController = c.controller;
				if (newController != controller) {
					if (newController != NULL) {
						ref::addStrongRef(newController);
					}
					if (controller != NULL) {
						ref::killStrongRef(controller);
					}
					controller = newController;
				}
				THISREF();
			}

		private:
			/* Private Class Members */
			//Pointer to the ReferenceController object
			ReferenceController *controller;
			//Grant Friend Level Access To WeakObject
			template <PointerModes::TSMode m> friend class WeakObject;
		};

		/*
		WeakObject: Wrapper to a pointer object which tracks a weak object throughout it's lifetime in the engine.
		*/
		template <PointerModes::TSMode tsMode> class WeakObject {
			//Shortcut to Reference<tsMode>
			typedef Reference<tsMode> ref;

			public:
				/* Constructor / Destructor */
				//Default Constructor
				FINLINE WeakObject() : controller(NULL) { }
				//Direct Creation (From Object) Contructor
				template <class T> FINLINE explicit WeakObject(T* obj) : controller(new ReferenceController(obj, &deleteObj<T>)) { }
				//Copy Constructor (Copy From Weak)
				FINLINE WeakObject(const WeakObject &c) : controller(c.controller) {
					//Since we already have a controller and an object, simply add one to the weak reference count
					if (controller != NULL) {
						ref::addWeakRef(controller);
					}
				}
				//Copy Constructor (Copy From Strong)
				FINLINE WeakObject(const StrongObject &c) : controller(c.controller) {
					//Since we already have a controller and an object, simply add one to the strong reference count
					if (controller != NULL) {
						ref::addWeakRef(controller);
					}
				}
				//Destructor
				FINLINE ~WeakObject() {
					//If the controller is still alive, release the reference, the controller will handle the rest.
					if (controller != NULL) {
						ref::killWeakRef(controller);
					}
				}

				/* Public Class Methods */
				//Is the object valid?
				FINLINE const bool valid() const {
					return (controller != NULL) && (ref::fetchStrongRefCount(controller) > 0);
				}

				/* Operators */
				//Assignment operator (Assign from weak)
				FINLINE WeakObject& operator=(const WeakObject &c) {
					auto newController = c.controller;
					if (newController != controller) {
						if (newController != NULL) {
							ref::addWeakRef(newController);
						}
						if (controller != NULL) {
							ref::killWeakRef(controller);
						}
						controller = newController;
					}
					THISREF();
				}
				//Assignment operator (Assign from strong)
				FINLINE WeakObject& operator=(const StrongObject &c) {
					auto newController = c.controller;
					if (newController != controller) {
						if (newController != NULL) {
							ref::addWeakRef(newController);
						}
						if (controller != NULL) {
							ref::killWeakRef(controller);
						}
						controller = newController;
					}
					THISREF();
				}

			private:
				/* Private Class Members */
				//Pointer to the ReferenceController object
				ReferenceController *controller;
				//Grant Friend Level Access To StrongObject
				template <PointerModes::TSMode m> friend class StrongObject;
		};

		/* Template Helper Functions */
		/* This method is used to statically cast a strong reference of one type to another */
		template <class newType, class oldType, PointerModes::TSMode mode> FINLINE StrongReference<newType, mode>
		StaticCastStrongReference(const StrongReference<oldType, mode> &c) {
			return StrongReference<newType, mode>(c, PointerModes::StaticCast);
		}

		/* These last methods are used to create strong reference pointers by providing an object to it */

		template <class strongType, class objType, class newType, PointerModes::TSMode mode> FINLINE
		void MakeRefPtr(const StrongReferencePtr<strongType, mode> *strongPtr, const objType *obj, const makeRefPtr<newType, mode> *newPtr) {
			if (newPtr != NULL) {
				#define GALACTIC_CREATESTRONGFROMOBJ_UPDATEWEAKREFERENCES_INTERNALCALL
					newPtr->updateWeakReferences(strongPtr, const_cast<objType *>(obj));
				#undef GALACTIC_CREATESTRONGFROMOBJ_UPDATEWEAKREFERENCES_INTERNALCALL
			}
		}

		template <class strongType, class objType, class newType, PointerModes::TSMode mode> FINLINE
		void MakeRefPtr(StrongReferencePtr<strongType, mode> *strongPtr, const objType *obj, const makeRefPtr<newType, mode> *newPtr) {
			if (newPtr != NULL) {
				#define GALACTIC_CREATESTRONGFROMOBJ_UPDATEWEAKREFERENCES_INTERNALCALL
					newPtr->updateWeakReferences(strongPtr, const_cast<objType *>(obj));
				#undef GALACTIC_CREATESTRONGFROMOBJ_UPDATEWEAKREFERENCES_INTERNALCALL
			}
		}

		template <class strongType, class objType, class newType, PointerModes::TSMode mode> FINLINE
		void MakeRefPtr(const StrongReference<strongType, mode> *strongRef, const objType *obj, const makeRefPtr<newType, mode> *newPtr) {
			if (newPtr != NULL) {
				#define GALACTIC_CREATESTRONGFROMOBJ_UPDATEWEAKREFERENCES_INTERNALCALL
					newPtr->updateWeakReferences(strongRef, const_cast<objType *>(obj));
				#undef GALACTIC_CREATESTRONGFROMOBJ_UPDATEWEAKREFERENCES_INTERNALCALL
			}
		}

		template <class strongType, class objType, class newType, PointerModes::TSMode mode> FINLINE
		void MakeRefPtr(StrongReference<strongType, mode> *strongRef, const objType *obj, const makeRefPtr<newType, mode> *newPtr) {
			if (newPtr != NULL) {
				#define GALACTIC_CREATESTRONGFROMOBJ_UPDATEWEAKREFERENCES_INTERNALCALL
					newPtr->updateWeakReferences(strongRef, const_cast<objType *>(obj));
				#undef GALACTIC_CREATESTRONGFROMOBJ_UPDATEWEAKREFERENCES_INTERNALCALL
			}
		}

		template <class objType> FINLINE RawProxy<objType> MakeRefPtr(objType *obj) {
			return RawProxy<objType>(obj);
		}
		
		FINLINE void MakeRefPtr(...) {
			//ToDo: Throw some kind of assert here for invalid creation?
			//GC_Error("makeRefPtr() [reference.h, 755]: Unable to deduce target pointer with specified arguments.");
		}

		/**************************************************************************************************************************
		***************************************************************************************************************************
		***************************************************************************************************************************
		***************************************************************************************************************************
		*The second half of this file actually declares the pointer classes and all of thier methods. When you're working in the  *
		* engine, you'll be using these classes and their relevant methods.                                                       *
		***************************************************************************************************************************
		***************************************************************************************************************************
		**************************************************************************************************************************/

		/*
		StrongReference: A non-NULL strong-counted object reference. This can be set to thread safe by setting the second parameter, but by
		 default it will use the engine defined parameter GALACTIC_THREADSAFE_SHAREDPTRS
		*/
		template <class T, PointerModes::TSMode m> class StrongReference {
			public:
				/* Constructor / Destructor */
				//Explicit Creation Constructor
				template <class objType> FINLINE explicit StrongReference(objType *object) : obj(object), ref(object) {
					if (!valid()) {
						//Strong references cannot be NULL, throw an error.
						GC_Error("explicit StrongReference(): Cannot initialize a NULL instance to a StrongReference, consider using StrongReferencePtr instead.");
						return;
					}
					//Cast to makeRefPtr.
					makeRefPtr(this, object, object);
				}
				//Copy Constructor
				template <class objType> FINLINE StrongReference(const StrongReference<objType, m> &c) : obj(c.obj), ref(c.ref) {
					//Since the existing strong reference has already been verified, we're good to go!
				}
				//Copy Constructor with target object parameter
				template <class objType> FINLINE StrongReference(const StrongReference<objType, m> &c, T* object) : obj(object), ref(c.ref) {
					//Since the existing strong reference has already been verified, we're good to go!
				}
				//Un-templated copy constructor
				FINLINE StrongReference(const StrongReference &c) : obj(c.obj), ref(c.ref) { }
				//Type-Cast Constructor
				template <class objType> FINLINE StrongReference(const StrongReference<objType, m> &c, PointerModes::Tags t = PointerModes::StaticCast) : obj(c.obj), ref(c.ref) {
					if (t == PointerModes::StaticCast) {
						obj = static_cast<T*>(c.obj);
					}
					else if (t == PointerModes::ConstCast) {
						obj = const_cast<T*>(c.obj);
					}
					else if (t == PointerModes::DynamicCast) {
						obj = dynamic_cast<T*>(c.obj);
					}
					else {
						GC_Error("StrongReference(): Cannot perform 2-param constructor with an unknown PointerModes::Tags param");
					}
				}
				//Create from raw-pointer constructor
				template <class objType> FINLINE StrongReference(const RawProxy<objType> &c) : obj(c.obj), ref(c.obj) {
					//Verify the object isn't NULL
					if (!valid()) {
						//Strong references cannot be NULL, throw an error.
						GC_Error("StrongReference(RawProxy<>()): Cannot initialize a NULL instance to a StrongReference, consider using StrongReferencePtr instead.");
						return;
					}
					//Cast to makeRefPtr.
					makeRefPtr(this, c.obj, c.obj);
				}

				/* Public Class Methods */
				//Get the object being referenced
				FINLINE T& getObject() const {
					if (!valid()) {
						GC_Error("StrongReference::getObject(): Cannot return an object, reference is NULL.");
						//ToDo: We need to assert here to block the below call.
					}
					return obj;
				}
				//Check if the reference is unique (IE: the only reference on the object)
				FINLINE const bool unique() const {
					return ref.unique();
				}

				/* Operators */
				//Assignment Operator (From StrongReference)
				FINLINE StrongReference& operator=(const StrongReference &c) {
					obj = c.obj;
					ref = c.ref;
					THISREF();
				}
				//Assignment Operator (From RawProxy)
				template <class objType> FINLINE StrongReference& operator=(const RawProxy<objType> &c) {
					if (c.obj == NULL) {
						GC_Error("StrongReference=(RawProxy<>): Cannot apply a NULL Proxy to a StrongReference.");
						THISREF();
					}
					//Instance a new StrongReference
					*this = StrongReference<objType, m>(c.obj);
					THISREF();
				}
				//Dereference Operator
				FINLINE T& operator*() const {
					if (!valid()) {
						GC_Error("*StrongReference(): Cannot apply the dereference operator to a NULL StrongReference.");
						//ToDo: We need to assert here to block the below call.
					}
					return *obj;
				}
				//Reference Operator
				FINLINE T* operator->() const {
					if (!valid()) {
						GC_Error("StrongReference->(): Cannot apply the reference operator to a NULL StrongReference.");
						return NULL;
					}
					return obj;
				}

			private:
				/* Private Class Methods */
				//Private Constructor: Convert StrongReferencePtr to StrongReference
				template <class objType> FINLINE explicit StrongReference(const StrongReferencePtr<objType, m> &c) : obj(c.obj), ref(c.ref) {
					if (!valid()) {
						GC_Error("explicit StrongReference(FromPtr): Cannot instance a StrongReference from a NULL StrongReferencePtr");
					}
				}

				//Check if the StrongReference is valid
				FINLINE const bool valid() const {
					return obj != NULL;
				}

				/* Private Class Members */
				//The object being referenced
				T *obj;
				//The instance of the strong reference
				StrongObject<m> ref;

				/* Grant friend level access to other (needed) classes, and ourselves with template<class objType> */
				template <class objType, PointerModes::TSMode mode> friend class StrongReference;
				template <class objType, PointerModes::TSMode mode> friend class StrongReferencePtr;
				template <class objType, PointerModes::TSMode mode> friend class WeakReferencePtr;
		};

		/*
		StrongReferencePtr: A non-intrusive object reference pointer. This can be set to thread safe by setting the second parameter, but by
		 default it will use the engine defined parameter GALACTIC_THREADSAFE_SHAREDPTRS
		*/
		template <class T, PointerModes::TSMode m> class StrongReferencePtr {
			public:
				/* Constructor / Destructor */
				//Null Constructor, AKA: default constructor
				FINLINE StrongReferencePtr(PointerModes::Tags t = PointerModes::Null) : obj(NULL), ref() { }
				//Explicit Creation Constructor
				template <class objType> FINLINE explicit StrongReferencePtr(objType *object) : obj(object), ref(object) {
					//Cast to makeRefPtr.
					makeRefPtr(this, object, object);
				}
				//Copy Constructor
				template <class objType> FINLINE StrongReferencePtr(const StrongReferencePtr<objType, m> &c) : obj(c.obj), ref(c.ref) { }
				//Copy Constructor with target object parameter
				template <class objType> FINLINE StrongReferencePtr(const StrongReferencePtr<objType, m> &c, T* object) : obj(object), ref(c.ref) { }
				//Non-Templated Copy Constructor
				FINLINE StrongReferencePtr(const StrongReferencePtr &c) : obj(c.obj), ref(c.ref) { }
				//Convert StrongReference to StrongReferencePtr
				template <class objType> FINLINE StrongReferencePtr(const StrongReference<objType, m> &c) : obj(c.obj), ref(c.ref) { }
				//Type-Cast Constructor
				template <class objType> FINLINE StrongReferencePtr(const StrongReferencePtr<objType, m> &c, PointerModes::Tags t = PointerModes::StaticCast) : obj(NULL), ref(c.ref) {
					if (t == PointerModes::StaticCast) {
						obj = static_cast<T*>(c.obj);
					}
					else if (t == PointerModes::ConstCast) {
						obj = const_cast<T*>(c.obj);
					}
					else if (t == PointerModes::DynamicCast) {
						obj = dynamic_cast<T*>(c.obj);
					}
					else {
						GC_Error("StrongReferencePtr(): Cannot perform 2-param constructor with an unknown PointerModes::Tags param");
					}
				}
				//Create from raw-pointer constructor
				template <class objType> FINLINE StrongReferencePtr(const RawProxy<objType> &c) : obj(c.obj), ref(c.obj) {
					//Cast to makeRefPtr.
					makeRefPtr(this, c.obj, c.obj);
				}

				/* Public Class Methods */
				//Check if the pointer is NULL
				FINLINE const bool null() const {
					return FBOOL(obj == NULL);
				}
				//Return the object referenced by the pointer
				FINLINE T* getPointer() const {
					return obj;
				}
				//Internal test to see if the pointer is valid (same as !null)
				FINLINE const bool valid() const {
					return FBOOL(!null());
				}
				//Check if the pointer is unique (IE: only one pointer on the object)
				FINLINE const bool unique() const {
					return ref.unique();
				}
				//Reset the pointer to the default (NULL) state
				FINLINE void reset() {
					*this = StrongReferencePtr<T, m>();
				}
				//Convert the pointer to a StrongReference, validate rules first
				FINLINE StrongReference<T, m> toStrongRef() const {
					if (!valid()) {
						GC_Error("StrongReferencePtr::toStrongRef(): Cannot convert to StrongReference, object pointer is NULL.");
						return NULL;
					}
					return StrongReference<T, m>(*this);
				}

				/* Operators */
				//Assignment Operator (From StrongReferencePtr)
				FINLINE StrongReferencePtr& operator=(const StrongReferencePtr &c) {
					obj = c.obj;
					ref = c.ref;
					THISREF();
				}
				//Assignment Operator (From RawProxy)
				template <class objType> FINLINE StrongReferencePtr& operator=(const RawProxy<objType> &c) {
					//Instance a new StrongReferencePtr
					*this = StrongReferencePtr<objType, m>(c.obj);
					THISREF();
				}
				//Assignment Operator (Assign object directly)
				FINLINE StrongReferencePtr& operator=(T* newObj) {
					*this = StrongReferencePtr<T, m>(newObj);
					THISREF();
				}
				//Assign to Null
				FINLINE StrongReferencePtr& operator=(PointerModes::Tags t) {
					if (t != PointerModes::Null) {
						THISREF();
					}
					reset();
					THISREF();
				}
				//Dereference Operator
				FINLINE T& operator*() const {
					if (!valid()) {
						GC_Error("*StrongReferencePtr(): Cannot apply the dereference operator to a NULL StrongReferencePtr.");
						//ToDo: We need to assert here to block the below call.
					}
					return *obj;
				}
				//Reference Operator
				FINLINE T* operator->() const {
					if (!valid()) {
						GC_Error("StrongReferencePtr->(): Cannot apply the reference operator to a NULL StrongReferencePtr.");
						return NULL;
					}
					return obj;
				}

			private:
				/* Private Class Methods */
				//Private Constructor: Convert a WeakReferencePtr to a StrongReferencePtr, observing pointer rules.
				template <class objType> FINLINE explicit StrongReferencePtr(const WeakReferencePtr<objType, m> &c) : obj(NULL), ref(c.ref) {
					if (ref.valid()) {
						//Only set the object if the pointer is valid.
						obj = c.obj;
					}
				}

				/* Private Class Members */
				//The object being referenced
				T *obj;
				//The instance of the strong reference
				StrongObject<m> ref;

				/* Grant friend level access to other (needed) classes, and ourselves with template<class objType> */
				template <class objType, PointerModes::TSMode mode> friend class StrongReferencePtr;
				template <class objType, PointerModes::TSMode mode> friend class StrongReference;
				template <class objType, PointerModes::TSMode mode> friend class WeakReferencePtr;
				template <class objType, PointerModes::TSMode mode> friend class makeRefPtr;
		};

		/*
		WeakReferencePtr: A non-intrusive object reference pointer. This can be set to thread safe by setting the second parameter, but by
		 default it will use the engine defined parameter GALACTIC_THREADSAFE_SHAREDPTRS
		*/
		template <class T, PointerModes::TSMode m> class WeakReferencePtr {
			public:
				/* Constructor / Destructor */
				//Null Constructor, AKA: default constructor
				FINLINE WeakReferencePtr(PointerModes::Tags t = PointerModes::Null) : obj(NULL), ref() { }
				//Copy Constructor
				template <class objType> FINLINE WeakReferencePtr(const WeakReferencePtr<objType, m> &c) : obj(c.obj), ref(c.ref) { }
				//Untemplated Copy Constructor
				FINLINE WeakReferencePtr(const WeakReferencePtr &c) : obj(c.obj), ref(c.ref) { }
				//Covert StrongReference to WeakReferencePtr
				template <class objType> FINLINE WeakReferencePtr(const StrongReference<objType, m> &c) : obj(c.obj), ref(c.ref) { }
				//Covert StrongReferencePtr to WeakReferencePtr
				template <class objType> FINLINE WeakReferencePtr(const StrongReferencePtr<objType, m> &c) : obj(c.obj), ref(c.ref) { }

				/* Public Class Methods */
				//Check if the pointer is NULL
				FINLINE const bool null() const {
					return FBOOL(obj == NULL);
				}
				//Internal test to see if the pointer is valid (same as !null)
				FINLINE const bool valid() const {
					return FBOOL(!null() && ref.valid());
				}
				//Check if the pointer is unique (IE: only one pointer on the object)
				FINLINE const bool unique() const {
					return ref.unique();
				}
				//Reset the pointer to the default (NULL) state
				FINLINE void reset() {
					*this = WeakReferencePtr<T, m>();
				}
				//Convert a WeakReferencePtr to a StrongReferencePtr
				FINLINE StrongReferencePtr<T, m> toStrongRefPtr() const {
					return StrongReferencePtr<T, m>(*this);
				}
				//Check if the specified pointer shares the same object
				FINLINE bool ptrSharesObject(cAny tPtr) const {
					return FBOOL(toStrongRefPtr().getPointer() == tPtr);
				}

				/* Operators */
				//Assignment Operator (From WeakRefPtr)
				FINLINE WeakReferencePtr& operator=(const WeakReferencePtr &c) {
					obj = c.toStrongRefPtr().getPointer();
					ref = c.ref;
					THISREF();
				}
				//Assignment Operator (From Other type of WeakRefPtr)
				template <class objType> FINLINE WeakReferencePtr& operator=(const WeakReferencePtr<objType, m> &c) {
					obj = c.toStrongRefPtr().getPointer();
					ref = c.ref;
					THISREF();
				}
				//Assignment Operator (From StrongRefPtr)
				template <class objType> FINLINE WeakReferencePtr& operator=(const StrongReferencePtr<objType, m> &c) {
					obj = c.obj;
					ref = c.ref;
					THISREF();
				}
				//Assignment Operator (From StrongRef)
				template <class objType> FINLINE WeakReferencePtr& operator=(const StrongReference<objType, m> &c) {
					obj = c.obj;
					ref = c.ref;
					THISREF();
				}
				//Assign to Null
				FINLINE WeakReferencePtr& operator=(PointerModes::Tags t) {
					if (t != PointerModes::Null) {
						THISREF();
					}
					reset();
					THISREF();
				}

			private:
				/* Private Class Members */
				//The object being referenced
				T *obj;
				//The instance of the weak reference
				WeakObject<m> ref;

				/* Grant friend level access to other (needed) classes, and ourselves with template<class objType> */
				template <class objType, PointerModes::TSMode mode> friend class WeakReferencePtr;
				template <class objType, PointerModes::TSMode mode> friend class StrongReferencePtr;
		};

		/*
		makeRefPtr: A helper class instance that is attached to a class instance to create a StrongReference<> instance of the class
		whenever it is created.
		*/
		template <class T, PointerModes::TSMode m> class makeRefPtr {
			public:
				/* Public Class Methods */
				//Return the specified object as a StrongReference instance
				StrongReference<T, m> becomeStrongRef() {
					StrongReferencePtr<T, m> strRef(weakSelf.toStrongRefPtr());
					if (strRef.getPointer() != this) {
						GC_Error("makeRefPtr::becomeStrongRef(): Cannot instance a strongReference. This is likely due to one of two reasons. 1. You called this in a constructor, 2. You called this while the object was being deleted.");
						return;
					}
					return strRef.toStrongRef();
				}
				//Return the specified object (const) as a StrongReference instance
				StrongReference<const T, m> becomeStrongRef() const {
					StrongReferencePtr<T, m> strRef(weakSelf.toStrongRefPtr());
					if (strRef.getPointer() != this) {
						GC_Error("makeRefPtr::becomeStrongRef(): Cannot instance a strongReference. This is likely due to one of two reasons. 1. You called this in a constructor, 2. You called this while the object was being deleted.");
						return;
					}
					return strRef.toStrongRef();
				}
				//Check if the pointer has already had an object instance (strongRef/strongRefPtr) attached to it, this is mainly used as a crash guard method
				FINLINE bool hasObjInstance() const {
					return weakSelf.valid();
				}

				/* Internal Methods */
				//Update the weak reference when a strongReferencePtr is instanced from a class
				template <class strongPtrType, class objType> FINLINE void updateWeakReferences(const StrongReferencePtr<strongPtrType, m> *c, objType *obj) const {
					#ifndef GALACTIC_CREATESTRONGFROMOBJ_UPDATEWEAKREFERENCES_INTERNALCALL
						GC_Warn("updateWeakReferences(): Cannot call this internal method.");
						return;
					#endif
					//Only update ourself if the pointer is not valid.
					if (!weakSelf.valid()) {
						weakSelf = StrongReferencePtr<objType, m>(*c, obj);
					}
				}
				//Update the weak reference when a strongReference is instanced from a class
				template <class strongRefType, class objType> FINLINE void updateWeakReferences(const StrongReference<strongRefType, m> *c, objType *obj) const {
					#ifndef GALACTIC_CREATESTRONGFROMOBJ_UPDATEWEAKREFERENCES_INTERNALCALL
						GC_Warn("updateWeakReferences(): Cannot call this internal method.");
						return;
					#endif
					//Only update ourself if the pointer is not valid.
					if (!weakSelf.valid()) {
						weakSelf = StrongReference<objType, m>(*c, obj);
					}
				}

			protected:
				/* Protected Class Methods */
				//Given an object instance, provide access to a StrongReference of it
				template <class objType> SFIN StrongReference<objType, m> toStrongRef(objType *obj) {
					return StaticCastStrongReference<objType>(obj->becomeStrongRef());
				}
				//Given an object instance (const), provide access to a StrongReference of it
				template <class objType> SFIN StrongReference<objType, m> toStrongRef(const objType *obj) {
					return StaticCastStrongReference<const objType>(obj->becomeStrongRef());
				}

				/* Hidden Constructors */
				//Default Constructor
				makeRefPtr() { }
				//Copy Constructor
				makeRefPtr(const makeRefPtr &c) { }
				//Destructor
				~makeRefPtr() { }

				/* Operators */
				//Assignment operator (Hidden)
				FINLINE makeRefPtr& operator=(const makeRefPtr &c) {
					THISREF();
				}

			private:
				/* Private Class Members */
				//Weak Reference To Ourself, mutable to allow access through const methods as seen in WeakReferencePtr, StrongReferencePtr, Etc.
				mutable WeakReferencePtr<T, m> weakSelf;
		};

	};

};

#endif //GALACTIC_INTERNAL_REFERENCE