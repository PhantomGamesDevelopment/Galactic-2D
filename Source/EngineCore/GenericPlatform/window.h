/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/window.h
* Standard platform window handler. Mainly templatized function decs for Galactic Supported Platforms
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

#ifndef GALACTIC_PLATFORM_GENERIC_WINDOW
#define GALACTIC_PLATFORM_GENERIC_WINDOW

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		WindowMode: Defines a list of standard modes the window could be in
		*/
		enum WindowMode {
			//Fullscreen: The window is in Standard OS style Fullscreen mode (Contains Border)
			Fullscreen,
			//AllScreen: Non-Standard Fullscreen mode (No Outer Border)
			AllScreen,
			//Windowed: Standard OS style Windowed mode
			Windowed,
		};

		/*
		WindowProperties: Defines a list of parameters and settings used by a standard window instance
		*/
		class WindowProperties {
			public:
				/* Public Class Methods */
				FINLINE RectangleF toRectangleF() const {
					Position2F pos, ext;
					pos.set(xPos, yPos);
					ext.set(xWidth, yWidth);
					return RectangleF(pos, ext);
				}

				/* Public Class Members */
				//Window position parameters
				//X position
				F32 xPos;
				//Y position
				F32 yPos;
				//X Width
				F32 xWidth;
				//Y Width
				F32 yWidth;

				//Size adjustment parameters
				//Calculated max width
				S32 cMaxWidth;
				//Calculated max height
				S32 cMaxHeight;

				//Window attributes
				//Title
				String wTitle;
				//Corner radius on the window instance
				S32 wCornerRadius;
				//Window opacity
				F32 wOpacity;
				//Window accepts user input
				bool wAcceptInput;
				//Window gains immediate focus when opened
				bool wFocusOnOpen;
				//Window is currently the top-most window
				bool wIsTop;
				//Window supports transparency
				bool wSupportsTransparent;
				//Window appears in the OS taskbar
				bool wAppearsInTaskbar;
				//Window contains OS borders
				bool wHasOSBorders;
				//Window is allowed to be minimized
				bool wCanMinimize;
				//Window is allowed to be maximized
				bool wCanMaximize;
				//Window is treated as a standard OS window
				bool wIsStandard;
				//Window is resizable
				bool wIsResizable;
				//This window will be resized frequently
				bool wResizesFrequently;
		};

		/*
		Window: Defines a standard platform independant window wrapper class instance to be used by the engine.
		*/
		class Window {
			public:
				/* Public Class Methods */
				//Standard (Default) Constructor
				Window();
				//Destructor
				virtual ~Window();
				//Enable the window (Allow input)
				virtual void enable();
				//Disable the window (Deny input)
				virtual void disable();
				//Resize window given X, Y, Width, Height
				virtual void resize(S32 x, S32 y, S32 width, S32 height);
				//Resize window given RectangleI
				virtual void resize(RectangleI newWindowSpace);
				//Move the window to the specified X, Y coords
				virtual void moveTo(S32 x, S32 y);
				//Move the window to the specified Position2I coord
				virtual void moveTo(Position2I newPos);
				//Bring this window to the front (into focus)
				virtual void bringToFront(bool byForce = false);
				//Set the window's title
				virtual void setTitle(UTF16 const newTitle);
				//Display the window
				virtual void show();
				//Hide the window
				virtual void hide();
				//Is the window visible?
				virtual bool visible() const;
				//Minimize the window
				virtual void minimize();
				//Is the window currently minimized?
				virtual bool minimized() const;
				//Maximize the window
				virtual void maximize();
				//Is the window currently maximized?
				virtual bool maximized() const;
				//Restore the window
				virtual void restore();
				//Destroy the window instance
				virtual void destroy();
				//Set the window's mode
				virtual void setWindowMode(WindowMode inMode);
				//Fetch the window's mode
				virtual WindowMode fetchWindowMode() const;
				//Wrapper for the standard OS SetWindowFocus function.
				virtual void setWindowFocus();
				//Set the opacity of the window (0.0 - 1.0f)
				virtual void setOpacity(const F32 newOpacity);
				//Is our window in the foreground?
				virtual bool isInForeground() const;
				//Does the specified X/Y coord exist in the window space?
				virtual bool isInWindow(S32 x, S32 y) const;
				//Does the specified Position2I exist in the window space?
				virtual bool isInWindow(Position2I pos) const;
				//Fetch the border size (Needed primarily for Windows)
				virtual S32 fetchBorderSize() const;

				//Fetch the fullscreen information from the computer (Place into four S32s)
				virtual bool fetchFSInformation(S32 &x, S32 &y, S32 &width, S32 &height) const;
				//Fetch the fullscreen information from the computer (Place into a RectangleI)
				virtual bool fetchFSInformation(RectangleI &inRect) const;
				//Fetch the window's restored dimensions into S32 values
				virtual bool fetchRestoreDimensions(S32 &x, S32 &y, S32 &width, S32 &height) const;
				//Fetch the window's restored dimensions into a RectangleI
				virtual bool fetchRestoreDimensions(RectangleI &inRect) const;
				//Adjust the window's cached size after an update
				virtual void adjustCachedSize(Position2F &newSize);

				//Fetch the window handle in a standard pointer format for any OS
				virtual any fetchWindowHandle() const;
				//Fetch the window properties object associated with this window instance
				virtual const WindowProperties &fetchWindowProperties() const;
				
			protected:
				/* Protected Class Members */
				//Strong reference pointer to the Window Properties
				StrongReferencePtr<WindowProperties> wProps;
		};

	};

};

#endif //GALACTIC_PLATFORM_GENERIC_WINDOW