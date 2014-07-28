/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* threadTasks.cpp
*
* Defines classes and operations to wire together the threading classes defined in threadBase.h & singleThreadBase.h
**/

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		TSCounter Class Definitions
		*/
		#if (!defined(GALACTIC_WINDOWS) || WINVER >= 0x0600)

			TSCounter::TSCounter(S64 initialValue) {
				tsCounter = initialValue;
			}

			TSCounter::TSCounter(const TSCounter &c) {
				//Note! This method is not 100% "thread-safe" because if the counter being copied is currently being used, then the value cannot be guarenteed.
				// ToDo? Consider some kind of mutex lock on the counter in question until the copy is complete.
				tsCounter = c.tsCounter;
			}

			S64 TSCounter::fetch() const {
				return tsCounter;
			}

			S32 TSCounter::toS32() const {
				//This type-cast "should" be safe, since we're downcasting.
				return (S32)tsCounter;
			}

			S64 TSCounter::inc() {
				return PlatformAtomics::increment(&tsCounter);
			}

			S64 TSCounter::dec() {
				return PlatformAtomics::decrement(&tsCounter);
			}

			S64 TSCounter::add(S64 amount) {
				return PlatformAtomics::add(&tsCounter, amount);
			}

			S64 TSCounter::sub(S64 amount) {
				return PlatformAtomics::add(&tsCounter, -(amount));
			}

			S64 TSCounter::set(S64 value) {
				return PlatformAtomics::exchange(&tsCounter, value);
			}

			S64 TSCounter::operator++() {
				return inc();
			}

			S64 TSCounter::operator--() {
				return dec();
			}

			S64 TSCounter::operator+=(S64 amount) {
				return add(amount);
			}

			S64 TSCounter::operator-=(S64 amount) {
				return sub(amount);
			}

			S64 TSCounter::operator=(S64 value) {
				return set(value);
			}

		#else

			TSCounter::TSCounter(S32 initialValue) {
				tsCounter = initialValue;
			}

			TSCounter::TSCounter(const TSCounter &c) {
				//Note! This method is not 100% "thread-safe" because if the counter being copied is currently being used, then the value cannot be guarenteed.
				// ToDo? Consider some kind of mutex lock on the counter in question until the copy is complete.
				tsCounter = c.tsCounter;
			}

			S32 TSCounter::fetch() const {
				return tsCounter;
			}

			S32 TSCounter::toS32() const {
				//We're on a windows platform below vista, hence there is no actual convert-to-S32 function, since, we're already S32, push a warn()
				GC_Warn("TSCounter::toS32(): This version of windows does not support 64-bit thread-safe counters, you may safely use fetch() to obtain the requested value.");
				return fetch();
			}

			S32 TSCounter::inc() {
				return PlatformAtomics::increment(&tsCounter);
			}

			S32 TSCounter::dec() {
				return PlatformAtomics::decrement(&tsCounter);
			}

			S32 TSCounter::add(S32 amount) {
				return PlatformAtomics::add(&tsCounter, amount);
			}

			S32 TSCounter::sub(S32 amount) {
				return PlatformAtomics::add(&tsCounter, -(amount));
			}

			S32 TSCounter::set(S32 value) {
				return PlatformAtomics::exchange(&tsCounter, value);
			}

			S32 TSCounter::operator++() {
				return inc();
			}

			S32 TSCounter::operator--() {
				return dec();
			}

			S32 TSCounter::operator+=(S32 amount) {
				return add(amount);
			}

			S32 TSCounter::operator-=(S32 amount) {
				return sub(amount);
			}

			S32 TSCounter::operator=(S32 value) {
				return set(value);
			}

		#endif

	};

};