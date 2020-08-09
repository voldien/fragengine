
#ifndef _FV_IMAGE_H_
#define _FV_IMAGE_H_ 1
#include "Renderer/Texture.h"

namespace fragcore {

	/**
	 *
	 */
	 //System memory bound texture data.
	class FVDECLSPEC Image : public Texture {
	public:
		//TODO determine of Image or surface or both classes will be used.
		Image(int width, int height, TextureFormat format);
	};
}

#endif
