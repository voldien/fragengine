#ifndef _AUDIOSETTINGS_H_
#define _AUDIOSETTINGS_H_ 1
#include "AudioInterface.h"

namespace fragview {

	/**
	 *
	 */
	class FVDECLSPEC AudioSettings : public AudioObject {
	public:


		virtual AudioSpeakerMode getSpeakerMode(void) const;
		virtual void setSpeakerMode(AudioSpeakerMode speakerMode);

		virtual int outputSampleRate(void);

	};

}

#endif