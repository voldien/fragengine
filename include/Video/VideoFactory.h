#ifndef FRAGVIEW_VIDEOFACTORY_H
#define FRAGVIEW_VIDEOFACTORY_H

#include "audio/AudioClip.h"
#include "Core/Ref.h"
#include "VideoTexture.h"

namespace fragview {

	/**
	 * 
	 */
	class FVDECLSPEC VideoFactory {
	public:

		static VideoTexture* loadVideoTexture(Ref<IO>& ref, AudioClip** audio, IRenderer* renderer, AudioInterface* audioInterface);

		static void VideoTask(void);

	private: /*	Prevent one from creating an instance of this class.	*/
		VideoFactory(void);
		VideoFactory(const VideoFactory &other);
	};
}

#endif