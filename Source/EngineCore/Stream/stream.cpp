/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* stream.cpp
*
* Defines the Galactic Engine Stream Base Class
**/

#include "stream.h"

namespace Galactic {

	namespace Core {
		
		namespace Streams {

			Stream::Stream() : streamStatus(Closed) {

			}

			Stream::Status Stream::getStatus() const {
				return streamStatus;
			}

			void Stream::readLine(UTX8 buffer, U64 size) {
				size--; //Take out one for the NULL terminator
				
				UTX8 buffCopy = buffer;
				UTX8 buffEnd = buffCopy + size;
				*buffCopy = '\r';
				//Strip the White Space
				while(*buffCopy == '\r') {
					if(!read(buffCopy) || *buffCopy == '\n') {
						*buffCopy = NULL;
						return;
					}
				}
				//Read the line
				while(buffCopy != buffEnd && read(buffCopy++) && *buffCopy != '\n') {
					if(*buffCopy == '\r') {
						#ifdef GALACTIC_MACOS
							//Macs, adding onto their tally of why I hate them, have a lovely little habbit of having the NULL termination
							// sequence, override the '\r' values we're adding to make life easy, so we need to compensate for this.
							U32 testPos = getPosition();
							if(read(buffCopy)) {
								if(*buffCopy != '\n') {
									setPosition(testPos);
								}
							}
							break; 
						#else
							buffCopy--;
						#endif
					}
				}
				*buffCopy = NULL;
			}

			void Stream::writeLine(UTX16 buffer) {
				write(buffer, strlen((UTF16)buffer));
				write("\r\n", 2);
			}

			void Stream::readString(C8 strBuff[256]) {
				U8 readLen;
				read(&readLen);

				read(strBuff, (S32)readLen);
				strBuff[readLen] = NULL;
			}

			void Stream::readString(U64 length, UTF8 strBuff) {
				U64 readLen;
				read(&readLen);

				if(readLen > length) {
					//houston, we have a problem!
					streamStatus = IOERR;
					return;
				}
				read(strBuff, readLen);
				strBuff[readLen] = NULL; //Add NULL Terminator
			}

			void Stream::writeString(UTF16 writeBuff, U64 length) {
				U64 writeLen = strlen(writeBuff);
				if(writeLen > length) {
					writeLen = length;
				}
				//Write the length and the raw string data to the stream
				write(writeLen);
				write(writeBuff, writeLen);
			}

			void Stream::writeLine(UTF16 strBuff) {
				if(strBuff && strBuff[0]) {
					write(strBuff, strlen(strBuff));
				}
			}

			bool Stream::write(const bool &b) {
				//Booleans need to be transmitted as integers since they have varying sizes on different platforms
				U8 translatedBool = b ? U8(1) : U8(0);
				return write(translatedBool);
			}

			bool Stream::write(strRef str) {
				//Fork it off to __write located at the bottom of this file
				__write(str);
				return true;
			}
			
			bool Stream::read(String *str) {
				//Fork it off to __read located at the bottom of this file
				__read(str);
				return true;
			}

			bool Stream::read(bool *b) {
				U8 translatedBool;
				//Try to read the Stream
				bool readSuccess = read(&translatedBool);
				if(!readSuccess) {
					return false;
				}
				//Write the result to b
				*b = (translatedBool != 0);
				return true;
			}

			bool Stream::write(const ColorI &c) {
				//This one's easy, use a boolean to store the |= result of writing r, g, b, and a values and return the result.
				bool writeResult;

				writeResult = write(c.r);
				writeResult |= write(c.g);
				writeResult |= write(c.b);
				writeResult |= write(c.a);

				return writeResult;
			}

			bool Stream::read(ColorI *c) {
				//Same as above, only we're reading in color references.
				bool readResult;

				readResult = read(&c->r);
				readResult |= read(&c->g);
				readResult |= read(&c->b);
				readResult |= read(&c->a);

				return readResult;
			}

			bool Stream::write(const ColorF &c) {
				//ColorF transmits similarly to ColorI, so the write is easy
				bool writeResult;

				writeResult = write(c.r);
				writeResult |= write(c.g);
				writeResult |= write(c.b);
				writeResult |= write(c.a);

				return writeResult;
			}

			bool Stream::read(ColorF *c) {
				//Reading works the same way.
				bool readResult;

				readResult = read(&c->r);
				readResult |= read(&c->g);
				readResult |= read(&c->b);
				readResult |= read(&c->a);

				return readResult;
			}

			bool Stream::write(const ENetAddress &addr) {
				//NetAddress classes are easy, since it's just a U32 and a U16.
				bool writeResult;

				writeResult = write(addr.host);
				writeResult &= write(addr.port);

				return writeResult;
			}

			bool Stream::read(ENetAddress *addr) {
				//Reading a NetAddress is just reading a U32 and a U16.
				bool readResult;

				readResult = read(&addr->host);
				readResult &= read(&addr->port);

				return readResult;
			}

			/* 
			The next large group of methods here has to do with writting standard C++ types to the stream. They're all very similar in process
			 so large amounts of documentation is not necessary for these methods. Values with bit counts at or above 16 convert the result to
			 little endian for cross-platform compatibility.
			*/

			bool Stream::write(S8 w) {
				return write(&w, sizeof(S8));
			}

			bool Stream::read(S8 *r) {
				return read(r, sizeof(S8));
			}

			bool Stream::write(U8 w) {
				return write(&w, sizeof(U8));
			}

			bool Stream::read(U8 *r) {
				return read(r, sizeof(U8));
			}

			bool Stream::write(S16 w) {
				S16 endConv = convertSrcToLittleEndian(w);
				return write(&endConv, sizeof(S16));
			}

			bool Stream::read(S16 *r) {
				S16 endConv;
				bool readResult = read(&endConv, sizeof(S16));
				*r = convertLittleEndianToSrc(endConv);
				return readResult;
			}

			bool Stream::write(U16 w) {
				U16 endConv = convertSrcToLittleEndian(w);
				return write(&endConv, sizeof(U16));
			}

			bool Stream::read(U16 *r) {
				U16 endConv;
				bool readResult = read(&endConv, sizeof(U16));
				*r = convertLittleEndianToSrc(endConv);
				return readResult;
			}

			bool Stream::write(S32 w) {
				S32 endConv = convertSrcToLittleEndian(w);
				return write(&endConv, sizeof(S32));
			}

			bool Stream::read(S32 *r) {
				S32 endConv;
				bool readResult = read(&endConv, sizeof(S32));
				*r = convertLittleEndianToSrc(endConv);
				return readResult;
			}

			bool Stream::write(U32 w) {
				U32 endConv = convertSrcToLittleEndian(w);
				return write(&endConv, sizeof(U32));
			}

			bool Stream::read(U32 *r) {
				U32 endConv;
				bool readResult = read(&endConv, sizeof(U32));
				*r = convertLittleEndianToSrc(endConv);
				return readResult;
			}

			bool Stream::write(F32 w) {
				F32 endConv = convertSrcToLittleEndian(w);
				return write(&endConv, sizeof(F32));
			}

			bool Stream::read(F32 *r) {
				F32 endConv;
				bool readResult = read(&endConv, sizeof(F32));
				*r = convertLittleEndianToSrc(endConv);
				return readResult;
			}

			bool Stream::write(S64 w) {
				S64 endConv = convertSrcToLittleEndian(w);
				return write(&endConv, sizeof(S64));
			}

			bool Stream::read(S64 *r) {
				S64 endConv;
				bool readResult = read(&endConv, sizeof(S64));
				*r = convertLittleEndianToSrc(endConv);
				return readResult;
			}

			bool Stream::write(U64 w) {
				U64 endConv = convertSrcToLittleEndian(w);
				return write(&endConv, sizeof(U64));
			}

			bool Stream::read(U64 *r) {
				U64 endConv;
				bool readResult = read(&endConv, sizeof(U64));
				*r = convertLittleEndianToSrc(endConv);
				return readResult;
			}

			bool Stream::write(F64 w) {
				F64 endConv = convertSrcToLittleEndian(w);
				return write(&endConv, sizeof(F64));
			}

			bool Stream::read(F64 *r) {
				F64 endConv;
				bool readResult = read(&endConv, sizeof(F64));
				*r = convertLittleEndianToSrc(endConv);
				return readResult;
			}

			/*
			We have a few additional methods here at the end, mainly some asset operations.
			*/

			void Stream::setStatus(Status s) {
				streamStatus = s;
			}

			void Stream::setStatus(Status s) const {
				streamStatus = s;
			}

			void Stream::__write(strRef str) {
				U32 writeLen = str.length();
				if(writeLen < 256) {
					write(U8(writeLen));
				}
				else {
					write(U8(255));
					if(writeLen > (1 << 16)) {
						//ToDo: Throw an assert error here
					}
					//Set the correct length (16 bits) - 1 (NULL Termination) & write it.
					writeLen &= (1 << 16) - 1;
					write((U16)writeLen);
				}
				//Write the String
				write(str.c_str(), writeLen);
			}

			void Stream::__read(String *str) {
				//Recall that for "long" strings, we potentially send a U16 as well as the U8.
				U16 streamReadLength;
				U8 byteReadLength;
				//Read the byteReadLength.
				read(&byteReadLength);
				if(byteReadLength == 255) {
					//If this length is 255, then we need to read the streamLegnth
					read(&streamReadLength);
				}
				else {
					streamReadLength = byteReadLength;
				}
				//Allocate some memory for the String, then Read it.
				UTF8 strBuff = (UTF8)malloc(streamReadLength);
				read(strBuff, streamReadLength);
				*str = String(strBuff, streamReadLength);
				//Free the memory allocated by strBuff
				SendToGatesOfHeaven(strBuff);
			}

		};

	};

};