/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* delegateInstance.inl
*
* This inline header file is included once by each instance of delegate declared in delegateTypes.h, this is actually resposible for taking the macro
*  defines of delegateTypes.h, and converting it to a C++ class definition to use as a representation of it.
**/

//First though, ensure that only delegate.h loads this file.
#if !defined(GALACTIC_ONLYINCLUDEFROM_DELEGATECOMBONATIONS_H) || !defined(GALACTIC_INCLUDING_DELEGATETYPES_INL)
	#error "delegateInstance.inl is being loaded by a file that is not delegate.h, breaking"
#endif

//Const Vs. Non-Const
#ifdef DELEGATE_IS_CONST
	#define DELEGATE_CONSTTAG const
#else
	#define DELEGATE_CONSTTAG
#endif

/* First, define the four signatures for our delegates */
//Define the base instance
#define DELEGATE_INSTANCE_CLASS COMBINEAB(DelegateInstance_, DELEGATE_FUNCTION_SUFFIX)
//Define the StrongPointerReference instance
#define DELEGATE_STRONGPOINTER_CLASS COMBINEAB(StrongPointerDelegateInstance_, COMBINEAB(DELEGATE_FUNCTION_ARGUMENTS_SUFFIX, FUNCTION_SUFFIX_CONSTANT))
//Define the C++ Class Method instance
#define DELEGATE_CPP_CLASS_METHOD_CLASS COMBINEAB(CPPClassMethodDelegateInstance_, COMBINEAB(DELEGATE_FUNCTION_ARGUMENTS_SUFFIX, FUNCTION_SUFFIX_CONSTANT))
//Define the C++ Global Method instance
#define DELEGATE_CPP_GLOBAL_METHOD_CLASS COMBINEAB(CPPGlobalMethodDelegateInstance_, COMBINEAB(DELEGATE_FUNCTION_ARGUMENTS_SUFFIX, FUNCTION_SUFFIX_CONSTANT))

namespace Galactic {

	namespace Core {

		//Check if a argument list is being sent
		#if DELEGATE_HAS_ARGS
			//We need to define this list, because 0 param delegates still send to a function, sending a comma to one of these without an argument generates an error
			#define DELEGATE_ARGUMENT_LIST_W_COMMA , DELEGATE_ARGS_LIST
			#define DELEGATE_ARGUMENT_ASSIGN_W_COMMA , DELEGATE_ARGS_ASSIGN
			#define DELEGATE_ARGUMENT_INITLIST_W_COMMA , DELEGATE_ARGS_INITIALIZER
			#define DELEGATE_ARGUMENT_PASSTOFUNC_W_COMMA , DELEGATE_ARGS_PASSTOFUNC
			//Check for parameters
			#if DELEGATE_HAS_PARAMS
				#define DELEGATE_FULL_ASSIGNMENT DELEGATE_PARAM_ASSIGN, DELEGATE_ARGS_ASSIGN
				#define DELEGATE_FULL_VARS DELEGATE_PARAM_LIST, DELEGATE_ARGS_LIST
				#define DELEGATE_FULL_INITIALIZER : DELEGATE_PARAM_INITIALIZER, DELEGATE_ARGS_INITIALIZER
			#else
				#define DELEGATE_FULL_ASSIGNMENT DELEGATE_ARGS_ASSIGN
				#define DELEGATE_FULL_VARS DELEGATE_ARGS_LIST
				#define DELEGATE_FULL_INITIALIZER : DELEGATE_ARGS_INITIALIZER
			#endif
		#else
			#define DELEGATE_ARGUMENT_LIST_W_COMMA
			#define DELEGATE_ARGUMENT_ASSIGN_W_COMMA
			#define DELEGATE_ARGUMENT_INITLIST_W_COMMA
			#define DELEGATE_ARGUMENT_PASSTOFUNC_W_COMMA
			#define DELEGATE_FULL_ASSIGNMENT DELEGATE_PARAM_ASSIGN
			#define DELEGATE_FULL_VARS DELEGATE_PARAM_LIST
			//Check for parameters
			#if DELEGATE_HAS_PARAMS
				#define DELEGATE_FULL_INITIALIZER : DELEGATE_PARAM_INITIALIZER
			#else
				#define DELEGATE_FULL_INITIALIZER
			#endif
		#endif

		//Forward dec. for C++ class method.
		template <class T, DELEGATE_FUNCTION_ARGUMENT_TEMPLATE_TYPENAME> class DELEGATE_CPP_CLASS_METHOD_CLASS;

		/*
		StrongPointer Delegate Instance Class: Methods and operations for delegates overloading via StrongReferencePtr.
		*/
		template <class T, DELEGATE_FUNCTION_ARGUMENT_TEMPLATE_TYPENAME, PointerModes::TSMode m> class DELEGATE_STRONGPOINTER_CLASS
			: public DELEGATE_INSTANCE_CLASS <DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> {
			public:
				/* Typedefs */
				//Type out a call to a function held within the pointer instance of T.
				typedef DelegateReturnType (T::*methodPointer)(DELEGATE_FULL_VARS) DELEGATE_CONSTTAG;

				/* Constructor / Destructor */
				//Default Constructor
				DELEGATE_STRONGPOINTER_CLASS(const StrongReferencePtr<T, m> &c, methodPointer p DELEGATE_ARGUMENT_LIST_W_COMMA) 
					: obj(c), func(p), DELEGATE_ARGUMENT_INITLIST_W_COMMA {
					//Check our method out
					if (func == NULL) {
						GC_Error("Delegate_StrongPointer: NULL method being stored.");
					}
				}

				/* Public Class Methods */
				//Create an instance from a StrongRefPtr
				SFIN DELEGATE_INSTANCE_CLASS <DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> *createInstance(const StrongReferencePtr<T, m> &c, methodPointer p DELEGATE_ARGUMENT_LIST_W_COMMA) {
					return new DELEGATE_STRONGPOINTER_CLASS <T, DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS, m>(c, p DELEGATE_ARGUMENT_ASSIGN_W_COMMA);
				}

				//Create an instance from a class instanced by makeRefPtr
				SFIN DELEGATE_INSTANCE_CLASS <DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> *createInstance(T *trgObj, methodPointer p DELEGATE_ARGUMENT_LIST_W_COMMA) {
					StrongReference<T> objectRef(StaticCastStrongReference<T>(trgObj->becomeStrongRef()));
					return new DELEGATE_STRONGPOINTER_CLASS <T, DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS, m>(objectRef, p DELEGATE_ARGUMENT_ASSIGN_W_COMMA);
				}

				//Internal function: obtain the method pointer, this route is much quicker since we have FINLINE access
				FINLINE cAny getMPInternal() const {
					return *(cAny*)&func;
				}  

				//Internal function: obtain the method pointer, this route is much quicker since we have FINLINE access
				FINLINE cAny getObjInternal() const {
					return obj.toStrongRefPtr().getPointer();
				}

				//Return a pointer to the stored C++ method
				virtual cAny getMethodPointer() const {
					return getMPInternal();
				}

				//Return a pointer to the stored object being referenced
				virtual cAny getObjectPointer() const {
					return getObjInternal();
				}

				//Returns the type of delegate
				virtual DelegateType getDelegateType() const {
					return m == PointerModes::ThreadSafe ? ThreadSafeStrongPointerReference : StrongPointerReference;
				}

				//Check if this delegate has been bound to the same object (class) reference as another
				virtual bool boundToSameObject(cAny trgObj) const {
					return obj.ptrSharesObject(trgObj);
				}

				//Check if the delegate function matches that of another
				virtual bool boundToSameFunc(const DELEGATE_INSTANCE_CLASS<DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> &c) const {
					//Confirm we have a matchable type
					if (c.getDelegateType() == ThreadSafeStrongPointerReference || c.getDelegateType() == StrongPointerReference
						|| c.getDelegateType() == CPPMemberMethod) {
						//Now check if the function is bound to one of the above listed, also check the object to affirm it's the same class instance.
						return getMPInternal() == c.getMethodPointer() && obj.ptrSharesObject(c.getObjectPointer());
					}
					return false;
				}

				//Create a copy of this delegate instance.
				virtual DELEGATE_INSTANCE_CLASS<DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> *createCopy() {
					return createInstance(obj.toStrongRefPtr(), func DELEGATE_ARGUMENT_PASSTOFUNC_W_COMMA);
				}

				//Can we safely execute?
				virtual bool canExecute() const {
					return obj.valid();
				}

				//Execute the delegate
				virtual DelegateReturnType exec(DELEGATE_PARAM_LIST) const {
					StrongReferencePtr<T, m> trgObj(obj.toStrongRefPtr());
					if (!trgObj.valid()) {
						GC_CError("Delegate_StrongPointer::exec(): Pointer reference is no longer valid.");
						//To-Do: Insert an assert here, because we cannot directly determine DelegateReturnType
					}
					//Next, we need to remove any constant references from the class, so we can safely adjust members inside of it
					typedef typename remove_const<T>::retType nonConstType;
					nonConstType *object = const_cast<nonConstType *>(trgObj.getPointer());
					//Lastly, call the function itself
					if (func == NULL) {
						//ToDo: Assert here, function doesn't exist.
						GC_CError("Delegate_StrongPointer::exec(): Targeted object method is invalid, or does not exist.");
					}
					return (object->*func)(DELEGATE_FULL_ASSIGNMENT);
				}

				#if DELEGATE_FUNCTION_IS_VOID
					//Execute the delegate if it is possible to do so
					virtual bool execIfPoss(DELEGATE_PARAM_LIST) const {
						StrongReferencePtr<T, m> trgObj(obj.toStrongRefPtr());
						if (trgObj.valid()) {
							exec(DELEGATE_PARAM_ASSIGN);
							return true;
						}
						return false;
					}
				#endif

			private:
				/* Private Class Members */
				//Weak Reference to object
				WeakReferencePtr<T, m> obj;
				//The targeted method to execute
				methodPointer func;

				//Argument definitions (if any)
				DELEGATE_ARGUMENTS

				/* Define as friend to alternate typedefs */
				// Grant friend access to all other instances of DELEGATE_STRONGPOINTER_CLASS so they may test against our object pointer
				template <class altT, DELEGATE_FUNCTION_ARGUMENT_ALTERNATE_TEMPLATE_DEC, PointerModes::TSMode altM> friend class DELEGATE_STRONGPOINTER_CLASS;
				// Grant friend access to instances of DELEGATE_CPP_CLASS_METHOD_CLASS so they may test against our object pointer
				template <class altT, DELEGATE_FUNCTION_ARGUMENT_ALTERNATE_TEMPLATE_DEC> friend class DELEGATE_CPP_CLASS_METHOD_CLASS;
		};

		/*
		CPP Class Method Delegate Instance Class: Methods and operations for delegates overloading via C++ class methods.
		*/
		template <class T, DELEGATE_FUNCTION_ARGUMENT_TEMPLATE_TYPENAME> class DELEGATE_CPP_CLASS_METHOD_CLASS
			: public DELEGATE_INSTANCE_CLASS <DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> {
			public:
				/* Typedefs */
				//Type out a call to a function held within the pointer instance of T.
				typedef DelegateReturnType (T::*methodPointer)(DELEGATE_FULL_VARS) DELEGATE_CONSTTAG;

				/* Constructor / Destructor */
				//Default Constructor
				DELEGATE_CPP_CLASS_METHOD_CLASS(T *c, methodPointer p DELEGATE_ARGUMENT_LIST_W_COMMA)
					: obj(c), func(p) DELEGATE_ARGUMENT_INITLIST_W_COMMA {
					//Check our method out
					if (obj == NULL || func == NULL) {
						GC_Error("Delegate_CPPMethod: Cannot init a delegate on a invalid class or method instance.");
					}
				}

				/* Public Class Methods */
				//Create an instance from a class pointer
				SFIN DELEGATE_INSTANCE_CLASS <DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> *createInstance(T *trgObj, methodPointer p DELEGATE_ARGUMENT_LIST_W_COMMA) {
					return new DELEGATE_CPP_CLASS_METHOD_CLASS <T, DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS>(trgObj, p DELEGATE_ARGUMENT_ASSIGN_W_COMMA);
				}

				//Internal function: obtain the method pointer, this route is much quicker since we have FINLINE access
				FINLINE cAny getMPInternal() const {
					return *(cAny*)&func;
				}

				//Internal function: obtain the method pointer, this route is much quicker since we have FINLINE access
				FINLINE cAny getObjInternal() const {
					return obj;
				}
				
				//Return a pointer to the stored C++ method
				virtual cAny getMethodPointer() const {
					return getMPInternal();
				}

				//Return a pointer to the stored object being referenced
				virtual cAny getObjectPointer() const {
					return getObjInternal();
				}

				//Returns the type of delegate
				virtual DelegateType getDelegateType() const {
					return CPPMemberMethod;
				}

				//Check if this delegate has been bound to the same object (class) reference as another
				virtual bool boundToSameObject(cAny trgObj) const {
					return FBOOL(obj == trgObj);
				}

				//Check if the delegate function matches that of another
				virtual bool boundToSameFunc(const DELEGATE_INSTANCE_CLASS<DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> &c) const {
					//Confirm we have a matchable type
					if (c.getDelegateType() == CPPMemberMethod || c.getDelegateType() == ThreadSafeStrongPointerReference || c.getDelegateType() == StrongPointerReference) {
						//Now check if the function is bound to one of the above listed, also check the object to affirm it's the same class instance.
						return getMPInternal() == c.getMethodPointer() && (obj == c.getObjectPointer());
					}
					return false;
				}

				//Create a copy of this delegate instance.
				virtual DELEGATE_INSTANCE_CLASS<DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> *createCopy() {
					return createInstance(obj, func DELEGATE_ARGUMENT_ASSIGN_W_COMMA);
				}

				//Can we safely execute?
				virtual bool canExecute() const {
					//ToDo: This isn't 100% safe, as we can't deduce wether or not the pointer may be safely dereferenced, without breaking the code here anyways.
					// Leaving this as a todo in the event support is added in C++11/C++14.
					return true;
				}

				//Execute the delegate
				virtual DelegateReturnType exec(DELEGATE_PARAM_LIST) const {
					//First, we need to remove any constant references from the class, so we can safely adjust members inside of it
					typedef typename remove_const<T>::retType nonConstType;
					nonConstType *object = const_cast<nonConstType *>(obj);
					//Lastly, call the function itself
					if (func == NULL) {
						//ToDo: Assert here, function doesn't exist.
						GC_CError("Delegate_CPPClassMethod::exec(): Targeted object method is invalid, or does not exist.");
					}
					return (object->*func)(DELEGATE_FULL_ASSIGNMENT);
				}

				#if DELEGATE_FUNCTION_IS_VOID
					//Execute the delegate if it is possible to do so
					virtual bool execIfPoss(DELEGATE_PARAM_LIST) const {
						//See ToDo note in canExecute() for deduction on safety...
						exec(DELEGATE_PARAM_ASSIGN);
						return true;
					}
				#endif

			private:
				/* Private Class Members */
				//The Class we're referencing
				T *obj;
				//The targeted method to execute
				methodPointer func;

				//Argument definitions (if any)
				DELEGATE_ARGUMENTS

				/* Define as friend to alternate typedefs */
				// Grant friend access to instances of DELEGATE_STRONGPOINTER_CLASS so they may test against our object pointer
				template <class altT, DELEGATE_FUNCTION_ARGUMENT_ALTERNATE_TEMPLATE_DEC, PointerModes::TSMode altM> friend class DELEGATE_STRONGPOINTER_CLASS;
				// Grant friend access to all other instances of DELEGATE_CPP_CLASS_METHOD_CLASS so they may test against our object pointer
				template <class altT, DELEGATE_FUNCTION_ARGUMENT_ALTERNATE_TEMPLATE_DEC> friend class DELEGATE_CPP_CLASS_METHOD_CLASS;
		};

		/*
		CPP Global Method Delegate Instance Class: Methods and operations for delegates overloading via C++ global methods.
		*/
		template <DELEGATE_FUNCTION_ARGUMENT_TEMPLATE_TYPENAME> class DELEGATE_CPP_GLOBAL_METHOD_CLASS
			: public DELEGATE_INSTANCE_CLASS <DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> {
			public:
				/* Typedefs */
				//Type out a call to a global function.
				typedef DelegateReturnType (*methodPointer)(DELEGATE_FULL_VARS);

				/* Constructor / Destructor */
				//Default Constructor
				DELEGATE_CPP_GLOBAL_METHOD_CLASS(methodPointer p DELEGATE_ARGUMENT_LIST_W_COMMA)
					: func(p) DELEGATE_ARGUMENT_INITLIST_W_COMMA {
					//Check our method out
					if (func == NULL) {
						GC_Error("Delegate_CPPGlobalMethod: Cannot init a delegate on an invalid method instance.");
					}
				}

				/* Public Class Methods */
				//Create an instance from a class pointer
				SFIN DELEGATE_INSTANCE_CLASS <DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> *createInstance(methodPointer p DELEGATE_ARGUMENT_LIST_W_COMMA) {
					return new DELEGATE_CPP_GLOBAL_METHOD_CLASS <DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS>(p DELEGATE_ARGUMENT_ASSIGN_W_COMMA);
				}

				//Internal function: obtain the method pointer, this route is much quicker since we have FINLINE access
				FINLINE cAny getMPInternal() const {
					return *(cAny*)&func;
				}

				//Return a pointer to the stored C++ method
				virtual cAny getMethodPointer() const {
					return getMPInternal();
				}

				//Return a pointer to the stored object being referenced
				virtual cAny getObjectPointer() const {
					return NULL;
				}

				//Returns the type of delegate
				virtual DelegateType getDelegateType() const {
					return CPPMethod;
				}

				//Check if this delegate has been bound to the same object (class) reference as another
				virtual bool boundToSameObject(cAny trgObj) const {
					//Global methods don't have objects, hence, false.
					return false;
				}

				//Check if the delegate function matches that of another
				virtual bool boundToSameFunc(const DELEGATE_INSTANCE_CLASS<DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> &c) const {
					//Confirm we have a matchable type
					if (c.getDelegateType() == CPPMemberMethod) {
						//Compare to the same method
						const DELEGATE_CPP_GLOBAL_METHOD_CLASS <DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> &other =
							static_cast<const DELEGATE_CPP_GLOBAL_METHOD_CLASS <DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> &>(c);
						if (func == c.getMethodPointer()) {
							return true;
						}
					}
					return false;
				}

				//Create a copy of this delegate instance.
				virtual DELEGATE_INSTANCE_CLASS<DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> *createCopy() {
					return createInstance(func DELEGATE_ARGUMENT_PASSTOFUNC_W_COMMA);
				}

				//Can we safely execute?
				virtual bool canExecute() const {
					//Global methods are always 100% safe to execute, so go ahead!! :)
					return true;
				}

				//Execute the delegate
				virtual DelegateReturnType exec(DELEGATE_PARAM_LIST) const {
					if (func == NULL) {
						//ToDo: Assert here, function doesn't exist.
						GC_CError("Delegate_CPPGlobalMethod::exec(): No such function exists.");
					}
					return func(DELEGATE_FULL_ASSIGNMENT);
				}

				#if DELEGATE_FUNCTION_IS_VOID
					//Execute the delegate if it is possible to do so
					virtual bool execIfPoss(DELEGATE_PARAM_LIST) const {
						exec(DELEGATE_PARAM_ASSIGN);
						return true;
					}
				#endif

			private:
				/* Private Class Members */
				//The targeted method to execute
				methodPointer func;

				//Argument definitions (if any)
				DELEGATE_ARGUMENTS
		};

	};

};

/* Lastly, Undef everything important */
#undef DELEGATE_INSTANCE_CLASS
#undef DELEGATE_STRONGPOINTER_CLASS
#undef DELEGATE_CPP_CLASS_METHOD_CLASS
#undef DELEGATE_CPP_GLOBAL_METHOD_CLASS

#undef DELEGATE_CONSTTAG 
#undef DELEGATE_FUNCTION_CONST_OR_NOSUFFIX
#undef DELEGATE_FULL_ASSIGNMENT
#undef DELEGATE_FULL_VARS
#undef DELEGATE_FULL_INITIALIZER
#undef DELEGATE_ARGUMENT_LIST_W_COMMA
#undef DELEGATE_ARGUMENT_ASSIGN_W_COMMA
#undef DELEGATE_ARGUMENT_INITLIST_W_COMMA
#undef DELEGATE_ARGUMENT_PASSTOFUNC_W_COMMA