/**
    FrameView for rendering shaders in screen space.
    Copyright (C) 2018  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _FRAMEVIEW_TEXTURE_UTIL_H_
#define _FRAMEVIEW_TEXTURE_UTIL_H_ 1
#include <Renderer/IRenderer.h>
#include"Renderer/Texture.h"

/**
 *
 */
class FVDECLSPEC TextureUtil {
public:

	static void loadTexture(const char *path, IRenderer *renderer, Texture **texture);

	static void loadTexture(const void *pbuf, long int size, IRenderer *renderer, Texture **texture);

	static void *loadTextureData(const char *cfilename, unsigned int *pwidth,
	                             unsigned int *pheight, TextureDesc::Format *pformat,
	                             TextureDesc::Format *pinternalformat, TextureDesc::Type *ptype,
	                             unsigned long *pixelSize);

	static void *loadTextureData(const char *cfilename, unsigned int *pwidth,
	                             unsigned int *pheight, unsigned long *pixelSize);

	static void *loadTextureData(const void *pbuf, long int size, unsigned int *width, unsigned int *height);

	static void *loadTextureDataFromMem(const void *pbuf, long int size, unsigned int *width, unsigned int *height,
	                                    TextureDesc::Format *pformat,
	                                    TextureDesc::Format *pinternalformat, TextureDesc::Type *ptype,
	                                    unsigned long *pixelSize);

	static void saveTexture(const char *filepath, IRenderer *renderer, Texture *texture);

private:    /*	Prevent one from creating an instance of this class.	*/

	TextureUtil(void);

	TextureUtil(const TextureUtil &other);
};

#endif