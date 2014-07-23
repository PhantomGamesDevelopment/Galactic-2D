/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* loadMac.h
*
* Load all of the platform mac classes and objects
**/

/* Mac Platform Settings */
//Disable warning if multiple instances of gl.h are included. This "might" be possible if a plugin loads some kind of GL supported image lib.
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

//Load Standard MAC Libs.
#include <Carbon/Carbon.h>
#include <CoreServices/CoreServices.h>
#include <CoreFoundation/CoreFoundation.h>

//IF this instance of MAC has Objective-C enabled, we can take advantage of the Cocoa library to get some extra shortcuts in some GL stuff
#ifdef __OBJC__
	#import <Cocoa/Cocoa.h>
#endif

//Undefine some stuff that's not needed
#undef TYPE_BOOL

//Load in standard C++ libs needed by MAC
#include <string.h>
#include <alloca.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
#include <sys/time.h>
#include <math.h>
#include <mach/mach_time.h>
#include <wchar.h>
#include <wctype.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <libkern/OSAtomic.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <fcntl.h>
#include <dirent.h>
#include <dlfcn.h>
#include <copyfile.h>
#include <utime.h>
#include <mach/mach_host.h>
#include <mach/task.h>
#include <execinfo.h>
#include <signal.h>
#include <sys/sysctl.h>
#include <xmmintrin.h>

//Apple platforms don't apparently define these, and we need to ensure alignment to 16 bytes (see http://stackoverflow.com/questions/5208356/memory-alignment-on-iphone-and-android)
#define _aligned_malloc(size, memAlign) malloc(size)
#define _aligned_realloc(trg, size, memAlign) realloc(trg, size)
#define _aligned_free(trg) free(trg)

//Type out int32_t and int64_t
typedef int32_t S32_t;
typedef int64_t S64_t;

//Load up the G2D Platform Files (see platformInclude.h for proper load order)
#include "MacAtomics.h"