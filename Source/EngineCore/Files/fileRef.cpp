/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* fileRef.cpp
*
* Defines the fileRef class which defines a set of common properties used by the file object classes in this engine. This code file is based off of the 
* Torque Game Engine's FileSystem, some of the features are the same, however modifications and adjustments are used to suit the Galactic 2D Engine.
**/

#include "fileRef.h"

namespace Galactic {

	namespace Core {

		namespace Files {

			FileRef::FileRef() {
				checksum = 0;
			}

			Time FileRef::getLastModified() {
				FileAttributes atrb;

				bool success = getAttributes(&atrb);
				if(!success) {
					return Time();
				}
				return atrb.fLastModified;
			}

			U64 FileRef::getChecksum() {
				bool needCalc = (lastChecksum == Time());
				if(!needCalc) {
					Time lastModified = getLastModified();
					needCalc = (lastModified > lastChecksum);
				}
				if(needCalc) {
					checksum = calcChecksum();
				}
				if(checksum) {
					lastChecksum = Time::getCurrentTime();
				}
				return checksum;
			}

			U64 FileRef::getSize() {
				FileAttributes atrb;

				bool success = getAttributes(&atrb);
				if(!success) {
					return 0;
				}
				return atrb.fSize;				
			}

		};

	};

};