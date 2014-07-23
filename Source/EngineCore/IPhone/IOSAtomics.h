/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* IOSAtomics.h
*
* Defines the PlatformAtomics class for iphone platforms
*
* References:
* https://mikeash.com/pyblog/friday-qa-2011-03-04-a-tour-of-osatomic.html
**/

#ifndef GALACTIC_PLATFORM_IOS_PLATFORMATOMICS
#define GALACTIC_PLATFORM_IOS_PLATFORMATOMICS

namespace Galactic {

	namespace Core {

		/*
		PlatformAtomics: Defines atomic locking capabilties for IPhone platforms.
		*/
		class PlatformAtomics : public GenericPlatformAtomics {
			public:
				/* Public Class Methods */
				//Add to the interlocked counter
				SFIN S64 increment(volatile S64 *value) {
					return (S64)OSAtomicIncrement64Barrier((S64_t*)value);
				}

				//Subduct from the interlocked counter
				SFIN S64 decrement(volatile S64 *value) {
					return (S64)OSAtomicDecrement64Barrier((S64_t*)value);
				}

				//Add a value to the interlocked counter
				SFIN S64 add(volatile S64 *value, S64 amount) {
					return OSAtomicAdd64Barrier((S64_t)amount, (S64_t*)value) - amount;
				}

				//Exchange a value on the interlocked counter
				SFIN S64 exchange(volatile S64 *value, S64 exchange) {
					S64 result;
					do {
						result = *value;
					} while(!OSAtomicCompareAndSwap64Barrier(result, exchange, (S64_t*)value));
					return result;
				}

				#if GALACTIC_64BIT_SUPPORT == 1
					//Compare a value on the interlocked counter and exchange if necessary
					SFIN S64 compareExchange(volatile S64 *dst, S64 exc, S64 comp) {
						S64 result;
						do {
							if(OSAtomicCompareAndSwap64Barrier(comp, exc, (S64_t*)dst)) {
								return comp;
							}
							result = *dst;
						} while(result == comp);
						return result;
					}
				#endif

				//Add to the interlocked counter
				SFIN S32 increment(volatile S32 *value) {
					return (S32)OSAtomicIncrement32Barrier((S32_t*)value);
				}

				//Subduct from the interlocked counter
				SFIN S32 decrement(volatile S32 *value) {
					return (S32)OSAtomicDecrement32Barrier((S32_t*)value)
				}

				//Add a value to the interlocked counter
				SFIN S32 add(volatile S32 *value, S32 amount) {
					return OSAtomicAdd32Barrier((S32_t)amount, (S32_t*)value) - amount;
				}

				//Exchange a value on the interlocked counter
				SFIN S32 exchange(volatile S32 *value, S32 exchange) {
					S32 result;
					do {
						result = *value;
					} while (!OSAtomicCompareAndSwap32Barrier(result, exchange, (S32_t*)value));
					return result;
				}

				//Compare a value on the interlocked counter and exchange if necessary
				SFIN S32 compareExchange(volatile S32 *dst, S32 exc, S32 comp) {
					S32 result;
					do {
						if (OSAtomicCompareAndSwap32Barrier(comp, exc, (S32_t*)dst)) {
							return comp;
						}
						result = *dst;
					} while (result == comp);
					return result;
				}

				//Perform interlock exchange on a pointer
				SFIN any exchange(any *dst, any exc) {
					any result;
					do {
						result = *dst;
					} while (!OSAtomicCompareAndSwapPtrBarrier(result, exc, dst));
					return result;
				}

				//Perform interlock compare exchange on a pointer
				SFIN any compareExchange(any *dst, any exc, any comp) {
					any result;
					do {
						if (OSAtomicCompareAndSwapPtrBarrier(comp, exc, dst)) {
							return comp;
						}
						result = *dst;
					} while (result == comp);
					return result;
				}

		};

	};

};

#endif //GALACTIC_PLATFORM_IOS_PLATFORMATOMICS