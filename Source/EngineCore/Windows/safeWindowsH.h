/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* safeWindowsH.h
*
* When you want to load up windows.h in Galactic, load this file instead, it disables a ton of unnecessary & unused windows functions in the engine.
*
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