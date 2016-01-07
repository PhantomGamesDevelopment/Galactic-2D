/**
* Galactic 2D
* Source/EngineCore/Memory/engineMemory.h
* Defines wrappers to platform specific memory functioning to be used as a global call source
* (C) 2014-2016 Phantom Games Development - All Rights Reserved
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

#ifndef GALACTIC_CORE_MEMORY_EMEM
#define GALACTIC_CORE_MEMORY_EMEM

namespace Galactic {

	namespace Core {

		//GLOBALALLOCCHECK(): Shortcut macro for repetitive function logic in the below methods, this will create the global allocator (if it's not there) and validate
		// that the creation was successful. To-Do: We need to replace the CError clause with an assert when that capability is installed.
		#define GLOBALALLOCCHECK(functionName) \
				if (!_GAllocater) { \
					createAllocater(); \
					if (!_GAllocater) {\
						String err = String::ToStr("Memory::%s(): Unable to perform %s(), cannot initalize global allocater module.", functionName, functionName); \
						GC_CError(err.c_str()); \
					} \
				} \

		/* Size definition enumerations */
		enum {
			//MEMORY_DEFAULTALIGN: If defined, then all memory allocation will try to align
			// to engine standards (blocks >=16bytes will convert to 16 and blocks <16bytes
			// will convert to 8 blocks)
			MEMORY_DEFEAULTALIGN = 0,
			//MEMORY_MINALIGN: The minimum alignment permitted by the engine
			MEMORY_MINALIGN = 8,
		};

		/*
		Memory: The engine's core memory call-pass class, this class shortcut defines routes
		 to the platform memory operations.
		*/
		class Memory {
			public:
				/* Public Class Methods */

				/* Standard C++ Memory Operations */
				//Perform a platform specific memcmp operation
				SFIN S32 Memcmp(cAny m1, cAny m2, SIZE_T count);
				//Perform a platform specific memcpy operation
				SFIN any Memcpy(any dst, cAny src, SIZE_T count);
				//Perform a platform specific memmove operation
				SFIN any Memmove(any dst, cAny src, SIZE_T count);
				//Perform a platform specific memset operation
				SFIN any Memset(any dst, U8 value, SIZE_T count);
				//Perform a platform specific memswap operation
				SFIN void Memswap(any m1, any m2, SIZE_T count);

				/* Standard C memory allocation calls */
				//Perform a malloc operation
				SFIN any C_malloc(SIZE_T size);
				//Perform a free operation
				SFIN void C_free(any ptr);

				/* Additional C-Style calls */
				//Engine dervied malloc function
				static any Malloc(SIZE_T size, U32 alignment = MEMORY_DEFEAULTALIGN);
				//Engine derived realloc function
				static any Realloc(any ptr, SIZE_T size, U32 alignment = MEMORY_DEFEAULTALIGN);
				//Engine derived free function
				static void Free(any ptr);

				/* Derived Tools */
				//Fetch the size that "should" be used for the requested allocation under engine alignment rules.
				static SIZE_T fetchRealSize(SIZE_T requested, U32 alignment = MEMORY_DEFEAULTALIGN);
				//Fetch the block allocation size for this specific pointer
				static SIZE_T fetchBlockSize(any ptr);
				//Zero a specific block of memory, used to "clear" pointers, essentially the same as doing Memset(dst, NULL, count)
				static any zeroBlock(any dst, SIZE_T count);
				//Alternate version of memcpy that is optimized for large blocks.
				SFIN any Memcpy_block(any dst, cAny src, SIZE_T count);
				//Alternate version of memcpy that streams copy commands to avoid L2 cache pollution by means of overloading with large blocks
				SFIN any Memcpy_streamed(any dst, cAny src, SIZE_T count);
		};

	};

};

#endif //GALACTIC_CORE_MEMORY_EMEM