/**
* Galactic 2D
* Source/EngineCore/Containers/conditionalBlock.h
* Allows conditionals in function declaration blocks, mainly used in platform check functioning
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

#ifndef GALACTIC_INTERNAL_CONDITIONALBLOCK
#define GALACTIC_INTERNAL_CONDITIONALBLOCK

namespace Galactic {

	namespace Core {

		/*
		conditionalBlock: A block of code to be executed in the event that the test condition is met. 

		For Example:
		template <typename T> typename conditionalBlock<Something<T>::value, returnType>::Type Function(const T& ref) {
		.
		.
		.
		}

		If the condition is met, then typename x::Type will be initialized, if not, it will not and the function will not be included
		 in compilation.
		*/
		template <bool test, typename result = void> class conditionalBlock;

		/*
		conditionalBlock: executed in the event the condition is met, allows definition of result Type.
		*/
		template <typename result> class conditionalBlock<true, result> {
			public:
				typedef result Type;
		};

		/*
		conditionalBlock: executed in the event the condition is not met, no definitions.
		*/
		template <typename result> class conditionalBlock<false, result> {
			public:
				//typedef result Type;
		};

	};

};

#endif