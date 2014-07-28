/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* mSingleton.h
*
* Defines a class similar to the functioning of boost::singleton for managing important instanced classes
*
* NOTE: You should create a static UTF16 getInstanceName() method for each of your classes that use the managedSingleton
*  definition for purposes of organization and access by name in some cases.
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