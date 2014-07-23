/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* fileStream.cpp
*
* Defines the Galactic Engine File Stream Class
**/

#include "fileStream.h"

namespace Galactic {

	namespace Core {
		
		namespace Streams {

			FileStream::FileStream() {
				init();
			}

			FileStream::~FileStream() {
				close();
			}

			bool FileStream::hasRights(const Rights r) const {
				return (accRights & U32(r)) != 0;
			}

			U64 FileStream::getPosition() const {
				if (accRights == 0) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::getPosition(): File Stream is not open.");
					return -1;
				}
				return ((bufferBegin != MaxBufferOffset) ? bufferPos : file->getPosition());
			}

			bool FileStream::setPosition(const U64 newPos) {
				if (accRights == 0) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::setPosition(): File Stream is not open.");
					return false;
				}
				if (!hasRights(CanMovePos)) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::setPosition(): File Stream does not have permission to adjust position.");
					return false;
				}
				//Check to ensure we're not breaking the stream bounds
				if ((bufferBegin != MaxBufferOffset) && (newPos >= bufferBegin) && (newPos <= bufferEnd)) {
					bufferPos = newPos;
					/*
					If the stream already has an End flag on it and we adjust the position and then perform an operation right after this call,
					you'll incorrectly get an EOS flag, so let's take care of that.
					*/
					if (bufferPos < bufferEnd) {
						Stream::setStatus(OK);
					}
					return true;
				}
				else {
					//We're outside the bounds, so let's make sure we can properly use this position
					if (dirty) {
						flushStream();
					}
					emptyBuffer();
					file->setPosition(newPos, File::Begin);
					setStatus();
					//Check if we're at the EOF
					if (file->getStatus() & File::EndOfFile) {
						isEOF = true;
					}
					return ((getStatus() & OK) || (getStatus() & End));
				}
			}

			U64 FileStream::getSize() {
				if (accRights == 0) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::getSize(): File Stream is not open.");
					return NULL; //NULL is defined as 0, this should work.
				}
				if (!((bufferBegin == MaxBufferOffset && dirty) || !dirty)) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::getSize(): File Stream must be valid if it's dirty to obtain the size.");
					return NULL; //NULL is defined as 0, this should work.
				}
				//Obtain...
				if (dirty) {
					return gMax(file->getSize(), bufferEnd + 1);
				}
				else {
					return file->getSize();
				}
			}

			FileStream *FileStream::initialize(strRef filePath, File::FileAccessMode acc) {
				FileStream *fS = new FileStream();
				if (fS) {
					bool success = fS->open(filePath, acc);
					if (!success) {
						SendToHell(fS);
					}
				}
				return fS;
			}

			bool FileStream::open(strRef filePath, File::FileAccessMode acc) {
				if (accRights != 0) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::open(): File Stream is already open.");
					return false; 
				}
				if (filePath.empty()) {
					GC_Error("FileStream::open(): File name is empty.");
					return false;
				}
				//Empty any existing data
				emptyBuffer();
				FilePath p(filePath);
				//Make sure the path exists if we're writing
				if (acc == File::Write || acc == File::Append || acc == File::ReadWrite) {
					createPath(p);
				}
				file = openFile(p, acc);
				if (!file.null()) {
					setStatus();
					switch (acc) {
						//Read
						case File::Read:
							accRights = U32(CanRead) | U32(CanMovePos);
							break;
						//Write & Append
						case File::Write:
						case File::Append:
							accRights = U32(CanWrite) | U32(CanMovePos);
							break;
						//Read-Write
						case File::ReadWrite:
							accRights = U32(CanRead) | U32(CanWrite) | U32(CanMovePos);
							break;
						//Error?
						default:
							GC_Error("FileStream::open(): Bad Access Mode on Target %s.", filePath.c_str());
							Stream::setStatus(IOERR);
							return false;
					}
				}
				else {
					GC_Error("FileStream::open(): Failed to open file %s.", filePath.c_str());
					Stream::setStatus(IOERR);
					return false;
				}
				return (getStatus() == OK);
			}

			void FileStream::close() {
				if (getStatus() == Closed) {
					//Already closed, kill...
					return;
				}
				if (!file.null()) {
					if (dirty) {
						//Empty the stream before closing.
						flushStream();
					}
					file->closeFile();
					if (file->getStatus() != File::Closed) {
						GC_Error("FileStream::close(): Failed to close file.");
					}
					file = NULL;
				}
				//And reset everything...
				init();
			}

			bool FileStream::flushStream() {
				if (accRights == 0) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::flushStream(): File Stream is not open.");
					return false; 
				}
				if (!((bufferBegin == MaxBufferOffset && dirty) || !dirty)) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::flushStream(): File Stream must be valid if it's dirty to flush the contents.");
					return false;
				}
				//Only need to flush dirty streams
				if (dirty) {
					if (!hasRights(CanWrite)) {
						//This one's just magical...
						Stream::setStatus(INVOP);
						GC_Error("FileStream::flushStream(): Cannot flush contents of a stream without write capabilities, that would just be magical.");
						return false;
					}
				}
				return true;
			}

			void FileStream::init() {
				accRights = 0;
				emptyBuffer();
				Stream::setStatus(Closed);
			}

			bool FileStream::fillBuffer(const U64 startPos) {
				if (accRights == 0) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::fillBuffer(): File Stream is not open.");
					return false;
				}
				if (dirty) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::fillBuffer(): File Stream must be clear to fill the buffer.");
					return false;
				}
				//Make sure the start position matches up with the file position
				if (startPos != file->getPosition()) {
					file->setPosition(startPos, File::Begin);
					//Now, we need to ensure we have proper file rights, check the status
					if (file->getStatus() != File::Open && file->getStatus() != File::EndOfFile) {
						setStatus();
						return false;
					}
					else {
						bufferPos = startPos;
					}
				}
				//Now that the stream and file positions match, check to see if the stream is in a valid spot.
				if (getStatus() == End) {
					//Not valid...
					bufferBegin = MaxBufferOffset;
					isEOF = true;
				}
				else {
					//Valid, so let's get what we need for block writting
					U64 blockBegin, amountRead;
					calcBuffBegin(bufferPos, &blockBegin);
					amountRead = file->read((UTF8)buffer + (startPos + bufferBegin), BufferSize - (startPos - bufferBegin));
					setStatus();
					//Check stream status
					if (getStatus() == OK || getStatus() == End) {
						//Update positions
						bufferBegin = startPos;
						bufferPos = startPos;
						bufferEnd = startPos + amountRead - 1;
						//If we hit the end of the stream, reset the status accordingly
						if (amountRead != 0 && getStatus() == End) {
							Stream::setStatus(OK);
							isEOF = true;
						}
					}
					else {
						//Something went wrong, invalidate the stream
						bufferBegin = MaxBufferOffset;
						return false;
					}
				}
				return true;
			}

			void FileStream::emptyBuffer() {
				bufferBegin = MaxBufferOffset;
				bufferPos = 0;
				bufferEnd = 0;
				dirty = false;
				isEOF = false;
			}

			void FileStream::setStatus() {
				switch (file->getStatus()) {
					//Open -> Open ( Obvious ;) )
					case File::Open:
						Stream::setStatus(OK);
						break;

					//Closed -> Closed ( Obvious, Again... ;) )
					case File::Closed:
						Stream::setStatus(Closed);
						break;

					//EOF = EOS
					case File::EndOfFile:
						Stream::setStatus(End);
						break;

					//This large list of file invalidations translates to a Stream IOError.
					case File::AccessDenied:
					case File::FileSystemFull:
					case File::NoSuchFile:
					case File::SharingViolation:
						Stream::setStatus(IOERR);
						break;

					//Illegal File Operation
					case File::IllegalCall:
						Stream::setStatus(INVOP);
						break;

					//Unknown Error Occured
					case File::UnknownError:
						Stream::setStatus(Unknown);
						break;

					//Something went wrong...
					default:
						GC_Error("FileStream::setStatus(): Unknown file status sent to this method.");
						break;
				}
			}

			void FileStream::calcBuffBegin(const U64 pos, U64 *buffBeginPtr) {
				if (!buffBeginPtr) {
					GC_Error("FileStream::calcBuffBegin(%i, [X]): NULL Pointer Argument sent to this method, breaking.", pos);
					return;
				}
				*buffBeginPtr = (pos / BufferSize) * BufferSize;
			}
			
			void FileStream::calcBuffBounds(const U64 pos, U64 *buffBeginPtr, U64 *buffEndPtr) {
				if (!buffBeginPtr) {
					GC_Error("FileStream::calcBuffBounds(%i, [X], X): NULL Pointer Argument sent to this method, breaking.", pos);
					return;
				}
				if (!buffEndPtr) {
					GC_Error("FileStream::calcBuffBounds(%i, X, [X]): NULL Pointer Argument sent to this method, breaking.", pos);
					return;
				}
				*buffBeginPtr = (pos / BufferSize) * BufferSize;
				*buffEndPtr = *buffBeginPtr + BufferSize - 1;
			}

			bool FileStream::__read(any outBuff, const U64 bytes) {
				if (accRights == 0) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::__read(): File Stream is not open.");
					return false;
				}
				if (!outBuff || bytes == 0) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::__read(): NULL Pointer or 0 bytes to read sent to function.");
					return false;
				}
				if (!hasRights(CanRead)) {
					//Trying to use __Read with no read permissions? I think not!
					Stream::setStatus(INVOP);
					GC_Error("FileStream::__read(): Cannot perform read operation on a stream without read permissions.");
					return false;
				}
				//If there's a prior status, exit.
				if (getStatus() != OK) {
					GC_Warn("FileStream::__read(): Prior status detected on FileStream, exiting.");
					return false;
				}
				if (bytes != 0) {
					UTX8 tmpBuf = (UTX8)outBuff;
					//Store numerical values. [0] = amountRead, [1] = amountRemaining, [2] = bytesRead, [3] = blockFront, [4] = blockEnd
					U64 tmpVls[5] = {0, bytes, 0, 0, 0};
					if (bufferBegin != MaxBufferOffset) {
						//Perform the initial buffer copy operation
						tmpVls[0] = ((bufferEnd + 1) >= bufferPos) ? (bufferEnd + 1 - bufferPos) : 0;
						tmpVls[0] = gMin(tmpVls[0], tmpVls[1]);
						calcBuffBegin(bufferPos, &tmpVls[3]);
						memcpy(tmpBuf, buffer + (bufferPos - tmpVls[3]), (size_t)tmpVls[0]);
						//Continue...
						tmpVls[1] -= tmpVls[0];
						bufferPos += tmpVls[0];
						tmpBuf += tmpVls[0];
						//Check for remaining...
						if (bufferPos > bufferEnd && tmpVls[1] > 0) {
							flushStream();
							bufferBegin = MaxBufferOffset;
							if (isEOF) {
								Stream::setStatus(End);
							}
						}
					}
					//What if there's still more data left and the request wasn't complete?
					if (!isEOF && tmpVls[1] > 0) {
						if (dirty) {
							flushStream();
						}
						//Reset the position,and continue the read operation.
						bufferPos = file->getPosition();
						calcBuffBounds(bufferPos, &tmpVls[3], &tmpVls[4]);
						if ((bufferPos + tmpVls[1]) <= tmpVls[4]) {
							if (fillBuffer(bufferPos)) {
								tmpVls[1] = gMin(tmpVls[1], bufferEnd - bufferPos + 1);
								memcpy(tmpBuf, buffer + (bufferPos - tmpVls[3]), (size_t)tmpVls[1]);
								bufferPos += tmpVls[1];
							}
							else {
								return false;
							}
						}
						else {
							//The remaining content spans multiple blocks, so just clean everything out and use File::Read instead.
							emptyBuffer();
							tmpVls[2] = file->read((UTF8)tmpBuf, tmpVls[1]);
							setStatus();
							if (getStatus() == OK || getStatus() == End) {
								//Did we perform any reading?
								if (tmpVls[2] != 0 && getStatus() == End) {
									Stream::setStatus(OK);
									isEOF = true;
								}
							}
							else {
								return false;
							}
						}
					}
				}
				return true;
			}

			bool FileStream::__write(cAny inBuff, const U64 bytes) {
				if (accRights == 0) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::__write(): File Stream is not open.");
					return false;
				}
				if (!inBuff || bytes == 0) {
					Stream::setStatus(INVOP);
					GC_Error("FileStream::__write(): NULL Pointer or 0 bytes to read sent to function.");
					return false;
				}
				if (!hasRights(CanRead)) {
					//Trying to use __Read with no read permissions? I think not!
					Stream::setStatus(INVOP);
					GC_Error("FileStream::__write(): Cannot perform write operation on a stream without write permissions.");
					return false;
				}
				//If there's a prior status, exit.
				if (getStatus() != OK && getStatus() != End) {
					GC_Warn("FileStream::__write(): Prior status detected on FileStream, exiting.");
					return false;
				}
				if (bytes != 0) {
					UTX8 tmpBuf = (UTX8)inBuff;
					//Store numerical values. [0] = writeSize, [1] = amountRemaining, [2] = bytesWritten, [3] = blockFront, [4] = blockEnd
					U64 tmpVls[5] = { 0, bytes, 0, 0, 0 };
					if (bufferBegin != MaxBufferOffset) {
						calcBuffBounds(bufferBegin, &tmpVls[3], &tmpVls[4]);
						tmpVls[0] = (bufferPos > tmpVls[4]) ? 0 : tmpVls[4] - bufferPos + 1;
						tmpVls[0] = gMin(tmpVls[0], tmpVls[1]);
						//Check our parameters before writting
						if (tmpVls[0] == 0 || (bufferPos - tmpVls[3]) > MaxBufferOffset) {
							::Galactic::Console::warn("FileStream::__write(): Cannot write to the specified position.");
							return false;
						}
						memcpy(buffer + (bufferPos - tmpVls[3]), tmpBuf, (size_t)tmpVls[0]);
						tmpVls[1] -= tmpVls[0];
						bufferPos += tmpVls[0];
						bufferEnd = gMax(bufferEnd, bufferPos - 1);
						tmpBuf += tmpVls[0];
						if (tmpVls[0] > 0) {
							dirty = true;
						}
					}
					//Anything left?
					if (tmpVls[1] > 0) {
						if (dirty) {
							flushStream();
						}
						bufferPos = file->getPosition();
						calcBuffBounds(bufferPos, &tmpVls[3], &tmpVls[4]);
						//Check if the operation needs one more block or multiple blocks.
						if ((bufferPos + tmpVls[1]) <= tmpVls[4]) {
							memcpy(buffer + (bufferPos - tmpVls[3]), tmpBuf, (size_t)tmpVls[1]);
							bufferBegin = bufferPos;
							bufferPos += tmpVls[1];
							bufferEnd = bufferPos - 1;
							dirty = true;
						}
						else {
							emptyBuffer();
							tmpVls[2] = file->write((UTF8)tmpBuf, tmpVls[1]);
							setStatus();
							return (getStatus() == OK || getStatus() == End);
						}
					}
				}
				return true;
			}

		};

	};

};