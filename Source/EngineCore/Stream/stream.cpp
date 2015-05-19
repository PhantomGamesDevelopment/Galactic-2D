/**
* Galactic 2D
* Source/EngineCore/Stream/stream.cpp
* Definitions for the standard base Stream class and it's necessities
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

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		Stream::Stream() {
			reset();
		}

		Stream::Stream(const Stream &str) {
			copyMembersToStream(str);
		}

		Stream::~Stream() { }

		void Stream::pack(any dataPtr, S64 len) { }

		void Stream::packBits(any dataPtr, S64 len) {
			pack(dataPtr, (len + 7) / 8);
			if (isLoading()) {
				//If the stream is loading data, fetch the pointer now.
				((U8*)dataPtr)[len / 8] &= ((1 << (len & 7)) - 1);
			}
		}

		Stream& Stream::packBytes(any dataPtr, S32 len) {
			pack(dataPtr, len);
			if (needsEndianSwap()) {
				swapBytes(dataPtr, len);
			}
			THISREF();
		}

		void Stream::packU32(U32 &dataRef, U32 maxValue) {
			packBytes(&dataRef, sizeof(dataRef));
		}

		void Stream::packCompressedU32(U32 &dataRef) {
			//To pack a compressed integer, we need to work with some memory trickery
			// to get that extra 8th bit. This is done on a save/load basis, so let's work
			// it out.
			if (isLoading()) {
				//If we're loading data, then we just need to shift some bytes around
				dataRef = 0;
				U8 byteCount = 0;
				U8 moreBytes = 1;
				while (moreBytes > 0) {
					//Read in the next byte
					U8 nextByte;
					pack(&nextByte, 1);
					//Do some bit magic & trickery to pull the value, and test for more bytes
					moreBytes = nextByte & 1;
					nextByte >>= 1;
					dataRef += nextByte << (7 * byteCount++);
				}
			}
			else {
				//Saving is a bit more tricky (pun, haha), we need to perform adjustments on each 8-bit interval
				DynArray<U8> packed;
				U32 remainingPacked = dataRef;
				while (true) {
					//To save data to the stream, we need to fetch each individual 8 bit component, leaving
					// the 8th bit empty for extra space. To do this, we fetch 7 bits from the value and store
					// it in a DynArray, then move to the next, and the next until done.
					U8 nextByte = remainingPacked & 0x7F;
					remainingPacked >>= 7;
					//Don't forget to empty the 8th bit...
					nextByte <<= 1;
					if (remainingPacked > 0) {
						//More to do...
						nextByte |= 1;
						packed.pushToBack(nextByte);
					}
					else {
						//Last byte, push the last, and exit.
						packed.pushToBack(nextByte);
						break;
					}
				}
				//Pack the value to the stream
				pack(packed.addr(), packed.size());
			}
		}

		bool Stream::needsEndianSwap() {
			#if GALACTIC_USE_LENDIAN
				return shouldSwapBytesAlways;
			#else
				return shouldSaveToPersistent;
			#endif
		}

		void Stream::swapBytes(any dataPtr, S32 len) {
			//TO-DO? A simple A/B swap implementation is being used here for now. Consider placing this implement in Tools/endian.h 
			// for consistency purposes?
			U8 *bit = (U8*)dataPtr;
			S32 begin = 0;
			S32 end = len - 1;
			while (begin < end) {
				swapPtrs(bit[end--], bit[begin++]);
			}
		}

		void Stream::countBytes(SIZE_T inPos, SIZE_T inEnd) { }

		S64 Stream::fetchSize() {
			return NO_INDEX;
		}

		S64 Stream::tell() {
			return NO_INDEX;
		}

		void Stream::seek(S64 inPos) { }

		bool Stream::atEnd() {
			S64 pos = tell();
			return ((pos != NO_INDEX) && (pos >= fetchSize()));
		}

		bool Stream::close() {
			return !hasError;
		}

		void Stream::flush() { }

		bool Stream::precache(S64 inPos, S64 inLen) {
			return true;
		}

		void Stream::flushCache() { }

		void Stream::setError() {
			hasError = true;
		}

		S64 Stream::fetchMaxSize() const {
			return maxSize;
		}

		bool Stream::isSaving() const {
			return strIsSaving;
		}

		bool Stream::isLoading() const {
			return strIsLoading;
		}

		bool Stream::isForcingByteSwaps() const {
			return shouldSwapBytesAlways;
		}

		bool Stream::isErrorPresent() const {
			return hasError;
		}

		bool Stream::isErrorPresent() {
			return hasError;
		}

		bool Stream::isCriticalErrorPresent() const {
			return hasCError;
		}

		bool Stream::hasClosed(bool &sHasError) {
			sHasError = false;
			return true;
		}

		void Stream::setByteSwapForcing(bool newFlag) {
			shouldSwapBytesAlways = newFlag;
		}

		Stream &operator<<(Stream &s, C8 &v) {
			s.pack(&v, 1);
			return s;
		}

		Stream &operator<<(Stream &s, U8 &v) {
			s.pack(&v, 1);
			return s;
		}

		Stream &operator<<(Stream &s, S8 &v) {
			s.pack(&v, 1);
			return s;
		}

		Stream &operator<<(Stream &s, U16 &v) {
			s.packBytes(&v, sizeof(v));
			return s;
		}

		Stream &operator<<(Stream &s, S16 &v) {
			s.packBytes(&v, sizeof(v));
			return s;
		}

		Stream &operator<<(Stream &s, U32 &v) {
			s.packBytes(&v, sizeof(v));
			return s;
		}

		Stream &operator<<(Stream &s, S32 &v) {
			s.packBytes(&v, sizeof(v));
			return s;
		}

		Stream &operator<<(Stream &s, bool &v) {
			U32 numBoolVal = v ? 1 : 0;
			s.packBytes(&numBoolVal, sizeof(numBoolVal));
			v = FBOOL(numBoolVal);
			return s;
		}

		Stream &operator<<(Stream &s, F32 &v) {
			s.packBytes(&v, sizeof(v));
			return s;
		}

		Stream &operator<<(Stream &s, U64 &v) {
			s.packBytes(&v, sizeof(v));
			return s;
		}

		Stream &operator<<(Stream &s, S64 &v) {
			s.packBytes(&v, sizeof(v));
			return s;
		}

		Stream &operator<<(Stream &s, F64 &v) {
			s.packBytes(&v, sizeof(v));
			return s;
		}

		Stream &operator<<(Stream &s, String &v) {
			//For strings we pack the string's length as well as the string's contents
			S32 stringSize;
			if (s.isLoading()) {				
				s << stringSize;
				auto maxSize = s.fetchMaxSize();
				if (maxSize > 0 && (stringSize > maxSize)) {
					//Error...
					GC_Error("Stream::pack(STRING): String exceeds maximum bounds for this stream.");
					s.hasError = true;
					s.hasCError = true;
					return s;
				}
				//Empty the string instance and prep it for reading.
				v.empty();
				if (stringSize > 0) {
					//Load the string...
					C8 *strData = new C8[stringSize];
					s.pack(strData, stringSize * sizeof(C8));
					//Add the NULL terminator...
					strData[stringSize - 1] = '\0';
					//And apply...
					v = String(strData);
					//Done with strData, delete...
					SendToHell(strData);
				}
			}
			else {
				//Saving's a bit easier here. Just fetch the length, write it. And then break the string into a UTF16 and write that.
				stringSize = v.length();
				s << stringSize;
				//Count the bytes for the stream, Strings are not treated as array instances, and therefore the byte count will only be reliant
				// on the size (not length) of the stream instance.
				s.countBytes(v.size(), v.size());
				if (stringSize > 0) {
					//Note: We type-cast the .c_str call to (void *) to ensure compliance with the pack method, this may require later investigation
					// but for now, we should be ok.
					s.pack((any)v.c_str(), stringSize * sizeof(C8));
				}
			}
			return s;
		}

		void Stream::reset() {
			maxSize = 0;
			strIsSaving = false;
			shouldSaveToPersistent = false;
			strIsLoading = false;
			shouldSwapBytesAlways = false;
			hasError = false;
			hasCError = false;
		}

		void Stream::copyMembersToStream(const Stream &from) {
			maxSize = from.maxSize;
			strIsSaving = from.strIsSaving;
			shouldSaveToPersistent = from.shouldSaveToPersistent;
			strIsLoading = from.strIsLoading;
			shouldSwapBytesAlways = from.shouldSwapBytesAlways;
			hasError = from.hasError;
			hasCError = from.hasCError;
		}

	};

};