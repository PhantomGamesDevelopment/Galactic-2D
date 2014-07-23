/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* stream.h
*
* Defines the Galactic Engine Stream Base Class
**/

#ifndef GALACTIC_INTERNAL_STREAM
#define GALACTIC_INTERNAL_STREAM

#include "../engineCore.h"
#include "../Tools/color.h"
#include "../../Net/NetMain.h"
#include "../endian.h"

namespace Galactic {

	namespace Core {
		
		namespace Streams {

			/*
			Stream: A basic class for streaming various different forms of data across any specific
			media, Ex: Transmit between two connections, transmit to a file, etc.
			*/
			class Stream {
				public:
					//Stream Status Flags
					enum Status {
						// 0: Stream operations are running fine
						OK = 0,
						// 1: End of Stream Reached, Used by __read()
						End = 1,
						// 2: Stream is closed
						Closed = 2,
						// 3: IO Error occured on the Stream
						IOERR = 3,
						// 4: Invalid Operation Called on the Stream
						INVOP = 4,
						// 5: Unknown Error Occured
						Unknown = 5,
					};

					//Stream Operation Rights (Mainly used by the FileStream)
					enum Rights {
						// 0: Stream has Write Capabilities
						CanWrite = 0,
						// 1: Stream has Read Capabilities
						CanRead = 1,
						// 2: Stream may move Positions
						CanMovePos = 2,
					};

					/* Stream Methods */
					//Standard Constructor for the Stream class.
					Stream();
					//Destructor can be overloaded by the various stream types, therefore, virtual.
					virtual ~Stream() {} 

					//Get the status of the Stream
					Status getStatus() const;
					//Validate if the Stream has certain access
					virtual bool hasRights(const Rights r) const = 0;
					//Obtain the current stream position
					virtual U64 getPosition() const = 0;
					//Set the current stream position
					virtual bool setPosition(const U64 newPos) = 0;
					//Get the size of the stream
					virtual U64 getSize() = 0;
					//Read a single line from the Stream (/r/n termination)
					void readLine(UTX8 buffer, U64 size);
					//Write a single line to the Stream
					void writeLine(UTX16 buffer);
					//Read a character string of up to 255 characters
					virtual void readString(C8 strBuff[256]);
					//Read a String of up to a defined length (use this method when a string length is unknown and can go over 255)
					void readString(U64 length, UTF8 strBuff);
					//Write a String of adefined length to the buffer
					virtual void writeString(UTF16 strBuff, U64 length);
					//Write a line of text to the Stream (/r/n termination)
					void writeLine(UTF16 strBuff);

					/* Individual Read / Write Operations 
					   This is where we define the read and write functions for the individual
					   data types that are in the engine. We do things this way to ensure 
					   we write the correct size and values every time, and to ensure that
					   endian conversions are met. */

					//Overloads for our two protected member functions
					//Write to the buffer
					bool write(cAny inBuff, const U64 bytes) {
						return __write(inBuff, bytes);
					}
					//Read from the buffer
					bool read(any outBuff, const U64 bytes) {
						return __read(outBuff, bytes);
					}

					//Methods for all of the needed data types.
					//Write a bool to the Stream
					bool write(const bool &b);
					//Read a bool from the Stream
					bool read(bool *b);
					//Write a String to the Stream
					bool write(strRef str);
					//Read a String from the Stream
					bool read(String *str);
					//Write a ColorI to the Stream
					bool write(const ColorI &c);
					//Read a ColorI from the Stream
					bool read(ColorI *c);
					//Write a ColorF to the Stream
					bool write(const ColorF &c);
					//Read a ColorF from the Stream
					bool read(ColorF *c);
					//Write a NetAddress to the Stream
					bool write(const ENetAddress &addr);
					//Read a NetAddress from the Stream
					bool read(ENetAddress *addr);
					//Write a S8 to the Stream
					bool write(S8 w);
					//Read a S8 from the Stream
					bool read(S8 *r);
					//Write a U8 to the Stream
					bool write(U8 w);
					//Read a U8 from the Stream
					bool read(U8 *r);
					//Write a S16 to the Stream
					bool write(S16 w);
					//Read a S16 from the Stream
					bool read(S16 *r);
					//Write a U16 to the Stream
					bool write(U16 w);
					//Read a U16 from the Stream
					bool read(U16 *r);
					//Write a S32 to the Stream
					bool write(S32 w);
					//Read a S32 from the Stream
					bool read(S32 *r);
					//Write a U32 to the Stream
					bool write(U32 w);
					//Read a U32 from the Stream
					bool read(U32 *r);
					//Write a F32 to the Stream
					bool write(F32 w);
					//Read a F32 from the Stream
					bool read(F32 *r);
					//Write a S64 to the Stream
					bool write(S64 w);
					//Read a S64 from the Stream
					bool read(S64 *r);
					//Write a U64 to the Stream
					bool write(U64 w);
					//Read a U64 from the Stream
					bool read(U64 *r);
					//Write a F64 to the Stream
					bool write(F64 w);
					//Read a F64 from the Stream
					bool read(F64 *r);

				protected:
					//Set the status of the Stream
					void setStatus(Status s);
					//Same, const level access.
					void setStatus(Status s) const;

					/* Protected stream methods (Read / Write) */
					// Read from a buffer
					virtual bool __read(any outBuff, const U64 bytes) = 0;
					// Write to a buffer
					virtual bool __write(cAny inBuff, const U64 bytes) = 0;
					//Strings are special, and therefore we give them their own method
					// Read a String
					virtual void __read(String *str);
					// Write a String
					virtual void __write(strRef str);

				private:
					/* 
					Current status of the Stream 
					(Update 6-26: had to set this to mutable due to FileStream getPosition() method needing setStatus as a const call.)
					*/
					mutable Status streamStatus;	
			};

		};

	};

};

#endif //GALACTIC_INTERNAL_STREAM