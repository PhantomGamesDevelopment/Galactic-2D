/**
* Galactic 2D
* Source/EngineCore/Files/fileLogging.h
* Loads the file logging class wrappers and associated tools for file logging
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

//Extern access to file log ignore calls
extern bool gIgnoreFileLogCalls;
//Macro shortcut for log writting for files. We toggle the ignore flag on/off to ensure nothing else jumps in front of the log call.
#define FILE_LOGWRITE(className, format, ...) \
		if (!gIgnoreFileLogCalls) { \
			gIgnoreFileLogCalls = true; \
			String form = String::ToStr("<FILELOG %s> %s", className, format); \
			GC_Print(form.c_str(), ##__VA_ARGS__); \
			gIgnoreFileLogCalls = false; \
		}

//Load the associated logged file wraps

#include "loggedFileHandle.h"
#include "loggedFile.h"