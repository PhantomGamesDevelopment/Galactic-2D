### Galactic 2D Engine ###
## By: Phantom Games Development ##

V. 1.0.0.0 (7-12-2014)

# Introduction #
Galactic 2D is our first in-house engine technology that takes advantage of numerous open-source, and cross-platform systems to deliver a compact and easy to use modular development engine to create games and applications of numerous types.

# What's Included #
Galactic 2D includes the following core features and systems: 

* 64-Bit Cross Platform Support For Windows, Linux, Mac, Android, and more!
* Internal Rendering Module using OpenGL / GLES
* Audio Module using OpenAL
* 128 player multiplayer support with eNet
* Built in LUA-JIT scripting & FFI Implementation
* Internal 64-bit Threading, Files, Streams
* External Module Loading System (.dll / .so / .app)
* Easy to navigate and use source code properly documented and sorted by means of namespacing.

These features combine together to give both game and application developers an amazing set of tools and mechanics to get off the ground at a fast pace in their development.

# How To Develop #

If you have access to this source-code, then you can simple copy the code-base into a new project and hop right into development. If you are reading this readme or are simply using this as a reference source, you may use the Galactic 2D Toolkit to create a library (.dll, .app, .so) and with Galactic 2D's module loading system, plug in your code directly to the engine and run as a stand-alone application.

For further details, see the Galactic 2D page on our website: http://www.phantomdev.net/Galactic/2D/

# Getting Started #

Once you download the engine files listed here, you'll need to start by compiling a clean copy of the engine to ensure the validity of your files. You may follow the specified sections below to compile the engine on your platform. Once you have compiled the engine and have validated the file integrity, you should start by reading the included documentation to get a good grip on the workflow of the engine. From there, you may visit the Galactic 2D website at: http://www.phantomdev.net/Galactic/2D/ to download the G2D SDK. The included template files & projects will give you a great starting point for your own application. Since you have a copy of the source code to the engine, it is recommended that instead of building a module for the engine that you follow the steps below to create a project directly attached to the engine. This will prevent the possibility of security breaches to the code of your game by means of .DLL manipulation and reverse compiler software such as IDA, Etc.

# Compiling Galactic 2D on Windows #

To compile on Windows, you need to have Microsoft Visual Studio 2013 (http://www.microsoft.com/en-us/download/details.aspx?id=40787) installed. Any version of MSVS 2013 is acceptable, including the express version. Load the included Galactic2D.sln file in MSVS 2013.
 You may compile either a 32 bit or a 64 bit, however, we recommend you leave it on Win64, as the platform will identify the version for you. Compiling on Win64 ensures that computers of both 32 and 64 bit may use their functioning. Set the build mode to 'Release' mode and build the solution (F7), this process should take anywhere between 5 - 15 minutes depending on your computer setup. Once the engine is compiled, you may run it by means of the built executable file, or by pressing Ctrl+F5 in MSVS.

# Compiling Galactic 2D on Mac #

To compile on a Mac, you need to have XCode 5.1 (https://itunes.apple.com/us/app/xcode/id497799835) installed. Included in the main directory is a GenerateProject.command file, run this file to generate the necessary project files. Run the generated Galactic2D.xcodeproj to load the project in XCode.
 Compile by using the 'Build For' option under the 'Product' menu. This process will take between 5 -15 minutes depending on your machine. Once this process is complete, you may run the engine by means of the built G2D.exe file.

# How to build a project directly inside the engine #

Included with the engine is a single template project folder. You'll want to copy this folder to a directory of your choosing.
 To begin development of an internal project, you'll want to open the Galactic 2D project file in your code editor. Once inside the editor, under the project files you will see the standard Galactic 2D engine files & folders. From the top directory of the engine, create a new folder naming it something resembling to your project, then you'll want to create a new C++ header file to serve as the entry point, for example:

    /**
    * Galactic 2D
    * (C) 2014 Phantom Games Development - All Rights Reserved
    * myGameMain.h
    *
    * Entry point to my game
    *
    **/

    #ifndef MY_GAME_MAIN_H
    #define MY_GAME_MAIN_H

    #include "../EngineCore/engineCore.h"

    #define GALACTIC_INTERNAL_PROJECT

    namespace Galactic {

       FINLINE void initInternalProject() {
          //Load custom modules here
       }

       namespace myGame {
          //Create a namespace for your game
       };

    };

    #endif //MY_GAME_MAIN_H

The main premesis of this approach is simple. By using the C++ flag GALACTIC_INTERNAL_PROJECT, the engine knows to look for the method initInternalProject. You can treat this is void main() for your project and proceed from there.