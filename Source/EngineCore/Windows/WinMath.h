/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* WinMath.h
*
* Defines the PlatformMath class for windows platforms
**/

#ifdef GALACTIC_WINDOWS	

	#ifndef GALACTIC_PLATFORM_WINDOWS_PLATFORMMATH
	#define GALACTIC_PLATFORM_WINDOWS_PLATFORMMATH

	namespace Galactic {

		namespace Core {

			/*
			PlatformMath: Wrapper functions and methods to convert Windows Math functions into a standardized list that the engine may use.
			*/
			class PlatformMath : public GenericPlatformMath { 
				public:
					/* Public Class Methods */

					//Most of the MSVN functions referenced in PlatformMath on windows relies on compilation from MSVS, therefore we cannot be using LLVM/GCC here.
					// These are MSVS intristic functions (More Info: http://msdn.microsoft.com/en-us/library/26td21ds.aspx)
					#if !GALACTIC_USING_LLVM
						/* Basic Mathematical Operations */
						//Truncate a F32 to an integer with a preference towards zero.
						SFIN S32 TruncateToInteger(F32 value);
						//Apply the floor operation to a F32, then convert it to an S32.
						SFIN S32 FloorDownToInt(F32 value);
						//Directly floor the F32
						SFIN F32 Floor(F32 value);
						//Apply the ceil operation to a F32, then convert it to an S32.
						SFIN S32 CeilUpToInt(F32 value);
						//Directly ceil the F32
						SFIN F32 Ceil(F32 value);
						//Round F32 to S32
						SFIN S32 RoundToInt(F32 value);
						//Round F32 to F32
						SFIN F32 RoundToF32(F32 value);

						/* Mathematical Library Checks (For F32) */
						//Is the number finite?
						SFIN bool mIsFinite(F32 value);
						//Is this number NaN by the definition of F32?
						SFIN bool mIsNaN(F32 value);
					#endif
			};

		};

	};

	#endif //GALACTIC_PLATFORM_WINDOWS_PLATFORMMATH

#endif //GALACTIC_WINDOWS