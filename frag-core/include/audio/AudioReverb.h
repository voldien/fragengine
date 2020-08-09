#ifndef _FV_AUDIOREVERB_H_
#define _FV_AUDIOREVERB_H_ 1

#include "AudioObject.h"

namespace fragcore {

	/**
	 *
	 */
	class FVDECLSPEC AudioReverb : public AudioObject {
		friend class AudioInterface;
	public:
		intptr_t getNativePtr(void) const override;

	protected:
		AudioReverb(void);
		virtual ~AudioReverb(void);
	};

}

#endif