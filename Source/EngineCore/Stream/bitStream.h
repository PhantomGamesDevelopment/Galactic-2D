/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* bitStream.h
*
* Defines the Galactic Engine Bit Stream Class
**/

#ifndef GALACTIC_INTERNAL_BITSTREAM
#define GALACTIC_INTERNAL_BITSTREAM

#include "stream.h"
#include "../../Net/NetConnection.h"
#include "../Tools/huffman.h"
#include "../Math/mVector.h"

namespace Galactic {

	namespace Core {

		//Forward Dec for the HuffCoder Class
		class HuffCoder;
		
		namespace Streams {

			/*
			BitStream: A Stream that compresses various forms of data into a single binary stream that can be safely transmitted
			 across the network, specifically between client and server instances.
			*/
			class BitStream : public Stream {

				/* 
				In numerous places we have to back out values where the BitCount doesn't match the bits used by the type. To safely back out
				 the original value, we use a left shift of the original BitCount wrote.
				*/ 
				#define BackBitShift(x) ((1 << x) - 1)

				public:
					/* Public Class Methods */
					// Default Constructor
					BitStream(any bufData, S64 bufSize, S64 maxSize = 0);
					// Set the Buffer
					void setBuffer(any bufData, S64 bufSize, S64 maxSize = 0);
					// Get the Buffer
					UTX8 getBuffer();
					// Get the Byte Buffer
					UTX8 getByteBuffer();
					// Get the current bit position in the Stream (Does not function in the same way as getPosition)
					S64 getCurrentPos() const;
					// Set the current bit position in the Stream (Does not function in the same way as setPosition)
					void setCurrentPos(U64 newPos);
					// Obtain the amount of read bytes
					U64 getReadBytes();
					// Obtain the amount of write bytes
					U64 getWriteBytes();
					// Empty the String Buffer
					void emptyStringBuffer();
					// Empty the BitStream
					void clear();
					/* Overrides For Stream Virtual Methods */
					// Check if the Stream has given access rights
					bool hasRights(const Rights r) const;
					// Get the current Byte Position
					U64 getPosition() const;
					// Set the current Byte Position
					bool setPosition(const U64 newPos);
					// Get the size of the Stream
					U64 getSize();
					// Generic Write function
					bool __write(cAny inBuff, const U64 bytes);
					// Generic Read function
					bool __read(any outBuff, const U64 bytes);
					/* Read / Write Methods */
					//Write S32
					void writeS32(S32 value, S64 bitCount);
					//Read S32
					S32 readS32(S64 bitCount);
					//Write Signed S32 (Grants Double S32 Range)
					void writeSignedS32(S32 value, S64 bitCount);
					//Read Signed S32
					S32 readSignedS32(S64 bitCount);
					//Write F32
					void writeF32(F32 value, S64 bitCount);
					//Read F32
					F32 readF32(S64 bitCount);
					//Write Signed F32 (Grants Double F32 Range)
					void writeSignedF32(F32 value, S64 bitCount);
					//Read Signed F32
					F32 readSignedF32(S64 bitCount);
					//Write Vector2
					void writeVector(const Math::Vector2F &v, S64 bitCount);
					//Read Vector2
					void readVector(Math::Vector2F *v, S64 bitCount);
					//Write Bits
					virtual void writeBits(cAny writeBuff, S64 bitCount);
					//Read Bits
					virtual void readBits(any readBuff, S64 bitCount);
					//Write Boolean (Flag)
					virtual bool writeFlag(bool val);
					//Write Flag Using Non-Boolean Value
					FINLINE bool writeFlag(any val);
					//Read Flag
					virtual bool readFlag();
					//Write String
					void writeString(UTF16 stringBuff, S32 maxLen = 255);
					//Read String
					void readString(C8 stringBuff[256]);
					/* A Few Extras */
					//Test if the Stream is full
					bool isFull();
					//Test for errors
					bool isValid();
					//Obtain the Packet Transmission BitStream
					static BitStream *getTransmissionStream(U64 writeSize = 0);
					//Send the Packet Transmission BitStream to a specified location
					static void sendTransmissionStream(::Galactic::Network::NetConnection *conn);

				protected:
					// Bit Shift Enumerations
					enum BitShifts {
						//Don't Touch Please, This is used to shift the size value (raise to power of three) to test maxima on the BitStream ends.
						BuffSizeShift = 3,
						//Same as above, this is used when writing and reading directly to the Stream
						BuffRWShift = 1,
					};
					/* Protected Data Values */
					// Pointer Containing The Data in the Stream
					UTX8 data;
					// Pointer Containing any String Buffers
					UTF8 strData;
					// Value of the current Bit Number in the Stream
					S64 bitNumber;
					// Size of the Buffer
					S64 bufferSize;
					// Maximum read amount
					S64 maxReadAmount;
					// Maximum write amount
					S64 maxWriteAmount;
					// Boolean to test if errors occured in the process
					bool errorFlag;
					//Apply the "friend" access level to HuffCoder to allow access to these fields
					friend class HuffCoder;
			};

			/*
			InfiniteBitStream: This is an extension of the existing BitStream class that allows you to create a Stream that constantly expands as
			 the needs of the memory exist.
			*/
			class InfiniteBitStream : public BitStream {
				public:
					//Default Constructor
					InfiniteBitStream(U64 minSpace = 1000, U64 initialSize = 0);
					//Destructor
					~InfiniteBitStream();
					//Validate the Stream for upcoming space needs
					void validate(U64 upcomingSpaceNeed);
					//Empty the stream, but don't remove the memory.
					void emptyStream();
					//Remove unused memory
					void compact();
					//Write the buffer of the Infinite Stream to a standard Stream
					void writetoStream(Stream &str);
					//Write Bits
					virtual void writeBits(cAny writeBuff, S64 bitCount);
					//Write Boolean (Flag)
					virtual bool writeFlag(bool val);
				protected:
					//Value containing the minimum space needed by this Stream
					U64 minimumSpace;
			};

		};

	};

};

#endif //GALACTIC_INTERNAL_BITSTREAM