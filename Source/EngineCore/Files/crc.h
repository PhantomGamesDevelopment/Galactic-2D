/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* crc.h
*
* Defines a class for calculating CRC32 values. This is mainly used for file checksums for determining the modified time of files to be used by the engine
* Reference: http://en.wikipedia.org/wiki/CRC32
**/

#ifndef GALACTIC_INTERNAL_FILES_CRC
#define GALACTIC_INTERNAL_FILES_CRC

#include "../platform.h"
#include "../Stream/stream.h"

namespace Galactic {

	namespace Core {
		
		namespace Files {

			/*
			CRC: Defines a class for calculating the Cyclic Redundancy Check (CRC) using 33 bits of polynomial length, or CRC-32. This calculation is mainly used
			 by the file system for calculating checksum values for files and directories for determining the absolute last modified time.
			*/
			class CRC {
				public:
					//Calculate the CRC-32 for the given data buffer
					U32 calculateCRC(cAny buff, S32 length, U32 crcVl);
					//Calculate the CRC-32 for a given Stream instance
					U32 calculateCRC(Streams::Stream *s, U32 crcVl);
			
				private:
					//Table of hexadecimal values used for calculating CRC32
					static U32 CRCTable[];
			};

		};

	};

};

#endif //GALACTIC_INTERNAL_FILES_CRC