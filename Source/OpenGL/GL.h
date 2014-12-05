/**
* Galactic 2D
* GL.h
* The primary loaded file to initialize the engine's OpenGL systems
* (C) 2014 Phantom Games Development - All Rights Reserved
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

#ifndef GALACTIC_OPENGL_GL
#define GALACTIC_OPENGL_GL

/* Standard Defines */
//This OpenGL Module Supports Uniform Buffers
#define GL_UNIFORM_BUFERS 1
//This OpenGL Module Supports Pixel Buffers
#define GL_PIXEL_BUFERS 1

namespace Galactic {

	namespace OpenGL {

		/*
		OGLBase: Base functioning for the OpenGL Module
		*/
		class OGLBase {
			public:
				/* Public Class Members */
				//Flags for the current state of reading & writing
				enum GLRWFlags {
					//The state can only read data
					ReadOnly,
					//The state can only write data
					WriteOnly,
					//The state may read or write data
					ReadWrite,
					//The state can only write, and it must be persistent data
					WritePersistOnly,
					//The state can only write, no data restrictions
					WriteAnyOnly,
				};
				//Flags for the results of the Fence system of the OGL rendering module
				enum FenceResult {
					//All good!
					AllOK,
					//This fence has already been completed
					AlreadyDone,
					//The timeout has expired for this fence
					TimeoutExpired,
					//Failed
					Failed,
				};

				/* Public Class Methods */
				//Check the extensions
				static void validateExtensions(const String &extensions);
				//Update the numerics of this module
				static void updateNumerics();

			protected:
				/* Protected Class Members */
				/*The maximum amount of image units, array values are for:
				[0]: Texture
				[1]: Combined Texture
				[2]: Vertex Texture
				[3]: Geometry Texture
				[4]: Hull Texture
				[5]: Domain Texture
				*/
				static GLint maxImageUnits[6];
				/*The maximum amount of uniform components, array values are for:
				[0]: Vertex
				[1]: Pixel
				[2]: Geometry
				[3]: Hull
				[4]: Domain
				*/
				static GLint maxUniformComponents[5];
				// Support for GL_KHR_texture_compression_astc_ldr?
				static bool ASTCSupported;
				//Support for GL_ARB_copy_image?
				static bool CopyImageSupported;
				// Support for GL_ARB_seamless_cube_map?
				static bool SeamlessCubemapSupported;
				// Can we render to texture 2D array or 3D
				static bool VolumeTextureRenderingSupported;
				// Support for GL_EXT_texture_filter_anisotropic?
				static bool TextureFilterAnisotropicSupported;
		};

	};

};

#endif //GALACTIC_OPENGL_GL