#include"FontFactory.h"
#include<ft2build.h>
#include<cassert>
#include<cmath>
#include <Utils/TextureUtil.h>
#include <Utils/StringUtil.h>
#include <Core/IO/FileSystem.h>
#include <Exception/InvalidArgumentException.h>
#include FT_FREETYPE_H
using namespace fragview;

inline static int nextp2(int n) {
	int res = 1;
	while (res < n)res <<= 1;
	return res;
}

Font *FontFactory::createFont(IRenderer* renderer, IO* io, float size, Encoding encoding) {
	Font *object;
	Texture *fontTexture;

	/*  */
	const size_t numChar = 128;
	const size_t nrFontFields = 9;
	std::map<unsigned int, Font::Character> characters;
	int i, j, l;
	FT_Error ftError;
	FT_Library ft;
	FT_Glyph_Metrics *metrics;
	FT_Face face;
	FT_GlyphSlot slot;
	FT_Matrix matrix;                 /* transformation matrix */
	FT_Vector pen;                    /* untransformed origin  */
	FT_Bitmap *bmp;
	int glyph_width;
	int glyph_height;
	int num_segments_x = numChar;
	int num_segments_y = numChar;
	int segment_size_x = 0;
	int segment_size_y = 0;
	int font_tex_width;
	int font_tex_height;
	int bitmap_offset_x = 0, bitmap_offset_y = 0;

	/*  Validate arguments. */
	if (renderer == NULL)
		throw InvalidArgumentException("Requires none-null renderer object.");
	if (size <= 0.0f)
		throw InvalidArgumentException("Requires size to be greater than 0.");

	/*  Init library.   */
	ftError = FT_Init_FreeType(&ft);
	if (ftError != FT_Err_Ok)
		throw InvalidArgumentException(fvformatf("Failed to initialize FreeType - %d.\n", ftError));

	//TODO add support for IO object.
	/*  Load font face by the path. */
	char* buf;
	long int nBytes = FileSystem::loadFile(io, &buf);
	ftError = FT_New_Memory_Face(ft, (const FT_Byte*)buf, nBytes, 0, &face);
	if (ftError != FT_Err_Ok) {
		FT_Done_FreeType(ft);
		throw InvalidArgumentException(fvformatf("Failed to load font - %d.\n", ftError));
	}

	ftError = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
	if (ftError != FT_Err_Ok) {
		FT_Done_FreeType(ft);
		throw InvalidArgumentException(fvformatf("Failed to load font - %d.\n", ftError));
	}

	/*  Set the size of the font.   */
	//ftError = FT_Set_Char_Size(face, 0, size, 96, 96);   //TODO get the DPI
	ftError = FT_Set_Pixel_Sizes(face, 0, 48);
	if (ftError != FT_Err_Ok) {
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
		throw InvalidArgumentException(fvformatf("Failed to set character size - %d.\n", ftError));
	}

	/*	First calculate the max width and height of a character in a passed font	*/
	for (i = 0; i < numChar; i++) {

		/*  Load character. */
		ftError = FT_Load_Char(face, i, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LIGHT);
		if (ftError != FT_Err_Ok) {
			FT_Done_Face(face);
			FT_Done_FreeType(ft);
			throw InvalidArgumentException(fvformatf("FT_Load_Char failed - %d.\n", ftError));
		}

		/*  */
		slot = face->glyph;
		bmp = &slot->bitmap;

		/*  Character bitmap size.  */
		glyph_width = bmp->width;
		glyph_height = bmp->rows;

		/*  Compute max width and height.   */
		if (glyph_width > segment_size_x) {
			segment_size_x = glyph_width;
		}

		if (glyph_height > segment_size_y) {
			segment_size_y = glyph_height;
		}
	}

	/*  Compute texture size.    */
	font_tex_width = nextp2(num_segments_x * segment_size_x);
	font_tex_height = nextp2(num_segments_y * segment_size_y);

	int max_dim = (1 + (face->size->metrics.height >> 6)) * ceilf(sqrtf(128));
	font_tex_width = 1;
	while (font_tex_width < max_dim) font_tex_width <<= 1;
	font_tex_height = font_tex_width;

	/*	Allocate pixel data.    */
	const unsigned int fontPixelSize = sizeof(char) * font_tex_width * font_tex_height;
	char *font_texture_data = (char *) malloc(fontPixelSize);
	memset((void *) font_texture_data, 0, fontPixelSize);

	int pen_x = 0, pen_y = 0;

	/*  Iterate through each character. */
	for (i = 0; i < numChar; i++) {

		/*  Load character. */
		ftError = FT_Load_Char(face, i, FT_LOAD_RENDER);
		if (ftError != FT_Err_Ok) {

			/*  Release all resources.    */
			FT_Done_Face(face);
			FT_Done_FreeType(ft);
			free(font_texture_data);
			throw InvalidArgumentException(fvformatf("FT_Load_Char failed - %d.\n", ftError));
		}
		FT_Bitmap *bmp = &face->glyph->bitmap;


		/*  Rotate the face.    */
		matrix.xx = (FT_Fixed) (-cos(3.14) * 0x10000L);
		matrix.xy = (FT_Fixed) (-sin(3.14) * 0x10000L);
		matrix.yx = (FT_Fixed) (sin(3.14) * 0x10000L);
		matrix.yy = (FT_Fixed) (cos(3.14) * 0x10000L);
		/*  */
		div_t temp = div(i, num_segments_x);
		/*  */
		bitmap_offset_x = segment_size_x * temp.rem;
		bitmap_offset_y = segment_size_y * temp.quot;
		/*  */
		pen.x = bitmap_offset_x;
		pen.y = bitmap_offset_y;
		FT_Set_Transform(face, &matrix, &pen);

		/*  */
		slot = face->glyph;
		bmp = &slot->bitmap;

		/*  Get power of two size.  */
		glyph_width = bmp->width;
		glyph_height = bmp->rows;

		if (bmp->buffer) {
			if (pen_x + bmp->width >= font_tex_width) {
				pen_x = 0;
				pen_y += ((face->size->metrics.height >> 6) + 1);
			}
			for (int row = 0; row < glyph_height; ++row) {
				for (int col = 0; col < glyph_width; ++col) {
					int x = pen_x + col;
					int y = pen_y + row;
					font_texture_data[y * font_tex_width + x] = bmp->buffer[row * bmp->pitch + col];
				}
			}
		}

		pen_x += bmp->width + 1;

		/*  Set character properties.   */
		Font::Character character;
		character.Advance = (float) (slot->advance.x >> 6);
		character.tex_x1 = (float) bitmap_offset_x / (float) font_tex_width;
		character.tex_x2 = (float) (bitmap_offset_x + bmp->width) / (float) font_tex_width;
		character.tex_y1 = (float) bitmap_offset_y / (float) font_tex_height;
		character.tex_y2 = (float) (bitmap_offset_y + bmp->rows) / (float) font_tex_height;
		character.width = bmp->width;
		character.height = bmp->rows;
		character.offset_x = (float) slot->bitmap_left;
		character.offset_y = (float) ((slot->metrics.horiBearingY - face->glyph->metrics.height) >> 6);
		characters[i] = character;
	}

	/*  Release resources.  */
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	//TODO add signed texture support.

	/*  Allocate texture.   */
	/*  Texture attributes. */
	TextureDesc desc = {0};
	desc.width = font_tex_width;
	desc.height = font_tex_height;
	desc.depth = 1;
	desc.pixel = font_texture_data;
	desc.pixelSize = fontPixelSize;
	desc.compression = TextureDesc::eNoCompression;

	/*  Texture.    */
	desc.target = TextureDesc::eTexture2D;
	desc.format = TextureDesc::eSingleColor;
	desc.internalformat = TextureDesc::eRGBA;
	desc.type = TextureDesc::eUnsignedByte;
	desc.numlevel = 3;
	desc.usemipmaps = 1;
	desc.srgb = 0;

	/*  sampler.    */
	desc.sampler.AddressU = SamplerDesc::eRepeat;
	desc.sampler.AddressV = SamplerDesc::eRepeat;
	desc.sampler.AddressW = SamplerDesc::eRepeat;
	desc.sampler.anisotropy = 8.0f;
	desc.sampler.minFilter = SamplerDesc::eLinear;
	desc.sampler.magFilter = SamplerDesc::eLinear;
	desc.sampler.mipmapFilter = SamplerDesc::eLinear;
	fontTexture = renderer->createTexture(&desc);

	//TODO remove
	TextureUtil::saveTexture("test.png", renderer, fontTexture);

	/*  Free resources. */
	//free(signedTexture);
	free(font_texture_data);

	/*  Create texture object.  */
	object = new Font();
	object->texture = fontTexture;
	object->characters = characters;
	return object;
}