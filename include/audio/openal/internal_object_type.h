
#ifndef _INTERNAL_OBJECT_TYPE_H_
#define _INTERNAL_OBJECT_TYPE_H_ 1
#include<AL/al.h>
#include<AL/alext.h>
#include<AL/alut.h>
#include<AL/efx-presets.h>
#include <audio/AudioDesc.h>

namespace fragview {

	typedef struct openal_interface_object_t {
		ALCdevice *device;
		ALCcontext *context;
		bool supportEffects;
		LPALGENEFFECTS alGenEffects;
		LPALDELETEEFFECTS alDeleteEffects;
		LPALISEFFECT alIsEffect;
	} OpenALInterfaceObject;

	typedef struct openal_audio_clip_t {
		unsigned int source;
	} ALClip;

	typedef struct openal_audio_source_t {
		unsigned int source;
	} ALSource;

	typedef struct openal_audio_reverb_t{
		unsigned int reverb;
	} ALReverb;


	extern ALenum translate2ALFormat(AudioFormat format);
}

#endif
