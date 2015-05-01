/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/application.h
* Defines a standard application class instance for a generic platform. Mainly templates
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

#ifndef GALACTIC_PLATFORM_GENERIC_APPLICATION
#define GALACTIC_PLATFORM_GENERIC_APPLICATION

namespace Galactic {

	namespace Core {

		/*
		WindowActivationTypes: Defines a list of common activiation/deactivation commands that can be sent from the application
		*/
		enum WindowActivationTypes {
			//Activate: Standard activation command, forced by the engine
			Activate,
			//ActivateByUserInput: User triggered event activation, usually when the user clicks with a mouse in the window space
			ActivateByUserInput,
			//Deactivate: Deactivation command, triggered by clicking outside the app. area
			Deactivate,
		};

		/*
		WindowActionTypes: Defines a list of common application commands that can be sent to window instances
		*/
		enum WindowActionTypes {
			//UserInputOutsideClientArea: User has sent a input command outside of the client area
			UserInputOutsideClientArea = 1,
			//Maximize: The user has sent a maximize command to the window instance
			Maximize,
			//Restore: The user has sent a restore command to the window instance
			Restore,
			//Menu: The user has sent a command to access a menu on the window instance
			Menu,
		};

		/*
		WindowZoneTypes: Defines a list of accessible zones for the window instance
		*/
		enum WindowZoneTypes {
			//NotInside: This area is outside of the window instance
			NotInside,
			//ClientArea: This area is considered as the client area of the window
			ClientArea,
			//NWBorder: This area is the NorthWest (Top-Left) Border
			NWBorder,
			//NBorder: This area is the North (Top) Border
			NBorder,
			//NEBorder: This area is the NorthEast (Top-Right) Border
			NEBorder,
			//EBorder: This area is the East (Right) Border
			EBorder,
			//SEBorder: This area is the SouthEast (Bottom-Right) Border
			SEBorder,
			//SBorder: This area is the South (Bottom) Border
			SBorder,
			//SWBorder: This area is the SouthWest (Bottom-Left) Border
			SWBorder,
			//WBorder: This area is the West (Left) Border
			WBorder,
			//TitleBar: This area is the window's title bar
			TitleBar,
			//CloseButton: This is the close button
			CloseButton,
			//MinimizeButton: This is the minimize button
			MinimizeButton,
			//MaximizeButton: This is the maximize button
			MaximizeButton,
			//SystemMenu: This is the system menu area of the window
			SystemMenu,

			//Unknown: This is not a defined window area
			Unknown = NotInside,
		};

		/*
		DropEventTypes: Actions and events used by Drag and Drop controls when a control is "dropped"
		*/
		enum DropEventTypes {
			//None: No event is occuring
			None, 
			//Copy: A copy event is occuring
			Copy,
			//Move: A move event is occuring
			Move,
			//Link: A link event is occuring
			Link,
		};

		/*
		MouseButtonTypes: Buttons and actions used by mouse instances
		*/
		enum MouseButtonTypes {
			//LeftMouse: Left Mouse Button
			LeftMouse,
			//MiddleMouse: Middle Mouse (Wheel) Button
			MiddleMouse,
			//RightMouse: Right Mouse Button
			RightMouse,
			//Thumb1: Thumb Button #1
			Thumb1,
			//Thumb2: Thumb Button #2
			Thumb2,

			//Unknown: Unknown mouse action
			Unknown,
		};

		/*
		ControllerButtonTypes: Buttons and actions used by game controller (Xbox, Steam, Playstation) instances
		*/
		enum ControllerButtonTypes {
			/* Standard Controller Buttons */
			//BottomButton (Lower Face Button [Xbox A])
			BottomButton,
			//RightButton (Right Face Button [Xbox B])
			RightButton,
			//LeftButton (Left Face Button [Xbox X])
			LeftButton,
			//TopButton (Top Face Button [Xbox Y])
			TopButton,
			//RightTrigger (Right Rear Trigger button)
			RightTrigger,
			//LeftTrigger (Left Rear Trigger button)
			LeftTrigger,
			//RightShoulder (Right Shoulder Button)
			RightShoulder,
			//LeftShoulder (Left Shoulder Button)
			LeftShoulder,
			//RightSpecial (Special Right Button)
			RightSpecial,
			//LeftSpecial (Special Left Button)
			LeftSpecial,
			//RightThumb (Right Thumbstick Button)
			RightThumb,
			//LeftThumb (Left Thumbstick Button)
			LeftThumb,
			//DPadUp
			DPadUp,
			//DPadRight
			DPadRight,
			//DPadLeft
			DPadLeft,
			//DPadDown
			DPadDown,
			//RightAnalogStickUp
			RightAnalogStickUp,
			//RightAnalogStickRight
			RightAnalogStickRight,
			//RightAnalogStickLeft
			RightAnalogStickLeft,
			//RightAnalogStickDown
			RightAnalogStickDown,
			//LeftAnalogStickUp
			LeftAnalogStickUp,
			//LeftAnalogStickRight
			LeftAnalogStickRight,
			//LeftAnalogStickLeft
			LeftAnalogStickLeft,
			//LeftAnalogStickDown
			LeftAnalogStickDown,

			/* Tresholds, Specials */
			//RightAnalogX: X Movement on the RAS
			RightAnalogX,
			//RightAnalogY: Y Movement on the RAS
			RightAnalogY,
			//LeftAnalogX: X Movement on the LAS
			LeftAnalogX,
			//LeftAnalogY: Y Movement on the LAS
			LeftAnalogY,
			//RightTriggerThreshold: Maximum application of the right trigger
			RightTriggerThreshold,
			//LeftTriggerThreshold: Maximum application of the left trigger
			LeftTriggerThreshold,

			/* Steam Controller Specials */
			//Touch0
			Touch0,
			//Touch1
			Touch1,
			//Touch2
			Touch2,
			//BackRight
			BackRight,
			//BackLeft
			BackLeft,

			/* Misc */
			//Unknown Controller Button
			Unknown,
		};

		/*
		GestureEventTypes: Event actions used by android and apple phone instances
		*/
		enum GestureEventTypes {
			//None: No gesture event is occuring
			None,
			//Scroll: A scroll event is occuring
			Scroll,
			//Magnify: A magnify event is occuring
			Magnify,
			//Swipe: A swipe event is occuring
			Swipe,
			//Rotate: A rotate event is occuring
			Rotate,
		};

		/*
		PopUpOrientationType: Defines the two types of orientation to be used by pop-up window instances
		*/
		enum PopUpOrientationType {
			//Horizontal
			Horizontal,
			//Vertical
			Vertical,
		};

		/*
		ApplicationMessageHandler: Proxy for catching and pushing application messages around the engine
		*/
		class ApplicationMessageHandler {
			//Shortcut to the strong reference pointer of the application window instance
			typedef const StrongReferencePtr<Window> &windowRef;

			public:
				/* Public Class Methods */
				//Destructor
				virtual ~ApplicationMessageHandler() {
				}
				//Callback function that is triggered when the application's active state is changed
				virtual bool onApplicationActiveStateChanged(cbol isActive) {
					return false;
				}

				/* Window Related Messages */
				//Should this application process user input messages?
				virtual bool shouldProcessUserInputMessages(windowRef wRef) const {
					return false;
				}
				//Callback function when a Window Paint command is triggered by the OS
				virtual void onWindowPaint(windowRef wRef) {
				}
				//Callback function for a window action event
				virtual bool onWindowActionEvent(windowRef wRef, WindowActionTypes wActType) {
					return true;
				}
				//Callback function when a window is resized
				virtual bool onWindowResized(windowRef wRef, X32 width, X32 height, bool wasMinimized = false) {
					return false;
				}
				//Callback function to be triggered when a resize command begins, returns a boolean if the event was successfully triggered
				virtual bool onBeginResize(windowRef wRef) {
					return true;
				}
				//Callback function that is triggered during the resize event
				virtual void onWindowResizing(windowRef wRef) {
				}
				//Callback function to be triggered when a resize command ends
				virtual void onEndResize(windowRef wRef) {
				}
				//Callback function to be triggered when a window moves
				virtual void onWindowMoved(windowRef wRef, X32 x, X32 y) {
				}
				//Callback function to be triggered when the window closes
				virtual void onWindowClosed(windowRef wRef) {
				}
				//Fetch the WindowZoneType for the given point
				virtual WindowZoneTypes fetchWZTypeFromPoint(windowRef wRef, const Position2I point) {
					return WindowZoneTypes::NotInside;
				}
				//Fetch the WindowZoneType for the given <x, y> pair
				virtual WindowZoneTypes fetchWZTypeFromPoint(windowRef wRef, X32 x, X32 y) {
					return WindowZoneTypes::NotInside;
				}
				//Callback function to be triggered when the window activation type changes
				virtual void onWindowActivationChanged(windowRef wRef, const WindowActivationTypes wActType) {
				}

				/* Drag and Drop Messages */
				//Standard callback when the drag event moves over a window
				virtual DropEventTypes onDragEnterWindow(windowRef wRef) {
					return DropEventTypes::None;
				}
				//Standard callback when the drag event leaves a window
				virtual void onDragLeaveWindow(windowRef wRef) {
				}
				//Callback function to be triggered when the drop event is triggered
				virtual DropEventTypes onDragEventDrop(windowRef wRef) {
					return DropEventTypes::None;
				}
				//Callback when a drag event enters text
				virtual DropEventTypes onDragEnterText(windowRef wRef, strRef text) {
					return DropEventTypes::None;
				}
				//Callback when a drag event enters an external file
				virtual DropEventTypes onDragEnterExternalFile(windowRef wRef, const DynArray<String> &file) {
					return DropEventTypes::None;
				}

				/* User Input Messages */
		};

		/*
		ApplicationModifierKeyState: Proxy for catching information about standard modifier keys (Shift, Ctrl, Etc)
		*/

		/*
		Application: Standard set of functions and operations as used by the application instance
		*/

	};

};

#endif //GALACTIC_PLATFORM_GENERIC_APPLICATION