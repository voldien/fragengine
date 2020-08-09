
#ifndef _FRAG_CORE_TEXTURE_FACTORY_H_
#define _FRAG_CORE_TEXTURE_FACTORY_H_ 1
#include "Prerequisites.h"
#include"Def.h"

namespace fragcore {

	/**
	 *	Texture factory class responsible
	 *	for the creation of predefined
	 *	texture objects.
	 */
	class FVDECLSPEC TextureFactory {
	public:
		static Texture *createChecker(IRenderer *renderer, int width, int height);
		static Texture *createPerlinNoise(IRenderer *renderer, int width, int height);
		static Texture *createNoiseTexture(IRenderer *renderer, int width, int height);

	public:
		static void createChecker(int width, int height, char **pixels);
	private:    /*	Prevent one from creating an instance of this class.	*/

		TextureFactory(void);
		TextureFactory(const TextureFactory &other);
		~TextureFactory(void);
	};
}

#endif
