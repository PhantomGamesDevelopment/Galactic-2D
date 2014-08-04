/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* commandLineParams.h
*
* Defines an operational class to store and fetch the command line parameters of the launched Galactic 2D instance.
**/

#ifndef GALACTIC_PLATFORM_GENERIC_CMDLINEPRMS
#define GALACTIC_PLATFORM_GENERIC_CMDLINEPRMS

#include "../engineCore.h"

namespace Galactic {

	namespace Core {
		
		/*
		ProcessCommandLine: A singleton instance that stores the command line of the executed G2D instance.
		*/
		class ProcessCommandLine {
			public:
				/* Public Class Methods */
				//Default Constructor
				ProcessCommandLine::ProcessCommandLine() { }
				//Fetch the singleton instance of this class
				ProcessCommandLine &fetchInstance() {
					if (managedSingleton<ProcessCommandLine>::instance() == NULL) {
						managedSingleton<ProcessCommandLine>::createInstance();
					}
					return *(managedSingleton<ProcessCommandLine>::instance());
				}
				//Set the command line to a specific value
				void set(UTF16 newLine) {
					strcpy(cmdLine, newLine);
				}
				//Append a string to the command line
				void append(UTF16 toAppend) {
					strncat(cmdLine, toAppend, getArrayCount(cmdLine));
				}

			private:
				/* Private Class Members */
				//How much can be written to the buffer
				static X32 maxLength = 16384;
				//The character array of the stored command line
				static C8 cmdLine[maxLength];
		};

	};

};

#endif //GALACTIC_PLATFORM_GENERIC_CMDLINEPRMS