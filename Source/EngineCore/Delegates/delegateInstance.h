/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* delegateInstance.h
*
* Declares a template base class for all delegate signatures
**/

#ifndef GALACTIC_CORE_DELEGATE_INSTANCE
#define GALACTIC_CORE_DELEGATE_INSTANCE

namespace Galactic {

	namespace Core {

		/*
		enum DelegateType: Global enumeration for the type of delegate being created
		*/
		enum DelegateType {
			//StrongPointerReference: Stored in a StrongReferencePtr<X, NotThreadSafe> instance
			StrongPointerReference,
			//ThreadSafeStrongPointerReference: Stored in a StrongReferencePtr<X, ThreadSafe> instance
			ThreadSafeStrongPointerReference,
			//CPPMemberMethod: Stored as a pointer to a C++ class-member function
			CPPMemberMethod,
			//CPPMethod: Stored as a pointer to a statically declared global C++ function
			CPPMethod,
		};

		/*
		DelegateInstance: A set of templated virtual functions that are overloaded by other delegate signatures
		*/ 
		class DelegateInstance {
			public:
				/* Constructor / Destructor */
				//Destructor
				virtual ~DelegateInstance() { }

				/* Public Class Methods */
				//Return a pointer to the stored C++ method
				virtual cAny getMethodPointer() const = 0;
				//Return a pointer to the stored object being referenced
				virtual cAny getObjectPointer() const = 0;
				//Returns the type of delegate
				virtual DelegateType getDelegateType() const = 0;
				//Check if this delegate has been bound to the same object (class) reference as another
				virtual bool boundToSameObject(cAny trgObj) const = 0;
				//Can this delegate still execute?
				virtual bool canExecute() const = 0;
				//Can we expire portions of a multi-cast delegate, this is a flag to tell the instance to remove NULL instances from it's DynArray
				virtual bool canExpireMCDelegates() const {
					return !canExecute();
				}
		};

	};

};

#endif //GALACTIC_CORE_DELEGATE_INSTANCE