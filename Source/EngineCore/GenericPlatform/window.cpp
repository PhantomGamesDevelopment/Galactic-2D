/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/window.cpp
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

#include "../engineCore.h"
#include "window.h"

namespace Galactic {

	namespace Core {

		Window::Window() {
			GC_Warn("Window::Window(): This method is not implemented on the generic platform.");
		}

		Window::~Window() {
			GC_Warn("Window::~Window(): This method is not implemented on the generic platform.");
		}

		void Window::enable() {
			GC_Warn("Window::enable(): This method is not implemented on the generic platform.");
		}

		void Window::disable() {
			GC_Warn("Window::disable(): This method is not implemented on the generic platform.");
		}

		void Window::resize(S32 x, S32 y, S32 width, S32 height) {
			GC_Warn("Window::resize(): This method is not implemented on the generic platform.");
		}

		void Window::resize(RectangleI newWindowSpace) {
			GC_Warn("Window::resize(): This method is not implemented on the generic platform.");
		}

		void Window::moveTo(S32 x, S32 y) {
			GC_Warn("Window::moveTo(): This method is not implemented on the generic platform.");
		}

		void Window::moveTo(Position2I newPos) {
			GC_Warn("Window::moveTo(): This method is not implemented on the generic platform.");
		}

		void Window::bringToFront(bool byForce) {
			GC_Warn("Window::bringToFront(): This method is not implemented on the generic platform.");
		}

		void Window::setTitle(UTF16 const newTitle) {
			GC_Warn("Window::setTitle(): This method is not implemented on the generic platform.");
		}

		void Window::show() {
			GC_Warn("Window::show(): This method is not implemented on the generic platform.");
		}

		void Window::hide() {
			GC_Warn("Window::hide(): This method is not implemented on the generic platform.");
		}

		bool Window::visible() const {
			GC_Warn("Window::visible(): This method is not implemented on the generic platform.");
			return true;
		}

		void Window::minimize() {
			GC_Warn("Window::minimize(): This method is not implemented on the generic platform.");
		}

		bool Window::minimized() const {
			GC_Warn("Window::minimized(): This method is not implemented on the generic platform.");
			return true;
		}

		void Window::maximize() {
			GC_Warn("Window::maximize(): This method is not implemented on the generic platform.");
		}

		bool Window::maximized() const {
			GC_Warn("Window::maximized(): This method is not implemented on the generic platform.");
			return true;
		}

		void Window::restore() {
			GC_Warn("Window::restore(): This method is not implemented on the generic platform.");
		}

		void Window::destroy() {
			GC_Warn("Window::destroy(): This method is not implemented on the generic platform.");
		}

		void Window::setWindowMode(WindowMode inMode) {
			GC_Warn("Window::setWindowMode(): This method is not implemented on the generic platform.");
		}

		WindowMode Window::fetchWindowMode() const {
			GC_Warn("Window::fetchWindowMode(): This method is not implemented on the generic platform.");
			return Windowed;
		}

		void Window::setWindowFocus() {
			GC_Warn("Window::setWindowFocus(): This method is not implemented on the generic platform.");
		}

		void Window::setOpacity(const F32 newOpacity) {
			GC_Warn("Window::setOpacity(): This method is not implemented on the generic platform.");
		}

		bool Window::isInForeground() const {
			GC_Warn("Window::isInForeground(): This method is not implemented on the generic platform.");
			return true;
		}

		bool Window::isInWindow(S32 x, S32 y) const {
			GC_Warn("Window::isInWindow(): This method is not implemented on the generic platform.");
		}

		bool Window::isInWindow(Position2I pos) const {
			GC_Warn("Window::isInWindow(): This method is not implemented on the generic platform.");
		}

		S32 Window::fetchBorderSize() const {
			GC_Warn("Window::fetchBorderSize(): This method is not implemented on the generic platform.");
			return 0;
		}

		bool Window::fetchFSInformation(S32 &x, S32 &y, S32 &width, S32 &height) const {
			GC_Warn("Window::fetchFSInformation(): This method is not implemented on the generic platform.");
			return true;
		}

		bool Window::fetchFSInformation(RectangleI &inRect) const {
			GC_Warn("Window::fetchFSInformation(): This method is not implemented on the generic platform.");
			return true;
		}

		bool Window::fetchRestoreDimensions(S32 &x, S32 &y, S32 &width, S32 &height) const {
			GC_Warn("Window::fetchRestoreDimensions(): This method is not implemented on the generic platform."); 
			return true;
		}

		bool Window::fetchRestoreDimensions(RectangleI &inRect) const {
			GC_Warn("Window::fetchRestoreDimensions(): This method is not implemented on the generic platform.");
			return true;
		}

		void Window::adjustCachedSize(Position2F &newSize) {
			GC_Warn("Window::adjustCachedSize(): This method is not implemented on the generic platform.");
		}

		any Window::fetchWindowHandle() const {
			return PlatformOperations::fetchWindowObject();
		}

		const WindowProperties &Window::fetchWindowProperties() const {
			return *(wProps.getPointer());
		}

	};

};