/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* delegateCore.h
*
* Declares the main class instance for Delegate signatures
*
**/

#ifndef GALACTIC_CORE_DELEGATE_CORE
#define GALACTIC_CORE_DELEGATE_CORE

namespace Galactic {

	namespace Core {

		/*
		DelegateCore: The base class for single-cast delegates, accepts a single template parameter for the pointer type being 
		 accepted by this delegate signature.
		*/
		/*template <typename ptrType = NULL> */
		class DelegateCore {
			public:
				/* Constructor / Destructor */
				//Default Constructor
				DelegateCore(DelegateInstance *dInst) : dInstance(dInst) { }

				/* Public Class Methods */
				//Is this delegate bound?
				FINLINE bool bound() const {
					return ((dInstance != NULL) && dInstance->canExecute());
				}
				//Unbind a delegate from this class instance
				FINLINE void unbindDelegate() {
					if (dInstance != NULL) {
						SendToHell(dInstance);
					}
				}

			protected:
				/* Protected Class Methods */
				//Set a new delegate instance to this Core
				FINLINE void applyNewDInstance(DelegateInstance *newInstance) {
					unbindDelegate();
					dInstance = newInstance;
				}
				//Fetch the delegate instance object
				DelegateInstance *fetchDInstance() const {
					return dInstance;
				}

			private:
				/* Private Class Members */
				//The instance of this delegate
				DelegateInstance *dInstance;
		};

	};

};

#endif //GALACTIC_CORE_DELEGATE_CORE