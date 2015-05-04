/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/Input/textInput.h
* Defines a set of classes and methods to handle text input from the user
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

#ifndef GALACTIC_INTERNAL_GENERICPLATFORM_TEXTINPUT
#define GALACTIC_INTERNAL_GENERICPLATFORM_TEXTINPUT

namespace Galactic {

	namespace Core {

		/*
		TextInputContext: Whenever you define a class instance that handles text input from the user, it should either inherit or store
		 a copy of this class on the side to handle the platform related functions as needed for user input.
		*/
		class TextInputContext {
			public:
				/* Enumerations */
				enum InputPosition {
					//Begin: Tell the input to move to the beginning
					Begin,
					//End: Tell the input to move to the end
					End,
				};

				/* Public Class Methods */
				//Return the length of the current text instance
				virtual U32 getLength() = 0;
				//Fetch the reference of the current window instance
				virtual StrongReferencePtr<Window> getWindow() = 0;
				//Start the user input
				virtual void beginInput() = 0;
				//End the user input
				virtual void endInput() = 0;
				//Update the specified input range (highlight it)
				virtual void updateSpecifiedRange(S32 startIndex, S32 length) = 0;
				//Is the specified text read-only?
				virtual bool readOnly() = 0;
				//Fetch information from the current selected range
				virtual void fetchRangeSelectInfo(U32 &startIndex, U32 &length, InputPosition &iPos) = 0;
				//Apply information to the context over the selected range
				virtual void setRangeSelectInfo(Z32 startIndex, Z32 length, const InputPosition iPos) = 0;
				//Fetch the text in the specified range
				virtual void fetchTextFromRange(Z32 startIndex, Z32 length, String &str) = 0;
				//Set the text over the specified range
				virtual void setTextOverRange(Z32 startIndex, Z32 length, strRef str) = 0;
				//Fetch a ASCII character code from a point on the screen
				virtual S32 fetchASCIIFromPosition(const Position2F &pos) = 0;
				//Obtain the available screen bounds for the specified range and text length
				virtual void fetchTextBoundsInfo(Z32 startIndex, Z32 length, Position2F &pos, Vector2F &length) = 0;
				//Measure the available space for text using the provided information
				virtual void measureAvailableSpace(Position2F &pos, Vector2F &length) = 0;
		};

		/*
		TextInputNotifier: A basic messaging class instance that wraps over the TextInputContent to forward messages to the platform input system whe
		 text changes are detected
		*/
		class TextInputNotifier {
			public:
				/* Enumerations */
				/*
				ChangeInformation: What type of change is occuring.
				*/
				enum class ChangeInformation {
					//Created: The text layout was just created.
					Created,
					//Modified: The text layout was just modified.
					Modified,
					//Destroyed: The text layout was just destroyed.
					Destroyed,
				};

				/* Public Class Methods */
				//Notification command to be sent when the selected text is modified
				virtual void notifySelectedTextChange() = 0;
				//Notification command to be sent when the text over a specified range is adjusted
				virtual void notifyTextChange(Z32 startIndex, Z32 oldLen, Z32 newLen) = 0;
				//Notification command to be sent when the layout is changed
				virtual void notifyLayoutChange(const ChangeInformation info) = 0;
				//Forwarding command when text input ends
				virtual void endInput() = 0;
		};

		/*
		TextInputSystem: Generic platform abstract wrapper for the text input system. Each individual platform should override this instance to handle per-platform
		 functioning of the system
		*/
		class TextInputSystem {
			public:
				/* Public Class Methods */
				//Register a TextInputContent to the engine to recieve notification callbacks. Returns a notification object for storage purposes.
				virtual StrongReferencePtr<TextInputNotifier> registerTextInputContext(const StrongReferencePtr<TextInputContext> &context) = 0;
				//Unregister a TextInputContext from the engine. Individual input objects should call this prior to deletion
				virtual void unregisterTextInputContext(const StrongReferencePtr<TextInputContext> &context) = 0;
				//Activate the specified TextInputContext object. This method should be called once Keyboard focus is obtained to the editable input object
				virtual void activateTextInputContext(const StrongReferencePtr<TextInputContext> &context) = 0;
				//Deactivate the specified TextInputContext object. Once the keyboard focus is lost, or input is done on an object, call this method
				virtual void deactivateTextInputContext(const StrongReferencePtr<TextInputContext> &context) = 0;
		};

	};

};

#endif //GALACTIC_INTERNAL_GENERICPLATFORM_TEXTINPUT