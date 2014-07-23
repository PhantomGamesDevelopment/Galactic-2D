/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* loadAndroid.h
*
* Load all of the platform android classes and objects
**/

//Load up out android libs for G2D.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <wctype.h>
#include <pthread.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <utime.h>

//Android platforms don't apparently define these, and we need to ensure alignment to 16 bytes (see http://stackoverflow.com/questions/5208356/memory-alignment-on-iphone-and-android)
#define _aligned_malloc(size, memAlign) malloc(size)
#define _aligned_realloc(trg, size, memAlign) realloc(trg, size)
#define _aligned_free(trg) free(trg)

//Load in the G2D platform files (see platformInclude.h for include order)
#include "AndroidTime.h"
#include "AndroidAtomics.h"