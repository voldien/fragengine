#include "TextureFactory.h"
#include"Renderer/IRenderer.h"
#include"Renderer/Texture.h"
#include<libnoise/noise.h>

using namespace fragview;
using namespace noise;

Texture* TextureFactory::createChecker(IRenderer *renderer, int w, int h) {
	void *pixels;

	assert(renderer && w > 0 && h > 0);

	createChecker(w, h, &pixels);

	TextureDesc desc = {};
	desc.width = w;
	desc.height = h;
	desc.depth = 1;
	desc.target = TextureDesc::eTexture2D;
	desc.internalformat = TextureDesc::eRGB;
	desc.type = TextureDesc::eSignedByte;
	desc.format = TextureDesc::eRGBA;
	desc.pixel = pixels;

	Texture *texture = renderer->createTexture(&desc);

	free(pixels);
	return texture;
}

Texture* TextureFactory::createPerlinNoise(IRenderer *renderer, int w, int h) {
	Texture *textureObject;
	void *pixels;

	assert(renderer && w > 0 && h > 0);

	/*  */
//	module::Perlin perlin;
//	utils::NoiseMap heightMap;
//	utils::NoiseMapBuilderPlane heightMapBuilder;
//	heightMapBuilder.SetSourceModule (perlin);
//	heightMapBuilder.SetDestNoiseMap (heightMap);
//	heightMapBuilder.SetDestSize (256, 256);
//	heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
//	heightMapBuilder.Build ();
	//pixels = PerlinNoise::generatePerlinNoise(w, h, 65, 7, 1.0f, 1.0f);

	/*  */
	TextureDesc desc;
	desc.width = w;
	desc.height = h;
	desc.target = TextureDesc::eTexture2D;
	desc.internalformat = TextureDesc::eRGB;
	desc.type = TextureDesc::eUnsignedByte;
	desc.format = TextureDesc::eSingleColor;
	desc.pixel = pixels;

	/*  */
	Texture *texture = renderer->createTexture(&desc);

	free(pixels);
	return texture;
}


void TextureFactory::createChecker(int width, int Height, char **pixelsResult) {
	/*  TODO perform cleaning. */

	unsigned int x, y, Xpatter, Ypatter, bpp = 4;

	*pixelsResult = malloc(width * Height * bpp);
//	if (!VDIntMallocTexture((void**) pixelsResult, Width, Height, TextureType))
//		return SDL_FALSE;

	int CheckerXDimension = 32;
	int CheckerYDimension = 32;

	Xpatter = (width / CheckerXDimension);	// pattern count in X

	Ypatter = (Height / CheckerYDimension);	// pattern count in Y
	for (x = 0; x < width; x++) {
		for (y = 0; y < Height; y++) {

			float patternIndexX = (float) x / (float) CheckerXDimension;
			float patternIndexY = (float) y / (float) CheckerYDimension;

			switch (bpp) {
				case 1:
					if ((int) patternIndexX % 2 == 0) {	// black
						pixelsResult[0][x * Height * 1 + y * 1] = (
								((int) patternIndexY % 2 == 0) ? 0 : 255);
					} else {	//white
						pixelsResult[0][x * Height * 1 + y * 1] = (
								((int) patternIndexY % 2 == 0) ? 255 : 0);
					}

					continue;
				case 3:
					if ((int) patternIndexX % 2 == 0) {
						pixelsResult[0][x * Height * 3 + y * 3] = (
								((int) patternIndexY % 2 == 0) ? 0 : 255);
						pixelsResult[0][x * Height * 3 + y * 3 + 1] = (
								((int) patternIndexY % 2 == 0) ? 0 : 255);
						pixelsResult[0][x * Height * 3 + y * 3 + 2] = (
								((int) patternIndexY % 2 == 0) ? 0 : 255);
					} else {
						pixelsResult[0][x * Height * 3 + y * 3] = (
								((int) patternIndexY % 2 == 0) ? 255 : 0);
						pixelsResult[0][x * Height * 3 + y * 3 + 1] = (
								((int) patternIndexY % 2 == 0) ? 255 : 0);
						pixelsResult[0][x * Height * 3 + y * 3 + 2] = (
								((int) patternIndexY % 2 == 0) ? 255 : 0);
					}

					continue;
				case 4:
					if ((int) patternIndexX % 2 == 0) {
						pixelsResult[0][x * Height * 4 + y * 4] = (
								((int) patternIndexY % 2 == 0) ? 0 : 255);
						pixelsResult[0][x * Height * 4 + y * 4 + 1] = (
								((int) patternIndexY % 2 == 0) ? 0 : 255);
						pixelsResult[0][x * Height * 4 + y * 4 + 2] = (
								((int) patternIndexY % 2 == 0) ? 0 : 255);
						pixelsResult[0][x * Height * 4 + y * 4 + 3] = 255;
					} else {
						pixelsResult[0][x * Height * 4 + y * 4] = (
								((int) patternIndexY % 2 == 0) ? 255 : 0);
						pixelsResult[0][x * Height * 4 + y * 4 + 1] = (
								((int) patternIndexY % 2 == 0) ? 255 : 0);
						pixelsResult[0][x * Height * 4 + y * 4 + 2] = (
								((int) patternIndexY % 2 == 0) ? 255 : 0);
						pixelsResult[0][x * Height * 4 + y * 4 + 3] = 255;
					}
					continue;
			}	// iteration of bpp
			continue;
		}	// iteration of X
		continue;
	}	// iteration of Y

}

