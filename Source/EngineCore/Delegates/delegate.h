/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* delegate.h
*
* Main header file for the Galactic Engine Delegate System. This file serves to define some key parameters and methods that may be used
* throughout the engine to define delegates of varying types
*
* This system is based off of the FastDelegate.h design by Don Clugston (http://www.codeproject.com/cpp/FastDelegate.asp), with some significant levels
*  of improvements to remove ASM dependancies as well as create a simple program to declare as many levels of parameters & arguments we need for our
*  delegates.
**/

/* This file is special, in a sense, we only want this file to be included from one other file in the engine, hence we use a secondary guard */
#ifndef GALACTIC_ONLYINCLUDEFROM_DELEGATECOMBONATIONS_H
#define GALACTIC_ONLYINCLUDEFROM_DELEGATECOMBONATIONS_H

	#ifndef GALACTIC_ENGINECORE_DELEGATE
	#define GALACTIC_ENGINECORE_DELEGATE

	#include "../Tools/reference.h"
	#include "delegateInstance.h"
	#include "delegateCore.h"
	#include "multicastDelegateCore.h"

	/**
	* Internal Documentation for Delegate System
	*  Use this as your quick guide to the Galactic Delegate System
	*
	* What Is It?
	*  A delegate is a system that allows you to in a type-safe manner, call C++ member functions. These systems can be arbitrarily attached
	*   to dynamic sources allowing for numerous systems to be implemented. This system is behind many of the internal functioning systems
	*   of uttermost engine importance, such as timers, events, and most importantly, method callbacks.
	*
	* Supported Features
	*  Delegates may currently have the following:
	*   * Delegate Functions returning a value
	*   * Delegate Functions with 12 Parameters
	*   * Delegate Functions with 8 Arguments
	*   * Multi-Casting Delegates, which can attach to multiple functions and execute with a broadcast() command, No Return Types for MC Delegates
	*
	* How To Use
	*  Here are the macros to declare delegates:
	*
	*   GALACTIC_INIT_SC_DELEGATE...():   Single Cast Delegate
	*   GALACTIC_INIT_MC_DELEGATE...():   Multi-Cast Delegate
	*
	* So for example, if I want a singlecast delegate with a return type, two params, and one argument, I would use the following:
	*   GALACTIC_INIT_SC_DELEGATE_ReturnType_TwoParams_OneArg(MyDelegate, ReturnType, Param1, Param2, Arg1);
	* Delegates may also be bound to constant methods by using:
	*   GALACTIC_INIT_SC_DELEGATE_ReturnType_TwoParams_OneArg_constant(MyDelegate, ReturnType, Param1, Param2, Arg1);
	**/

	//Declaration functions
	//Declare Single-Cast Delegate
	#define DELEGATE_DECLARE(dName, dSuffix, ...) typedef BaseDelegateCore_##dSuffix<__VA_ARGS__> dName
	//Declare Multi-Cast Delegate
	#define DELEGATE_DECLARE_MULTICAST(dName, dSuffix, ...) typedef MulticastDelegateCoreInstance_##dSuffix<__VA_ARGS__> dName

	//Useful Macro Definitions 
	//Concatinate Arguments
	#define CONCATARG(...) __VA_ARGS__
	//Actual combine for A&B
	#define DOCOMBINE_AB(A, B) A##B
	//Combine A & B
	#define COMBINEAB(A, B) DOCOMBINE_AB(A, B)
	//This define is used to ensure that delegateTypes.inl is only included from here.
	#define GALACTIC_INCLUDING_DELEGATETYPES_INL
	#include "delegateTypes.h"

	//Undef the above.
	#undef GALACTIC_INCLUDING_DELEGATETYPES_INL
	#undef CONCATARG
	#undef DOCOMBINE_AB
	#undef COMBINEAB

	//Declare some basic delegates
	namespace Galactic {

		namespace Core {

			//Declare the basic single-cast delegate for the engine.
			GALACTIC_INIT_SC_DELEGATE(BasicDelegate);
			//Declare the basic multi-cast delegate for the engine.
			GALACTIC_INIT_MC_DELEGATE(BasicMulticastDelegate);

		};

	};

	#endif //GALACTIC_ENGINECORE_DELEGATE

#endif //GALACTIC_ONLYINCLUDEFROM_DELEGATECOMBONATIONS_H