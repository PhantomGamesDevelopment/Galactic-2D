/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* loadLinux.h
*
* Load all of the platform linux classes and objects
**/

//Load up out linux libs for G2D.
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
#include <wchar.h>
#include <wctype.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <fcntl.h>
#include <dirent.h>
#include <dlfcn.h>
#include <utime.h>
#include <execinfo.h>
#include <signal.h>
#include <sys/sysctl.h>
#include <sys/utsname.h>
#include <libgen.h>

//If we're running on a 64 bit linux platform, load in <xmmintrin.h>
#ifdef __x86_64__
	#include <xmmintrin.h>
#endif 

//Load in the G2D platform files (see platformInclude.h for include order)
#include "LinuxAtomics.h"