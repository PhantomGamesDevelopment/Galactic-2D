/**
* Galactic 2D
* Source/EngineCore/Stream/stream.h
* Definitions for the standard base Stream class and it's necessities
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

#ifndef GALACTIC_INTERNAL_STREAM
#define GALACTIC_INTERNAL_STREAM

namespace Galactic {

	namespace Core {
	
		/*
		Stream: A basic container used to store large amounts of data into a serialized bit format which can then be pushed around the engine, or across
		 the network line. This class should be used whenever data needs to be "streamed" from one location to another, hence the name.
		*/
		class Stream {
			public:
				/* Enumerations */
				//Empty Stream Related enum
				enum {
					//NO_INDEX: Used in search and move operations to test for location based on index, specifically if this index is outside the bounds.
					NO_INDEX = -1,
				};

				/* Public Class Methods */
				//Default (Empty) Constructor
				Stream();
				//Copy Constructor
				Stream(const Stream &str);
				//Destructor
				virtual ~Stream();

				/* Packing Methods */
				//Pack data to or from the stream
				virtual void pack(any dataPtr, S64 len);
				//Pack bits to or from the stream
				virtual void packBits(any dataPtr, S64 len);
				//Pack a byte block to or from the stream, applying endian swapping where necessary
				virtual Stream& packBytes(any dataPtr, S32 len);
				//Pack an uncompressed integer to or from the stream
				virtual void packU32(U32 &dataRef, U32 maxValue);
				//Pack a compressed integer to or from the stream, saving the last bit for 'extra' storage
				virtual void packCompressedU32(U32 &dataRef);
				//Do we need to perform endian swaps?
				FINLINE bool needsEndianSwap();
				//Perform the byte level swap for endian compliance
				void swapBytes(any dataPtr, S32 len);

				/* Standard Stream Operation Functions */
				//Count the number of bytes between the specified points
				virtual void countBytes(SIZE_T inPos, SIZE_T inEnd);
				//Fetch the current size used by the stream
				virtual S64 fetchSize();
				//Tell the current position of the stream operation
				virtual S64 tell();
				//Move the stream operation to the specified position
				virtual void seek(S64 inPos);
				//Are we at the end of the stream?
				virtual bool atEnd();
				//Close the stream
				virtual bool close();
				//Flush the contents of this stream
				virtual void flush();
				//Send a flag to the stream that the data between the specified points is up for a read operation and to cache the information for quick access
				virtual bool precache(S64 inPos, S64 inLen);
				//Flush any data that was cached
				virtual void flushCache();

				/* Misc Functions */
				//Tell the engine that this stream has an error
				virtual void setError();
				//Fetch the maximum size that we can pack to this stream
				FINLINE S64 fetchMaxSize() const;
				//Are we currently saving data?
				FINLINE bool isSaving() const;
				//Are we currently loading data?
				FINLINE bool isLoading() const;
				//Are we forcing byte swapping?
				FINLINE bool isForcingByteSwaps() const;
				//Is an error present in this stream?
				FINLINE bool isErrorPresent() const;
				//Same as above, no const or inline flag
				virtual bool isErrorPresent();
				//Is there a critical error present in this stream?
				FINLINE bool isCriticalErrorPresent() const;
				//Has this stream been successfully closed?
				virtual bool hasClosed(bool &sHasError);
				//Set the shouldSwapBytesAlways flag
				void setByteSwapForcing(bool newFlag);

				/* Operators */
				//Pack a C8 to the Stream
				FINLINE friend Stream& operator<<(Stream &s, C8 &v);
				//Pack a U8 to the Stream
				FINLINE friend Stream& operator<<(Stream &s, U8 &v);
				//Pack a S8 to the Stream
				FINLINE friend Stream& operator<<(Stream &s, S8 &v);
				//Pack a U16 to the Stream
				FINLINE friend Stream& operator<<(Stream &s, U16 &v);
				//Pack a S16 to the Stream
				FINLINE friend Stream& operator<<(Stream &s, S16 &v);
				//Pack a U32 to the Stream
				FINLINE friend Stream& operator<<(Stream &s, U32 &v);
				//Pack a S32 to the Stream
				FINLINE friend Stream& operator<<(Stream &s, S32 &v);
				//Pack a boolean to the Stream
				FINLINE friend Stream& operator<<(Stream &s, bool &v);
				//Pack a F32 to the Stream
				FINLINE friend Stream& operator<<(Stream &s, F32 &v);
				//Pack a U64 to the Stream
				FINLINE friend Stream& operator<<(Stream &s, U64 &v);
				//Pack a S64 to the Stream
				FINLINE friend Stream& operator<<(Stream &s, S64 &v);
				//Pack a F64 to the Stream
				FINLINE friend Stream& operator<<(Stream &s, F64 &v);
				//Pack a String to the Stream
				FINLINE friend Stream& operator<<(Stream &s, String &v);

				/* Public Class Members */
				//The maximum amount of data we can store on this stream
				S64 maxSize;
				//Are we using this stream to save data?
				bool strIsSaving;
				//If we're saving, do we save to persistent storage (Write to drives?)
				bool shouldSaveToPersistent;
				//Are we using this stream to load data?
				bool strIsLoading;
				//Should we force byte swapping even if it's not necessarily needed?
				bool shouldSwapBytesAlways;
				//Is there an error in the stream?
				bool hasError;
				//Is there a high-level error that should result in this stream being deleted?
				bool hasCError;

			protected:
				/* Protected Class Methods */
				//Reset the Stream
				void reset();

			private:
				/* Private Class Methods */
				//Copy all flags and statuses to this stream
				void copyMembersToStream(const Stream &from);

		};

	};

};

#endif