/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* fileStream.h
*
* Defines the Galactic Engine File Stream Class
**/

#ifndef GALACTIC_INTERNAL_FILESTREAM
#define GALACTIC_INTERNAL_FILESTREAM

#include "stream.h"
#include "../Files/files.h"

using namespace Galactic::Core::Files;

namespace Galactic {

	namespace Core {
		
		namespace Streams {

			/*
			FileStream: A Stream that allows access to reading and writting of files
			*/
			class FileStream : public Stream {
				public:
					/* Public Class Members */
					// File Stream Constants
					enum FileStreamConstants {
						//BufferSize: The size of the buffer, this could be anything (in K)
						BufferSize = 4096, 
						//MaxBufferOffset: The maximum offset a file stream operation may have, anything beyond this is invalid
						MaxBufferOffset = 0xffffffff,
					};

					/* Public Class Methods */
					//Default Constructor
					FileStream();
					//Destructor
					virtual ~FileStream();
					//Validate if the Stream has certain access
					virtual bool hasRights(const Rights r) const;
					//Obtain the current stream position
					virtual U64 getPosition() const;
					//Set the current stream position
					virtual bool setPosition(const U64 newPos);
					//Get the size of the stream
					virtual U64 getSize();
					//Create a file stream and open the specified file in the defined mode
					static FileStream *initialize(strRef filePath, File::FileAccessMode acc);
					//Open the specified file in the defined mode
					virtual bool open(strRef filePath, File::FileAccessMode acc);
					//Close the stream
					virtual void close();
					//Flush the contents of the stream to the open file
					bool flushStream();

				protected:
					/* Protected Class Members */
					//The access rights of the FileStream
					U32 accRights;

					/* Protected Class Methods */
					//Initialize the fields of the FileStream
					void init();
					//Fill the data buffer with empty data at a given point
					bool fillBuffer(const U64 startPos);
					//Empty the data buffer
					void emptyBuffer();
					//Set the status of the FileStream based on current values
					void setStatus();
					//Asset function to calculate the beginning position of a block buffer
					static void calcBuffBegin(const U64 pos, U64 *buffBeginPtr);
					//Asset function to calculate the bounds (begin and end positions) of a block buffer
					static void calcBuffBounds(const U64 pos, U64 *buffBeginPtr, U64 *buffEndPtr);
					// Read from a buffer
					virtual bool __read(any outBuff, const U64 bytes);
					// Write to a buffer
					virtual bool __write(cAny inBuff, const U64 bytes);

				private:
					/* Private Class Members */
					//The file currently open
					File_Ref file;
					//The buffer. (obviously)
					U8 buffer[BufferSize];
					//The first valid position of the buffer.
					U64 bufferBegin;
					//The last valid position of the buffer.
					U64 bufferEnd;
					//The current position of the buffer (next operation occurs here)
					U64 bufferPos;
					//Check if the buffer currently has contents that need to be dealt with.
					bool dirty;
					//Check if the stream has reached the end of the file
					bool isEOF;

					/* Private Class Methods */
					/* We're disabling two Stream operations to prevent common misinterpretations of the class */
					//Disable the copy constructor.
					FileStream(const FileStream &c);
					//Disable the assign operator.
					FileStream &operator=(const FileStream &c);
			};

		};

	};

};

#endif //GALACTIC_INTERNAL_FILESTREAM