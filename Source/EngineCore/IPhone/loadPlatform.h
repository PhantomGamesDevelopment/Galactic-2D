/**
* Galactic 2D
* Source/EngineCore/IPhone/loadPlatform.h
* Loads up all of the necessary platform headers and our files
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

//Load Apple (IPhone) Libs (Note we use #import instead of #include here because we're directly loading the library)
#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>
//Load CoreFoundation.h
#include <CoreFoundation/CoreFoundation.h>

//Undefine some stuff that's not needed
#undef TYPE_BOOL

//Load in the standard C++ libs used by IPhone
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
#include <mach/mach.h>
#include <mach/mach_host.h>
#include <execinfo.h>
#include <signal.h>
#include <sys/sysctl.h>

//For platform intristics capabilities here, we can't directly use xmmintrin.h here due to some random IPhone bull, so load up an equivalent.
#include <arm_neon.h>

//Apple platforms don't apparently define these, and we need to ensure alignment to 16 bytes (see http://stackoverflow.com/questions/5208356/memory-alignment-on-iphone-and-android)
#define _aligned_malloc(size, memAlign) malloc(size)
#define _aligned_realloc(trg, size, memAlign) realloc(trg, size)
#define _aligned_free(trg) free(trg)

//Type out int32_t and int64_t
typedef int32_t S32_t;
typedef int64_t S64_t;

//Load up the G2D Platform Files (see platformInclude.h for proper load order)
#include "math.h"
#include "time.h"
#include "atomics.h"