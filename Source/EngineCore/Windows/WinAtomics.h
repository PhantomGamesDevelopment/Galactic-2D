/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* WinAtomics.h
*
* Defines the PlatformAtomics class for windows platforms
**/

#ifndef GALACTIC_PLATFORM_WINDOWS_PLATFORMATOMICS
#define GALACTIC_PLATFORM_WINDOWS_PLATFORMATOMICS

namespace Galactic {

	namespace Core {

		/*
		PlatformAtomics: Defines atomic locking capabilties for Windows platforms.
		*/
		class PlatformAtomics : public GenericPlatformAtomics {
			public:
				/* Public Class Methods */
				//NOTE! InterlockX64 functions are only available on vista, upwards, so check for those.
				#if WINVER >= 0x0600
					//Add to the interlocked counter
					SFIN S64 increment(volatile S64 *value) {
						return (S64)::InterlockedIncrement64((LONGLONG *)value);
					}

					//Subduct from the interlocked counter
					SFIN S64 decrement(volatile S64 *value) {
						return (S64)::InterlockedDecrement64((LONGLONG *)value);
					}

					//Add a value to the interlocked counter
					SFIN S64 add(volatile S64 *value, S64 amount) {
						return (S64)::InterlockedExchangeAdd64((LONGLONG *)value, (LONGLONG)amount);
					}

					//Exchange a value on the interlocked counter
					SFIN S64 exchange(volatile S64 *value, S64 exchange) {
						return (S64)::InterlockedExchange64((LONGLONG *)value, (LONGLONG)exchange);
					}

					//Compare a value on the interlocked counter and exchange if necessary
					SFIN S64 compareExchange(volatile S64 *dst, S64 exc, S64 comp) {
						return (S64)::InterlockedCompareExchange64((LONGLONG*)dst, (LONGLONG)exc, (LONGLONG)comp);
					}
				#endif

				//Add to the interlocked counter
				SFIN S32 increment(volatile S32 *value) {
					return (S32)::InterlockedIncrement((LPLONG)value);
				}

				//Subduct from the interlocked counter
				SFIN S32 decrement(volatile S32 *value) {
					return (S32)::InterlockedDecrement((LPLONG)value);
				}

				//Add a value to the interlocked counter
				SFIN S32 add(volatile S32 *value, S32 amount) {
					return (S32)::InterlockedExchangeAdd((LPLONG)value, (LONG)amount);
				}

				//Exchange a value on the interlocked counter
				SFIN S32 exchange(volatile S32 *value, S32 exchange) {
					return (S32)::InterlockedExchange((LPLONG)value, (LONG)exchange);
				}

				//Compare a value on the interlocked counter and exchange if necessary
				SFIN S32 compareExchange(volatile S32 *dst, S32 exc, S32 comp) {
					return (S32)::InterlockedCompareExchange((LPLONG)dst, (LONG)exc, (LONG)comp);
				}

				//Perform interlock exchange on a pointer
				SFIN any exchange(any *dst, any exc) {
					#if WINVER >= 0x0600
						return ::InterlockedExchangePointer(dst, exc);
					#else
						return (any)::InterlockedExchange((PLONG)dst, (LONG)exc);
					#endif
				}

				//Perform interlock compare exchange on a pointer
				SFIN any compareExchange(any *dst, any exc, any comp) {
					return ::InterlockedCompareExchangePointer(dst, exc, comp);
				}

				#if GALACTIC_128_BIT_ATOMICS == 1
					//Compare a value on the interlocked counter and exchange if necessary
					SFIN S64 compareExchange(volatile S128 *dst, const S128 &exc, S128 *comp) {
						return ::InterlockedCompareExchange128((volatile S64 *)dst, exc.high, exc.low, (S64 *)comp) == 1;
					}
				#endif
		};

	};

};

#endif //GALACTIC_PLATFORM_WINDOWS_PLATFORMATOMICS