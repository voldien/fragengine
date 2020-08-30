

#ifndef _FRAG_ENGINE_SPRITE_BATCH_H_
#define _FRAG_ENGINE_SPRITE_BATCH_H_ 1
#include <Renderer/Prerequisites.h>

namespace fragengine{
	using namespace fragcore;
	class FVDECLSPEC SpriteBatch : public SmartReference
	{
	public:
		SpriteBatch(void);
		SpriteBatch(const Ref<IRenderer> &renderer);

	private:
		/**/
	};
}

#endif