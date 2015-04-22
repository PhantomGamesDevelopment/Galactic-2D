/**
* Galactic 2D
* Source/EngineCore/Stream/bitStream.cpp
* Definitions for the BitStream class
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

#include "bitStream.h"

namespace Galactic {

	namespace Core {
		
		namespace Streams {
			/*
			BitStream
			*/

			//Packet Transmission Bitstream
			static BitStream G_TransStream(NULL, 0);
			static U8 G_PacketBuffer[::Galactic::Network::MaxPacketDataSize];

			BitStream::BitStream(any bufData, S64 bufSize, S64 maxSize) {
				setBuffer(bufData, bufSize, maxSize);
				strData = NULL;
			}

			void BitStream::setBuffer(any bufData, S64 bufSize, S64 maxSize) {
				if(maxSize < 0) {
					maxSize = bufSize;
				}
				data = (UTX8)bufData;
				bitNumber = 0;
				bufferSize = bufSize;
				maxReadAmount = (bufSize << BuffSizeShift);
				maxWriteAmount = (maxSize << BuffSizeShift);
				errorFlag = false;
			}

			UTX8 BitStream::getBuffer() {
				return data;
			}

			UTX8 BitStream::getByteBuffer() {
				return data + getPosition();
			}

			S64 BitStream::getCurrentPos() const {
				return bitNumber;
			}

			void BitStream::setCurrentPos(U64 newPos) {
				if (newPos > ((U64)(bufferSize << BuffSizeShift))) {
					if(GALACTIC_DONT_REPORT_INTERNAL_ERRORS != 0) {
						Galactic::Console::error("BitStream::setCurrentPos(%i): Requested position is outside of the range of this BitStream.", newPos);
					}
					return;
				}
				bitNumber = S64(newPos);
			}

			U64 BitStream::getReadBytes() {
				return (maxReadAmount >> BuffSizeShift) - getPosition();
			}

			U64 BitStream::getWriteBytes() {
				return (maxWriteAmount >> BuffSizeShift) - getPosition();
			}

			void BitStream::emptyStringBuffer() {
				//Overload the class with an array instance.
				static C8 strData[256];
				strData[0] = NULL;
			}

			void BitStream::clear() {
				memset(data, NULL, (size_t)bufferSize);
			}

			bool BitStream::hasRights(const Rights r) const {
				//BitStreams are not interfering with system files / memory, therefore all rights are granted.
				return true;
			}

			U64 BitStream::getPosition() const {
				return (bitNumber + 0x7) >> BuffSizeShift;
			}

			bool BitStream::setPosition(const U64 newPos) {
				bitNumber = (newPos << BuffSizeShift);
				return true;
			}

			U64 BitStream::getSize() {
				return bufferSize;
			}

			bool BitStream::__write(cAny inBuff, const U64 bytes) {
				writeBits(inBuff, (bytes << BuffSizeShift));
				return true;
			}

			bool BitStream::__read(any outBuff, const U64 bytes) {
				readBits(outBuff, (bytes << BuffSizeShift));
				return true;
			}

			void BitStream::writeS32(S32 value, S64 bitCount) {
				if((bitCount != 32) || ((value >> bitCount) != 0)) {
					if(GALACTIC_DONT_REPORT_INTERNAL_ERRORS != 0) {
						Galactic::Console::warn("BitStream::writeS32(%i, %i): The requested value [%i] is out of range of the bitcount [%i], this may cause some precision errors.", value, bitCount, value, bitCount);
					}
				}
				value = convertSrcToLittleEndian(value);
				writeBits(&value, bitCount);
			}

			S32 BitStream::readS32(S64 bitCount) {
				S32 readValue = 0;
				readBits(&readValue, bitCount);
				readValue = convertLittleEndianToSrc(readValue);
				//If we have a non 32-bit value, shift the bits to back out the original value
				if(bitCount != 32) {
					readValue &= BackBitShift(bitCount);
				}
				return readValue;
			}

			void BitStream::writeSignedS32(S32 value, S64 bitCount) {
				if(writeFlag((value < 0))) {
					writeS32((-value), bitCount-1);	
				}
				else {
					writeS32(value, bitCount-1);
				}
			}

			S32 BitStream::readSignedS32(S64 bitCount) {
				if(readFlag()) {
					return -readS32(bitCount-1);
				}
				return readS32(bitCount-1);
			}

			void BitStream::writeF32(F32 value, S64 bitCount) {
				writeS32((S32)(value * (BackBitShift(bitCount))), bitCount);
			}

			F32 BitStream::readF32(S64 bitCount) {
				return (readS32(bitCount) / F32(BackBitShift(bitCount)));
			}

			void BitStream::writeSignedF32(F32 value, S64 bitCount) {
				//We use multiply by 0.5 here to keep the floating point precision on the value.
				S32 writeVal = S32(((value + 1) * 0.5) * (BackBitShift(bitCount)));
				writeS32(writeVal, bitCount);
			}

			F32 BitStream::readSignedF32(S64 bitCount) {
				return ((readS32(bitCount) * 2) / F32(BackBitShift(bitCount)) - 1.0f);
			}

			void BitStream::writeVector(const Math::Vector2F &v, S64 bitCount) {
				writeSignedF32(v.x, bitCount);
				writeSignedF32(v.y, bitCount);
			}

			void BitStream::readVector(Math::Vector2F *v, S64 bitCount) {
				v->x = readSignedF32(bitCount);
				v->y = readSignedF32(bitCount);
			}

			void BitStream::writeBits(cAny writeBuff, S64 bitCount) {
				if(bitCount <= 0) {
					if(GALACTIC_DONT_REPORT_INTERNAL_ERRORS != 0) {
						Galactic::Console::error("BitStream::writeBits(x, %i): Cannot write a bitcount that is less than or equal to 0", bitCount);
					}
					return;
				}
				if((bitNumber + bitCount) > maxWriteAmount) {
					Galactic::Console::cerr("BitStream::writeBits(x, %i): The attempted write operation is accessing memory outside of range, halting and throwing exception.", bitCount);
					errorFlag = true;
					//ToDo: Throw an assert error here
					return; //I know this return is redundant, but we want to dead-stop here, no memory violations please...
				}
				//Convert the buffer to a writable format
				UTX16 bitBuffer = (UTX8)writeBuff;
				//Write each bit to the Stream, Recall that bitNumber contains the bit position, not the Byte position.
				for(S32 i = 0; i < bitCount; i++) {
					//First Compare the bits of the write buffer to that of the index we're writing, If they don't match, we need to flip the BITOR Bits in our stream
					if((*(bitBuffer + (i >> BuffSizeShift)) & (BuffRWShift << (i & 0x7))) != 0) {
						*(data + (bitNumber >> BuffSizeShift)) |= (BuffRWShift << (i & 0x7));
					}
					//Otherwise, we need to apply a BITAND Relation of the UNARY relation of the index shift
					else {
						*(data + (bitNumber >> BuffSizeShift)) &= ~(BuffRWShift << (i & 0x7));
					}
					//Increment our Stream value
					bitNumber++;
				}
			}

			void BitStream::readBits(any readBuff, S64 bitCount) {
				if(bitCount <= 0) {
					if(GALACTIC_DONT_REPORT_INTERNAL_ERRORS != 0) {
						Galactic::Console::error("BitStream::readBits(x, %i): Cannot read a bitcount that is less than or equal to 0", bitCount);
					}
					return;
				}
				if((bitNumber + bitCount) > maxReadAmount) {
					Galactic::Console::cerr("BitStream::readBits(x, %i): The attempted read operation is accessing memory outside of range, halting and throwing exception.", bitCount);
					errorFlag = true;
					//ToDo: Throw an assert error here
					return; //I know this return is redundant, but we want to dead-stop here, no memory violations please...
				}
				//Define our Starting Point & end Point
				UTX8 startingPtr = data + (bitNumber >> BuffSizeShift), bitBuffer = (UTX8)readBuff;
				UTX16 endPtr = data + bufferSize;
				//Ok, so for you people who are a little 'uneducated' in binary, here's how this works:
				// We add 7 to the bit count to fill a single "Byte" with binary values: (7 = 0111).
				// That number is then shifted by the size allocation for the byte in our Stream, which is defined in the header.
				S64 numBytes = (bitCount + 7) >> BuffSizeShift;
				//Define the points for a single shift up and down, 0x7 == 7. 
				S64 upShift = (8 - (bitNumber & 0x7)), downShift = (bitNumber & 0x7);
				//Get the current byte into a field
				U8 currentByte = *startingPtr, nextByte = 0;
				//Run through the Stream, read in the values we need into bitBuffer
				while(numBytes--) {
					startingPtr++;
					nextByte = startingPtr < endPtr ? *startingPtr : 0;
					*bitBuffer++ = (currentByte >> downShift) | (nextByte << upShift);
					currentByte = nextByte;
				}
				//Increment the bit position
				bitNumber += bitCount;
			}

			bool BitStream::writeFlag(bool val) {
				//Recall from stream.cpp, that booleans have different size values based
				// on the compiler, therefore we compress it to a static size.
				if((bitNumber + 1) > maxWriteAmount) {
					Galactic::Console::cerr("BitStream::writeFlag(%i): The attempted write operation is accessing memory outside of range, halting and throwing exception.", val == true ? 1 : 0);
					errorFlag = true;
					//ToDo: Throw an assert error here
					return false; //I know this return is redundant, but we want to dead-stop here, no memory violations please...
				}
				//see writeBits for these two statements. Writing a compressed 1 bit boolean takes on the same logic.
				// If the boolean is true, use a BITOR Shift, otherwise, use a BITAND against the UNARY Shift
				if(val) {
					*(data + (bitNumber >> BuffSizeShift)) |= (BuffRWShift << (bitNumber & 0x7));
				}
				else {
					*(data + (bitNumber >> BuffSizeShift)) &= ~(BuffRWShift << (bitNumber & 0x7));
				}
				//Add one to the BitNumber
				bitNumber++;
				//Return
				return val;
			}

			bool BitStream::writeFlag(any val) {
				return writeFlag(val != 0);
			}

			bool BitStream::readFlag() {
				if((bitNumber) > maxReadAmount) {
					Galactic::Console::cerr("BitStream::readFlag(): The attempted read operation is accessing memory outside of range, halting and throwing exception.");
					errorFlag = true;
					//ToDo: Throw an assert error here
					return false; //I know this return is redundant, but we want to dead-stop here, no memory violations please...
				}			
				S32 bitShift = BuffRWShift << (bitNumber & 0x7);
				bool value = (*(data + (bitNumber >> BuffSizeShift)) & bitShift) != 0;
				bitNumber++;
				return value;
			}

			void BitStream::writeString(UTF16 stringBuff, S32 maxLen) {
				if(!stringBuff) {
					stringBuff = "";
				}
				//Test for compressability.
				if(strData) {
					S32 buffLen;
					//Fetch the buffer length
					for(buffLen = 0; buffLen < maxLen && strData[buffLen] == stringBuff[buffLen] && stringBuff[buffLen]; buffLen++);
					//Apply the new buffer
					strncpy(strData, stringBuff, maxLen);
					strData[maxLen] = NULL;
					if(writeFlag(buffLen > 2)) {
						writeS32(buffLen, 8);
						HuffCoder::G_HuffCoder.compressStringToBitStream(stringBuff + buffLen, this, maxLen - buffLen);
						return;
					}
				}
				HuffCoder::G_HuffCoder.compressStringToBitStream(stringBuff, this, maxLen);
			}

			void BitStream::readString(C8 stringBuff[256]) {
				if(strData) {
					if(readFlag()) {
						S32 bufferLen = readS32(8);
						HuffCoder::G_HuffCoder.decompressStringFromBitStream(strData + bufferLen, this);
						strcpy(stringBuff, strData);
						return;
					}
				}
				HuffCoder::G_HuffCoder.decompressStringFromBitStream(stringBuff, this);
				if(strData) {
					strcpy(strData, stringBuff);
				}
			}

			bool BitStream::isFull() {
				return bitNumber > (bufferSize << BuffSizeShift);
			}

			bool BitStream::isValid() {
				return !errorFlag;
			}

			BitStream *BitStream::getTransmissionStream(U64 writeSize) {
				if(!writeSize) {
					writeSize = ::Galactic::Network::MaxPacketDataSize;
				}
				G_TransStream.setBuffer(G_PacketBuffer, writeSize, ::Galactic::Network::MaxPacketDataSize);
				G_TransStream.setPosition(0);

				return &G_TransStream;
			}

			void BitStream::sendTransmissionStream(::Galactic::Network::NetConnection *conn) {
				conn->send(G_TransStream.getBuffer(), G_TransStream.getPosition(), false);
			}

			/*
			InfiniteBitStream
			*/
			
			InfiniteBitStream::InfiniteBitStream(U64 minSpace, U64 initialSize) : BitStream(NULL, 0, 0) {
				minimumSpace = minSpace;
				if(!initialSize) {
					initialSize = minSpace * 2;
				}
				//Allocate Space
				UTX8 buffer = (UTX8)malloc((size_t)initialSize);
				setBuffer(buffer, initialSize, initialSize);
			}

			InfiniteBitStream::~InfiniteBitStream() {
				SendToGatesOfHeaven(data);
			}

			void InfiniteBitStream::validate(U64 upcomingSpaceNeed) {
				if(getPosition() + upcomingSpaceNeed + minimumSpace > U32(bufferSize)) {
					bufferSize = getPosition() + upcomingSpaceNeed + minimumSpace;
					data = (UTX8)realloc(data, (size_t)bufferSize);
					maxReadAmount = bufferSize << BuffSizeShift;
					maxWriteAmount = bufferSize << BuffSizeShift;
				}
			}

			void InfiniteBitStream::emptyStream() {
				setPosition(0);
			}

			void InfiniteBitStream::compact() {
				U64 old = bufferSize;
				UTX8 ptr = (UTX8)malloc((size_t)bufferSize);
				//Copy written data, then clean out anything else.
				bufferSize = getPosition() + minimumSpace * 2;
				memcpy(ptr, data, (size_t)old);
				SendToGatesOfHeaven(data);
				data = ptr;
				maxReadAmount = bufferSize << BuffSizeShift;
				maxWriteAmount = bufferSize << BuffSizeShift;
			}

			void InfiniteBitStream::writetoStream(Stream &str) {
				str.write(data, getPosition());
			}

			void InfiniteBitStream::writeBits(cAny writeBuff, S64 bitCount) {
				validate((bitCount >> BuffSizeShift) + 1);
				BitStream::writeBits(writeBuff, bitCount);
			}

			bool InfiniteBitStream::writeFlag(bool val) {
				validate(1);
				return BitStream::writeFlag(val);
			}

		};

	};

};