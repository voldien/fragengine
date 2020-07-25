#ifndef _FRAG_CORE_AUDIOSETTINGS_H_
#define _FRAG_CORE_AUDIOSETTINGS_H_ 1
#include "AudioInterface.h"

namespace fragview {

	/**
	 *
	 */
	class FVDECLSPEC AudioSettings : public AudioObject {
	public:

		virtual AudioSpeakerMode getSpeakerMode(void) const;
		virtual void setSpeakerMode(AudioSpeakerMode speakerMode);

		virtual void setMasterVolume(float volume);
		virtual float getMaterVolume(void) const;
		
		virtual int outputSampleRate(void);
	};

}

#endif