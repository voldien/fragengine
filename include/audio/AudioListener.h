
#ifndef _AUDIOLISTENER_H_
#define _AUDIOLISTENER_H_ 1
#include"../Def.h"
#include "AudioObject.h"

namespace fragview {

	/**
	 *
	 */
	class FVDECLSPEC AudioListener : public AudioObject {
		friend class AudioInterface;
	public:

		virtual void setVolume(float volume);
		virtual float getVolume(void) const;

		virtual void pause(bool pause);

		//virtual void getOutPutData(void);

		virtual void setPosition(const PVVector3& position);
		virtual const PVVector3& getPosition(void) const;

		virtual void setVelocity(const PVVector3& velocity);
		virtual const PVVector3& getVelocity(void) const;

		virtual void setOrientation(const PVQuaternion& orientation);
		virtual const PVQuaternion& getOrientation(void) const;

		intptr_t getNativePtr(void) const override;

	protected:
		AudioListener(void);
		virtual ~AudioListener(void);
	};
}

#endif