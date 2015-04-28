/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/cursor.h
* Defines a standard function set for working with the mouse instance
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

#ifndef GALACTIC_PLATFORM_GENERIC_CURSORDEC
#define GALACTIC_PLATFORM_GENERIC_CURSORDEC

namespace Galactic {

	namespace Core {

		/*
		CursorType: Defines a list of cursor types that could be active at the specified moment
		*/
		enum CursorType {
			//Default: Standard mouse cursor
			Default,
			//TextEdit: Cursor when highlighting a region of text that may be edited
			TextEdit,
			//ResizeHrz: Horizontal resize cursor
			ResizeHrz,
			//ResizeVrt: Vertical resize cursor
			ResizeVrt,
			//ResizeDglSE: Diagonal resize cursor (SE orientation)
			ResizeDglSE,
			//ResizeDglSW: Diagonal resize cursor (SW orientation)
			ResizeDglSW,
			//HandGrabable: Hand cursor to indicate a grabable item
			HandGrabable,
			//HandGrabing: Hand cursor to indicate grabbing this item
			HandGrabing,
			//ClosedHand: Hand cursor to indicate currently moving grabed item
			ClosedHand,
			//Invalid: Red circle with a slash through it
			Invalid,
			//Invisible: Set for no active cursor
			Invisible,
			//Total: Numerical value containing the number of selectable options
			Total,
		};

		/* 
		GenericCursor: Standard definition of the platform independant mouse cursor class
		*/
		class GenericCursor {
			public:
				/* Public Class Methods */
				//Make the cursor visible
				virtual void show() = 0;
				//Make the cursor invisible
				virtual void hide() = 0;
				//Set the type of cursor that is active
				virtual void setType(const CursorType cType) = 0;
				//Fetch the position of the cursor
				virtual Position2F getPosition() const = 0;
				//Set the position of the cursor
				virtual void setPosition(X32 x = 0, X32 y = 0) = 0;
				//Fetch the size of the cursor instance
				virtual void getSize(S32 &width, S32 &height) const = 0;
				//Bind the cursor to the specified region, pass a NULL ptr to unbind
				virtual void bind(const RectangleI *region) = 0;
		};

	};

};

#endif //GALACTIC_PLATFORM_GENERIC_CURSORDEC