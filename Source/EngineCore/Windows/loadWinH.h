/**
* Galactic 2D
* Source/EngineCore/Windows/loadWinH.h
* Safe loading of the <windows.h> header without all of the useless junk it brings.
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

/**
* References: http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745(v=vs.85).aspx
*			  http://stackoverflow.com/questions/1394910/how-to-tame-the-windows-headers-useful-defines
**/

#ifndef PLATFORM_WINDOWS_SAFE_WINH
#define PLATFORM_WINDOWS_SAFE_WINH

#ifdef _WINDOWS_
	#ifndef SAFE_WIN_DEFINED
		#pragma message ("safeWindowsH: This file is detecting that windows.h has already been defined without the safe flag enabled. Please check the source to validate execution order of files.")
	#endif
#endif

//This flag will disable the warning when we load this file another time.
#define SAFE_WIN_DEFINED

//Define WIN32_LEAN_AND_MEAN to disable most of the stuff we'll never use in G2D, the rest can be handled below.
#define WIN32_LEAN_AND_MEAN

//This list of defines removes a majority of stuff we won't use in G2D.
#define NOGDICAPMASKS
#define OEMRESOURCE
#define NOATOM
#define NODRAWTEXT
#define NOKERNEL
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NOCRYPT
#define NOTAPE
#define NOIMAGE
#define NOPROXYSTUB
#define NORPC

//Finally, load the dreaded file of interest.
#include <Windows.h>

#endif //PLATFORM_WINDOWS_SAFE_WINH