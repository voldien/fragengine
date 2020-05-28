
#ifndef _FV_TEXTURE_FACTORY_H_
#define _FV_TEXTURE_FACTORY_H_ 1

#include "Prerequisites.h"
#include"Def.h"

namespace fragview {

	/**
	 *	Texture factory class responsible
	 *	for the creation of predefined
	 *	texture objects.
	 */
	class FVDECLSPEC TextureFactory {
	public:

		static Texture *createChecker(IRenderer *renderer, int w, int h);

		static Texture *createPerlinNoise(IRenderer *renderer, int w, int h);

	public:
		static void createChecker(int width, int height, char **pixels);
	private:    /*	Prevent one from creating an instance of this class.	*/

		TextureFactory(void);
		TextureFactory(const TextureFactory &other);
		~TextureFactory(void);
	};
}

#endif
