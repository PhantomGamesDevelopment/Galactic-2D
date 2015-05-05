/**
* Galactic 2D
* Source/EngineCore/Tools/guid.h
* Defines a platform independant wrapper for "Globally Unique IDs" (GUIDs) that can be used throughout the engine
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

#ifndef GALACTIC_INTERNAL_GUIDS
#define GALACTIC_INTERNAL_GUIDS

namespace Galactic {

	namespace Core {

		/*
		guidFormatTypes: Enumerations of available formatting types for GUIDs
		*/
		enum guidFormatTypes {
			//NumericalString: All 32 digits printed in a single string with no separations
			// EX: ################################
			NumericalString,
			//HyphenatedBlock: Five block GUID string separated with hyphens
			// EX: ########-####-####-####-############
			HyphenatedBlock,
			//OSHexBlock: Standard OS-Style GUID with hexadecimal values in braces
			// EX: {0x########, 0x####, 0x####, {0x##, 0x##, 0x##, 0x##, 0x##, 0x##, 0x##, 0x##}}
			OSHexBlock,
		};

		/*
		galacticGUID: Engine's GUID class. Handles storage and manipulation of GUIDs. Generation is handled by the platform.
		 Named the class this way to prevent interference with OS's defining their own GUID class as 'GUID'
		*/
		class galacticGUID {
			public:
				/* Public Class Methods */

				/* Public Class Members */
				//First component
				U32 A;
				//Second component
				U32 B;
				//Third component
				U32 C;
				//Fourth component
				U32 D;
		};

	};

};

#endif //GALACTIC_INTERNAL_GUIDS