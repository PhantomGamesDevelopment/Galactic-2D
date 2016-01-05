/**
* Galactic 2D
* Source/EngineCore/Android/loadPlatform.h
* Loads up all of the necessary platform headers and our files
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
#include "math.h"
#include "time.h"
#include "atomics.h"