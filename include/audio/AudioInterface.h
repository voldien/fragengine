#ifndef _AUDIOINTERFACE_H_
#define _AUDIOINTERFACE_H_ 1
#include"../Def.h"
#include"../Core/IConfig.h"
#include"AudioDesc.h"
#include "AudioPhysicalDevice.h"
#include "AudioClip.h"
#include "AudioReverb.h"


#include<vector>

namespace fragview {

	/**
	 *
	 */
	class FVDECLSPEC AudioInterface : public SmartReference {
	protected:
		//virtual void initAllocate(InitAllocateTableInfo *table);

	public:
		AudioInterface(IConfig* config);
		virtual ~AudioInterface(void);

		/**
		 *
		 * @param desc
		 * @return
		 */
		virtual AudioClip* createAudioClip(AudioClipDesc* desc);
		virtual void deleteAudioClip(AudioClip* audioClip);

		/**
		 *
		 * @param desc
		 * @return
		 */
		virtual AudioSource* createAudioSource(AudioSourceDesc* desc);
		virtual void deleteAudioSource(AudioSource* audioSource);

		virtual AudioReverb* createAudioReverb(AudioReverbDesc* desc);
		virtual void deleteAudioReverb(AudioReverb* reverb);

		/**
		 *
		 * @param desc
		 * @return
		 */
		virtual AudioListener* createAudioListener(AudioListenerDesc* desc);

		/**
		 *
		 * @param listener
		 */
		virtual void deleteAudioListener(AudioListener* listener);

		/**
		 *
		 * @param listener
		 */
		virtual void setAudioListener(AudioListener* listener);

		/**
		 *
		 * @return
		 */
		virtual std::vector<AudioPhysicalDevices> getDevices(void) const;
		//TODO add mic.

		virtual void setAudioDevice(const AudioPhysicalDevices& device);
		virtual const AudioPhysicalDevices& getAudioDevice(void) const;

		//virtual AudioSettings* getAudioSettings(void);

		virtual const char *getVersion(void) const;

	private:
		void *pdata;
	};


	/**
	 * Create internal rendering interface.
	 * @param config
	 * @return non-null renderinginterface object.
	 */
	extern "C" AudioInterface* createInternalAudioInterface(IConfig* config);
}


#endif