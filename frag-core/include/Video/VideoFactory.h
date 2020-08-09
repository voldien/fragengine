#ifndef _FRAG_CORE_VIDEOFACTORY_H_
#define _FRAG_CORE_VIDEOFACTORY_H_ 1

#include "audio/AudioClip.h"
#include "Core/Ref.h"
#include "VideoTexture.h"

namespace fragcore {

	/**
	 * 
	 */
	class FVDECLSPEC VideoFactory {
	public:

		static VideoTexture* loadVideoTexture(Ref<IO>& ref, AudioClip** audio, IRenderer* renderer, AudioInterface* audioInterface);

	private: /*	Prevent one from creating an instance of this class.	*/
		VideoFactory(void);
		VideoFactory(const VideoFactory &other);
	};
}

#endif