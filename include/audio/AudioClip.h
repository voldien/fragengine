#ifndef PHYSIC_AUDIOCLIP_H_
#define PHYSIC_AUDIOCLIP_H_ 1
#include"../Def.h"
#include "AudioObject.h"
#include"AudioDesc.h"

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC AudioClip : public AudioObject {
		friend class AudioInterface;
	public:

		virtual unsigned long int getSampleRate(void) const;
		virtual unsigned long int getFrequency(void) const;
		virtual AudioFormat getAudioFormat(void) const;
		virtual unsigned int getNumberChannels(void) const;
		virtual unsigned long getSize(void) const;
		virtual float length(void) const;

		virtual void getData(void* pData, unsigned int nsamples, unsigned int offset);
		virtual void setData(void* pData, unsigned int nsamples, unsigned int offset);

		intptr_t getNativePtr(void) const override;

	protected:
		AudioClip(void);
		virtual ~AudioClip(void);
	};
}

#endif