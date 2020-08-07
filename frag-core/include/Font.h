#ifndef _FV_FONT_H_
#define _FV_FONT_H_ 1
#include "Core/SmartReference.h"
#include "Renderer/Texture.h"
#include <map>

namespace fragview {
	/**
	 *
	 */
	//TODO check if some polymorpihsm can be used.
	class FVDECLSPEC Font : public SmartReference {
		friend class FontFactory;

		struct Character {
			int width;
			int height;
			int Bearing[2];    // Offset from baseline to left/top of glyph
			float Advance;    // Offset to advance to next glyph
//		float* advance;             /*  */
			/*  UV rectangle.   */
			float tex_x1;              /*  */
			float tex_x2;              /*  */
			float tex_y1;              /*  */
			float tex_y2;              /*  */
			/*  UV offset.  */
			float offset_x;            /*  */
			float offset_y;            /*  */
			/*  Size of the font.   */
			float size;                 /*  */
		};
	public:
		Font(void);

		~Font(void);

		unsigned int getNumberCharacter(void) const;

		//TODO rename index to unicode or something.
		Character getCharacter(unsigned int index);

		const Character &getCharacter(unsigned int index) const;

		unsigned int getEncoding(void) const;

		Texture *getTexture(void) const;

		//TODO add support for config file for lookup.
	private:

		Texture *texture;
		std::map<unsigned int, Character> characters;
	};
}

#endif