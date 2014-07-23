/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* delegateInterface.inl
*
* This inline header file is included once by each instance of delegate declared in delegateTypes.h. This file declares the overloads of delegateInstace
*  by each of the delegate types declared in delegateTypes.h
*
**/

//First though, ensure that only delegate.h loads this file.
#if !defined(GALACTIC_ONLYINCLUDEFROM_DELEGATECOMBONATIONS_H) || !defined(GALACTIC_INCLUDING_DELEGATETYPES_INL)
	#error "delegateInterface.inl is being loaded by a file that is not delegate.h, breaking"
#endif

namespace Galactic {

	namespace Core {

		#define DELEGATE_INSTANCE_CLASS COMBINEAB(DelegateInstance_, DELEGATE_FUNCTION_SUFFIX)
		#if DELEGATE_HAS_PARAMS
			#define DELEGATE_FULL_INITIALIZER : DELEGATE_PARAM_INITIALIZER
		#else
			#define DELEGATE_FULL_INITIALIZER
		#endif

		/*
		DelegateInstace_X: Individual templated version of the delegate instance object, stores information and fires events
		*/
		template <DELEGATE_FUNCTION_TYPENAME_TEMPLATE_DEC> class DELEGATE_INSTANCE_CLASS : public DelegateInstance {
			private:
				/* Private Class Methods (First here for advanced definition) */
				/*
				DelegateParameters: A basic internal struct for converting parameter formats to C++
				*/
				struct DelegateParameters {
					public:
						/* Constructor / Destructor */
						//Default Constructor
						DelegateParameters(DELEGATE_PARAM_LIST) DELEGATE_FULL_INITIALIZER { }

						/* Struct Members */
						/* Delegate Parameters & Values */
						DELEGATE_PARAMETERS
						#if !DELEGATE_FUNCTION_IS_VOID
							//The value returned
							DelegateReturnType ret;
						#endif
				};

			public:
				/* Public Class Methods */
				//Execute the delegate, return an error if one occured
				virtual DelegateReturnType exec(DELEGATE_PARAM_LIST) const = 0;
				//Execute the delegate given virtual parameters (IE: From C++)
				virtual DelegateReturnType execWParams(any params) const {
					DelegateParameters &parameters = *((DelegateParameters*)params);
					return exec(DELEGATE_PARAMETERS_PASSTOFUNC);
				} 
				#if DELEGATE_FUNCTION_IS_VOID
					//Execute the delegate if it's possible to do so
					virtual bool execIfPoss(DELEGATE_PARAM_LIST) const = 0;
				#endif
				//Create a copy of this delegate instance.
				virtual DELEGATE_INSTANCE_CLASS<DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> *createCopy() = 0;
				//Check if the delegate function matches that of another
				virtual bool boundToSameFunc(const DELEGATE_INSTANCE_CLASS<DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS> &c) const = 0;
		};

		//Undef the defines we created here
		#undef DELEGATE_FULL_INITIALIZER
		#undef DELEGATE_INSTANCE_CLASS

	};

};