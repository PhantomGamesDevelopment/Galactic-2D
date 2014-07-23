/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* advTools.h
*
* Defines some advanced C++ tools.
**/

#ifndef GALACTIC_INTERNAL_ADVTOOLS
#define GALACTIC_INTERNAL_ADVTOOLS

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/* 
		   Memory Trickery Functions 
		   These are awesome in all ways, allows you to create and kill stuff without needing to use stuff like
		   malloc, calloc, and delete, over, and over, and over, these are also shortcuts used by DynArray in quite
		   a few places. We're referencing <new.h> in this file to allow for easier variants of memory copy functions
		   by means of using new in template style constructors.
		*/

		//killRef() - Delete a reference.
		template <class T> inline void killRef(T* p) {
			p->~T();
		}

		//createRef() - Create a pointer.
		template <class T> inline T* createRef(T* p) {
			return new ( p ) T;
		}

		//createRef() - Create a pointer by copying the information from an existing reference.
		template <class T> inline T* createRef(T* p, const T* copy) {
			return new ( p ) T( *copy );
		}

		/*
		Advanced Tools: These are tools that can be used to compact advanced operations into a single function line. These are
		 mainly used in the internal systems of the engine, however, you are more than welcome to use them for any application
		 that your task requires.
		*/ 

		/*
		remove_const(): A quick little type trickery method that can be used to remove a const flag from just about anything without needing prior
		knowledge of an object being in existence.

		Ref: http://www.boost.org/doc/libs/1_35_0/libs/type_traits/doc/html/boost_typetraits/reference/remove_const.html
		*/
		//remove_const(): Works on the premesis of Boost::remove_const, you can send in a const member and typedef out a non-const without knowing about the member
		template <class T> struct remove_const {
			typedef T retType;
		};
		//remove_const(): Works on the premesis of Boost::remove_const, you can send in a const member and typedef out a non-const without knowing about the member
		template <class T> struct remove_const <const T> {
			typedef T retType;
		};

		//alignVal(): Align a value to the next higher multiple of the specified value
		template <class T> inline T alignVal(const T ptrTrg, S32 val) {
			return (T)(((IntPointer)ptrTrg + val - 1) & ~(val - 1));
		}

		//swapPtrs(): Swap two pointer values.
		template <class T> inline void swapPtrs(T& r1, T& r2) {
			const T tmpStor = r1;
			r1 = r2;
			r2 = tmpStor;
		}

		//arrayCounter: This is a extremely useful class that can cast array values to a char and then count the elements.
		template <typename T, U32 elements> C8(&arrayCounter(const T(&)[elements]))[elements];
		//getArrayCount(): fetch the number of elements in the targeted array
		#define getArrayCount(trg) sizeof(arrayCounter(trg))

	};

};

#endif //GALACTIC_INTERNAL_ADVTOOLS