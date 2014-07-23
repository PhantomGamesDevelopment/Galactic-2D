/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* defines.h
*
* Loads Galactic Engine Macros and definitions
**/

#ifndef GALACTIC_DEFINES
#define GALACTIC_DEFINES

//Engine Defines

/* Yep, I just love being hilarious... :) */
//SendToHell(): Throw bad pointers and objects into the fire where they belong.
#define SendToHell(x) delete x; x = NULL;
//SendToPitsOfHell(): Throw bad pointers and objects into the deep pits of hell where they can rot, but not be eliminated.
#define SendToPitsOfHell(x) delete x;
//SendToHeaven(): Send pointers and objects to memory heaven, where their lives end and happiness commences.
#define SendToHeaven(x) free(x) x = NULL;
//SendToGatesOfHeaven(): Send pointers and objects to the gates of memory heaven, I guess they aren't quite... dead... yet.
#define SendToGatesOfHeaven(x) free(x);

/* Console Messaging Shortcuts */
//Print shortut
#define GC_Print(x, ...) ::Galactic::Console::print(x, __VA_ARGS__)
//Warn shortut
#define GC_Warn(x, ...) ::Galactic::Console::warn(x, __VA_ARGS__)
//Error shortut
#define GC_Error(x, ...) ::Galactic::Console::error(x, __VA_ARGS__)
//CError shortut
#define GC_CError(x, ...) ::Galactic::Console::cerr(x, __VA_ARGS__)

/* Type Forcing */
//Force result to boolean
#define FBOOL(x) !!x

#endif //GALACTIC_DEFINES