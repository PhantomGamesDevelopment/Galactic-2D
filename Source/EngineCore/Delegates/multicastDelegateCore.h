/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* multicastDelegateInstance.h
*
* Declares a template base class for all multicast delegate signatures
*
**/

#ifndef GALACTIC_CORE_MULTICASTDELEGATE_INSTANCE
#define GALACTIC_CORE_MULTICASTDELEGATE_INSTANCE

namespace Galactic {

	namespace Core {

		/*
		MulticastDelegateCore: The base class for multi-cast delegates, accepts a single template parameter for the pointer type 
		being accepted by this delegate signature.
		*/
		/*template <typename ptrType = NULL>*/
		class MulticastDelegateCore {
			public:
				/* Public Class Methods */
				//Is this delegate bound to any functions?
				FINLINE bool bound() const {
					return mcInstances.size() > 0;
				}
				//Empty the delegate list
				void empty() {
					mcInstances.clear();
					mcInstances.compact();
				}

			protected:
				/* Protected Class Methods */
				//Increment the lock counter
				FINLINE void incLocks() const {
					listLockCounter++;
				}
				//Decrement the lock counter
				FINLINE void decLocks() const {
					listLockCounter--;
					if (listLockCounter < 0) {
						listLockCounter = 0;
					}
				}
				//Add a delegate instance
				FINLINE void addDelegateInstance(DelegateInstance *dInst) {
					mcInstances.pushToBack(dInst);
				}
				//Force the cleaning flag to be active
				FINLINE void forceClean() {
					listNeedsCleaning = true;
				}
				//Fetch a read-only instance of the list
				FINLINE const DynArray<DelegateInstance *> &fetchDelegateList() const {
					return mcInstances;
				}
				//Clean the list.
				void performCleaning() {
					if (!listNeedsCleaning || listLockCounter > 0) {
						return;
					}
					for (DelegateInstance *iter = mcInstances.back(); iter != mcInstances.front(); iter--) {
						//Start at the end of the list and clean out any spaces that are NULL.
						if (iter == NULL || iter->canExpireMCDelegates()) {
							mcInstances.erase((U32)i);
						}
						//Compact the array
						mcInstances.compact();
					}
				}

				/* Hidden Constructors */
				//Default Constructor
				FINLINE MulticastDelegateCore() : listNeedsCleaning(false), listLockCounter(0) { }
				 
			private:
				/* Private Class Members */
				//Flag to determine if the list needs cleaning
				bool listNeedsCleaning;
				//DynArray of DelegateInstances attached to this multicast delegate
				DynArray<DelegateInstance *> mcInstances;
				//Lock count, if there is a 'lock' applied to this list, no items may be deleted during a clean cycle
				mutable S32 listLockCounter;
		};

	};

};

#endif //GALACTIC_CORE_MULTICASTDELEGATE_INSTANCE