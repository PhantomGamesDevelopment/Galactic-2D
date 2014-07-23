/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* loadIOS.h
*
* Load all of the platform ios (IPhone) classes and objects
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
#include "IOSTime.h"
#include "IOSAtomics.h"