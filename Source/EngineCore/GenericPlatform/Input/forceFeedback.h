/**
* Galactic 2D
* Source/EngineCore/GenericPlatform/Input/forceFeedback.h
* Defines a standard force feedback system for dealing with controller instances
* (C) 2014-2016 Phantom Games Development - All Rights Reserved
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
**/

#ifndef GALACTIC_INTERNAL_GENERICPLATFORM_FORCEFEEDBACK
#define GALACTIC_INTERNAL_GENERICPLATFORM_FORCEFEEDBACK

namespace Galactic {

	namespace Core {

		/*
		 Force Feedback systems are primarily associated with DirectX and the DirectInput class associated with DirectX. However, since we're going to
		  also include OpenGL in this engine, we need a wrapper class instance that handles this kind of a system on a per-platform basis.

		  A good informational reference on this is available here: http://www.egr.msu.edu/classes/ece480/capstone/spring13/group05/downloads/Application%20Note.pdf
		*/

		/* 
		FFChannels: Channels that may be used for the Force Feedback system

		NOTE: This refers to the H-Bridge switches as shown in the above article. These channels are identified as S1, S2, S3, and S4. However, since this
		 would be confusing for the sake of having to constantly refer to the diagram in the article, we'll just call them by the relative position they show 
		 on the chart. Refer to the ENUM comment for each of these channels to see the S# implementation.
		*/
		enum FFChannels {
			//FCHANNEL_TOP_LEFT: This refers to the top left, or H-Channel S1
			FCHANNEL_TOP_LEFT,
			//FCHANNEL_BOTTOM_LEFT: This refers to the bottom left, or H-Channel S2
			FCHANNEL_BOTTOM_LEFT,
			//FCHANNEL_TOP_RIGHT: This refers to the top right, or H-Channel S3
			FCHANNEL_TOP_RIGHT,
			//FCHANNEL_BOTTOM_RIGHT: This refers to the bottom right, or H-Channel S4
			FCHANNEL_BOTTOM_RIGHT,
		};

		/*
		FFValues: A basic structure containing values to be stored and worked with as needed by the Force Feedback implementation
		*/
		struct FFValues {
			/* Public Struct Methods */
			//Default (empty) constructor
			FFValues() :
				topLeftLevel(0.0f),
				bottomLeftLevel(0.0f),
				topRightLevel(0.0f),
				bottomRightLevel(0.0f) { }

			/* Public Struct Members */
			//Switch level of S1 (0.0f - 1.0f)
			F32 topLeftLevel;
			//Switch level of S2 (0.0f - 1.0f)
			F32 bottomLeftLevel;
			//Switch level of S3 (0.0f - 1.0f)
			F32 topRightLevel;
			//Switch level of S4 (0.0f - 1.0f)
			F32 bottomRightLevel;
		};

		/*
		GenericForceFeedback: Abstract base class for establishing connection to the ForceFeedback system in the engine. Platforms will need to define their
		 own instances of this particular class instance as needed by their controller instances.
		*/
		class GenericForceFeedback {
			public:
				/* Public Class Methods */
				//Destructor
				virtual ~GenericForceFeedback() {
				}
				//Set the channel value for the particular controller instance
				virtual void setChannelValue(FFChannels channel, S32 controllerID, F32 value) = 0;
				//Set all of the channel values for a particular controller instance
				virtual void setAllChannelValues(const FFValues &values, S32 controllerID) = 0;
		};

	};

};

#endif //GALACTIC_INTERNAL_GENERICPLATFORM_FORCEFEEDBACK