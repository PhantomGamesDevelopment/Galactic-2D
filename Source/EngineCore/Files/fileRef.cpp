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

			TimeVars FileRef::getLastModified() {
				FileAttributes atrb;

				bool success = getAttributes(&atrb);
				if(!success) {
					TimeVars t;
					PlatformTime::sysTime(t);
					return t;
				}
				return atrb.fLastModified;
			}

			U64 FileRef::getChecksum() {
				TimeVars t;
				PlatformTime::sysTime(t);

				bool needCalc = (lastChecksum == t);
				if(!needCalc) {
					TimeVars lastModified = getLastModified();
					needCalc = (lastModified > lastChecksum);
				}
				if(needCalc) {
					checksum = calcChecksum();
				}
				if(checksum) {
					PlatformTime::sysTime(lastChecksum);
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