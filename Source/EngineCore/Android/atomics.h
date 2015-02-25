/**
* Galactic 2D
* Source/EngineCore/Android/atomics.h
* Defines the PlatformAtomics class for the engine
* (C) 2014-2015 Phantom Games Development - All Rights Reserved
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

#ifdef GALACTIC_ANDROID

	#ifndef GALACTIC_PLATFORM_ANDROID_PLATFORMATOMICS
	#define GALACTIC_PLATFORM_ANDROID_PLATFORMATOMICS

	namespace Galactic {

		namespace Core {

			/*
			PlatformAtomics: Defines atomic locking capabilties for Android platforms.
			*/
			class PlatformAtomics {
				public:
					/* Public Class Methods */
					//Add to the interlocked counter
					SFIN S64 increment(volatile S64 *value) {
						return __sync_fetch_and_add(value, 1) + 1;
					}

					//Subduct from the interlocked counter
					SFIN S64 decrement(volatile S64 *value) {
						return __sync_fetch_and_sub(value, 1) - 1;
					}

					//Add a value to the interlocked counter
					SFIN S64 add(volatile S64 *value, S64 amount) {
						return __sync_fetch_and_add(value, amount);
					}

					//Exchange a value on the interlocked counter
					SFIN S64 exchange(volatile S64 *value, S64 exchange) {
						return __sync_lock_test_and_set(value, exchange);
					}

					#if GALACTIC_64BIT_SUPPORT == 1
						//Compare a value on the interlocked counter and exchange if necessary
						SFIN S64 compareExchange(volatile S64 *dst, S64 exc, S64 comp) {
							return __sync_val_compare_and_swap(dst, comp, exc);
						}
					#endif

					//Add to the interlocked counter
					SFIN S32 increment(volatile S32 *value) {
						return __sync_fetch_and_add(value, 1) + 1;
					}

					//Subduct from the interlocked counter
					SFIN S32 decrement(volatile S32 *value) {
						return __sync_fetch_and_sub(value, 1) - 1;
					}

					//Add a value to the interlocked counter
					SFIN S32 add(volatile S32 *value, S32 amount) {
						return __sync_fetch_and_add(value, amount);
					}

					//Exchange a value on the interlocked counter
					SFIN S32 exchange(volatile S32 *value, S32 exchange) {
						return __sync_lock_test_and_set(value, exchange);
					}

					//Compare a value on the interlocked counter and exchange if necessary
					SFIN S32 compareExchange(volatile S32 *dst, S32 exc, S32 comp) {
						return __sync_val_compare_and_swap(dst, comp, exc);
					}

					//Perform interlock exchange on a pointer
					SFIN any exchange(any *dst, any exc) {
						return __sync_lock_test_and_set(any, exc);
					}

					//Perform interlock compare exchange on a pointer
					SFIN any compareExchange(any *dst, any exc, any comp) {
						return __sync_val_compare_and_swap(dst, comp, exc);
					}

			};

		};

	};

	#endif //GALACTIC_PLATFORM_ANDROID_PLATFORMATOMICS

#endif //GALACTIC_ANDROID