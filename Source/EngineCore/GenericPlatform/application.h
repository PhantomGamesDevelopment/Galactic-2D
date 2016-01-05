/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/application.h
* Defines a standard application class instance for a generic platform. Mainly templates
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

#ifndef GALACTIC_PLATFORM_GENERIC_APPLICATION
#define GALACTIC_PLATFORM_GENERIC_APPLICATION

namespace Galactic {

	namespace Core {

		/* Forward Declarations for Application Class Requirements */
		//Forward Declaration for TextInputSystem
		class TextInputSystem;
		//Forward Declaration for GenericForceFeedback
		class GenericForceFeedback;

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
		ApplicationMessageHandler: Proxy for catching and pushing application message callback functions around the engine
		*/
		class ApplicationMessageHandler {
			//Shortcut to the strong reference pointer of the application window instance
			typedef const StrongReferencePtr<Window> &windowRefPtr;
			typedef const StrongReference<Window> &windowRef;

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
				virtual bool shouldProcessUserInputMessages(windowRefPtr wRef) const {
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
				virtual DropEventTypes onDragEnterWindow(windowRefPtr wRef) {
					return DropEventTypes::None;
				}
				//Standard callback when the drag event leaves a window
				virtual void onDragLeaveWindow(windowRefPtr wRef) {
				}
				//Callback function to be triggered when the drop event is triggered
				virtual DropEventTypes onDragEventDrop(windowRefPtr wRef) {
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

				/* Keyboard Input Messages */
				//Callback to be triggered when a key is pressed
				virtual bool onKeyPressed(X32 keyCode, Z32 charCode, cbol repeated) {
					return false;
				}
				//Callback to be triggered when a key is released
				virtual bool onKeyReleased(X32 keyCode, Z32 charCode, cbol repeated) {
					return false;
				}
				//Callback to be triggered for each individual keyboard character press
				virtual bool onKeyCharacter(const C8 character, cbol repeated) {
					return false;
				}

				/* Mouse Input Messages */
				//Callback to be triggered when the mouse is pressed
				virtual bool onMousePressed(windowRefPtr wRef, const MouseButtonTypes mBtn) {
					return false;
				}
				//Callback to be triggered when the mouse is released
				virtual bool onMouseReleased(const MouseButtonTypes mBtn) {
					return false;
				}
				//Callback to be triggered when the mouse moves
				virtual bool onMouseMove() {
					return false;
				}
				//Callback to be triggered when the mouse moves with position information
				virtual bool onMouseUpdatePosition(X32 x, X32 y) {
					return false;
				}
				//Callback to be triggered when the cursor changes
				virtual bool onCursorUpdate() {
					return false;
				}
				//Callback to be triggered when the mouse is double-clicked
				virtual bool onMouseDoubleClick(windowRefPtr wRef, const MouseButtonTypes mBtn) {
					return false;
				}
				//Callback to be triggered when the mouse wheel is moved
				virtual bool onMouseWheelMove(const F32 dM) {
					return false;
				}

				/* Controller Input Messages */
				//Callback to be triggered when a controller button is pressed
				virtual bool onControllerPressed(ControllerButtonTypes cBtn, S32 controllerID, cbol repeatd) {
					return false;
				}
				//Callback to be triggered when a controller button is released
				virtual bool onControllerReleased(ControllerButtonTypes cBtn, S32 controllerID, cbol repeatd) {
					return false;
				}
				//Callback to be triggered when a controller's analog stick is updated
				virtual bool onControllerAnalogUpdate(ControllerButtonTypes cBtn, S32 controllerID, F32 dM) {
					return false;
				}

				/* Phone Gesture Messages */
				//Standard callback when a gesture event begins
				virtual void onBeginGestureEvent() {
				}
				//Standard callback when a gesture event ends
				virtual void onEndGestureEvent() {
				}
				//Callback to be triggered when the user touches the device to start a gesture event
				virtual bool onTouchInputGesture(GestureEventTypes gType, const Position2F &dM, F32 dW) {
					return false;
				}
				//Callback to be triggered when the user moves the input of a touch event gesture
				virtual bool onTouchInputMove(const Position2F &pos, S32 eventIndex, S32 controllerID) {
					return false;
				}
				//Callback to be triggered when the user begins a touch input event
				virtual bool onTouchInputBegin(windowRefPtr wRef, const Position2F &pos, S32 eventIndex, S32 controlerID) {
					return false;
				}
				//Callback to be triggered when the user ends a touch input event
				virtual bool onTouchInputEnd(const Position2F &pos, S32 eventIndex, S32 controllerID) {
					return false;
				}
				//Callback to be triggered when the device detects movement and needs to update based on the movement
				virtual bool onDeviceMoveUpdate(const Vector3F &tilt, const Vector3F &rotation, const Vector3F &gravity, const Vector3F &acceletation, S32 controllerID) {
					return false;
				}

		};

		/*
		ViewingDeviceInformation: Storage structure for obtained information about the client viewing area as used by the application
		*/
		struct ViewingDeviceInformation {
			/* Struct Members */
			//Is this monitor/TV the primary viewing device?
			bool isPrimaryDevice;
			//The native width of the viewing device (In Pixels), used for safe area calculations
			S32 deviceWidth;
			//The native height of the viewing device (In Pixels), used for safe area calculations
			S32 deviceHeight;
			//The name of this particular device
			String deviceName;
			//The string identifier of the decive
			String deviceID;
		};

		/*
		ViewingDeviceMetrics: Storage structure for obtaining important information as it pertains to viewing area size and safe-area
		*/
		struct ViewingDeviceMetrics {
			/* Struct Methods */
			//Constructor
			ViewingDeviceMetrics() :
				absoluteSafeArea(0.0f, 0.0f),
				relativeSafeArea(0.0f, 0.0f) { }

			/* Struct Members */
			//The display area's width
			S32 displayWidth;
			//The display area's height
			S32 displayHeight;
			//The 'Working Area' of this device, this is the area of the screen not covered by OS bars (Taskbar, Etc)
			RectangleI workingArea;
			//The 'Virtual Area' of this device, this is the full screen size
			RectangleI virtualArea;
			//The absolute safe area of this device, this is the limits of the available space on the screen
			Vector2F absoluteSafeArea;
			//The relative safe area of this device, if there is "spill" over from rendering, this area can be used. (Mainly for PCs)
			Vector2F relativeSafeArea;
			//Information on ALL connected physical monitor devices, this is only used on PCs at the moment (Consoles don't allow multiple monitors)
			DynArray<ViewingDeviceInformation> physicalMonitorInformation;
		};

		/*
		ApplicationModifierKeyState: Proxy for catching information about standard modifier keys (Shift, Ctrl, Etc)
		*/
		class ApplicationModifierKeyState {
			public:
				/* Public Class Methods */
				//Constructor
				ApplicationModifierKeyState(cbol isRightShiftDown, cbol isRightCtrlDown, cbol isRightAltDown, cbol isLeftShiftDown, cbol isLeftCtrlDown, cbol isLeftAltDown) :
					rightShiftDown(isRightShiftDown),
					rightCtrlDown(isRightCtrlDown),
					rightAltDown(isRightAltDown), 
					leftShiftDown(isLeftShiftDown),
					leftCtrlDown(isLeftCtrlDown),
					leftAltDown(isLeftAltDown) { }

				//Is one of the two shift keys being held down?
				bool isShiftDown() const {
					return rightShiftDown || leftShiftDown;
				}
				//Is one of the two control keys being held down?
				bool isCtrlDown() const {
					return rightCtrlDown || leftCtrlDown;
				}
				//Is one of the two alternate keys being held down?
				bool isAltDown() const {
					return rightAltDown || leftAltDown;
				}
				//Is the right shift key being held down?
				bool isRightShiftDown() const {
					return rightShiftDown;
				}
				//Is the right control key being held down?
				bool isRightCtrlDown() const {
					return rightCtrlDown;
				}
				//Is the right alternate key being held down?
				bool isRightAltDown() const {
					return rightAltDown;
				}
				//Is the left shift key being held down?
				bool isLeftShiftDown() const {
					return leftShiftDown;
				}
				//Is the left control key being held down?
				bool isLeftCtrlDown() const {
					return leftCtrlDown;
				}
				//Is the left alternate key being held down?
				bool isLeftAltDown() const {
					return leftAltDown;
				}

			private:
				/* Private Class Members */
				//Is the right shift button down?
				bool rightShiftDown;
				//Is the right control button down?
				bool rightCtrlDown;
				//Is the right alternate button down?
				bool rightAltDown;
				//Is the left shift button down?
				bool leftShiftDown;
				//Is the left control button down?
				bool leftCtrlDown;
				//Is the left alternate button down?
				bool leftAltDown;
		};

		/*
		Application: Standard set of functions and operations as used by the application instance
		*/
		class Application {
			public:
				/* Public Class Methods */
				//Constructor
				Application(const StrongReferencePtr<Cursor> &cursorObj) :
					appCursor(cursorObj),
					appMessageHandler(MakeRefPtr(new ApplicationMessageHandler())) { }
				//Destructor
				virtual ~Application() { }
				//Standard running engine class time move method 
				virtual void tick(const F32 dt) { }
				//Destroy this application instance
				virtual void destroyApplication() { }
				//Create a window instance for the application
				virtual StrongReference<Window> createWindow() {
					return MakeRefPtr(new Window());
				}
				//Initialize a window instance as needed by the application
				virtual void initWindow(const StrongReference<Window> &wndRef, const StrongReference<WindowProperties> &wProps, const StrongReferencePtr<Window> &parentWnd, cbol showNow) {}
				//Pump all of the OS messages through the application
				virtual void pumpMessages(const F32 dt) { }
				//Process all events currently being held off for this tick cycle
				virtual void processHeldEvents(const F32 dt) { }
				//Poll up user input device states as needed for the game instance
				virtual void pollInputDeviceState(const F32 dt) { }
				//Set the application's message handler object
				virtual void setAppMessageHandler(const StrongReference<ApplicationMessageHandler> &mhRef) {
					appMessageHandler = mhRef;
				}
				//Generic Proxy to OS SetCapture function for mouse input
				virtual void setCapture(const StrongReferencePtr<Window> &wndRef) { }
				//Fetch the OS capture object
				virtual any getCapture() const { 
					return NULL; 
				}
				//Set High Precision Mouse Input mode 
				virtual void setHPMouseMode(const StrongReferencePtr<Window> &wndRef, bool toggleFlag) { }
				//Check the status of High Precision mouse input
				virtual bool usingHPMouseMode() const {
					return false;
				}
				//Fetch the working area
				virtual RectangleI getWorkingArea(const RectangleI &cRef) const {
					RectangleI out(0, 0, 0, 0);
					return out;
				}
				//Fetch the status of the modifier keys
				virtual ApplicationModifierKeyState getModKeyState() const {
					return ApplicationModifierKeyState(false, false, false, false, false, false);
				}
				//Fetch the viewing device metrics
				virtual void fetchViewingMetrics(ViewingDeviceMetrics &metrics) const { }
				//Calculate the position of a popup window
				virtual bool calculatePopupWindowPos(const RectangleI &anchorPos, const Vector2F &sizeVec, const Position2F *calculatedPos, const PopUpOrientationType oType) { 
					return false;
				}
				//Fetch the text input class instance for this application
				virtual TextInputSystem *getTextInputSystem() {
					return NULL;
				}
				//Fetch the force feedback class instance for this application
				virtual GenericForceFeedback *getForceFeedbackSystem() {
					return NULL;
				}

				/* Public Class Members */
				//Strong reference to the cursor instance which controlls this application
				const StrongReferencePtr<Cursor> appCursor;

			protected:
				/* Protected Class Members */
				//Strong reference to the application message proxy system
				StrongReference<ApplicationMessageHandler> appMessageHandler;

		};

	};

};

#endif //GALACTIC_PLATFORM_GENERIC_APPLICATION