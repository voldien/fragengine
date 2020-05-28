#include"audio/AudioInterface.h"
#include"audio/openal/internal_object_type.h"
#include <audio/AudioClip.h>
#include <audio/AudioSource.h>
#include "audio/AudioClip.h"
#include <audio/AudioPhysicalDevice.h>
#include"audio/AudioListener.h"
#include <Utils/StringUtil.h>
#include <FragViewCore.h>

using namespace fragview;
//
//void AudioInterface::initAllocate(InitAllocateTableInfo *table) {
//	table->interfacetype = eAudio;
//
//}

AudioInterface::AudioInterface(IConfig *config) {
	this->setName("OpenAL");

	OpenALInterfaceObject *alDevice = (OpenALInterfaceObject *) malloc(sizeof(OpenALInterfaceObject));
	this->pdata = alDevice;

	memset(alDevice, 0, sizeof(OpenALInterfaceObject));
	assert(alDevice);

	//TODO add support
	//const char* device = config->get<const char*>("device");

	const ALchar *defaultDevice = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	AudioPhysicalDevices audioPhysicalDevices;
	audioPhysicalDevices.setName(defaultDevice);
	setAudioDevice(audioPhysicalDevices);
}


AudioInterface::~AudioInterface(void) {
	OpenALInterfaceObject *audio = (OpenALInterfaceObject *) this->pdata;

	/*  Unbind and release context. */
	alcMakeContextCurrent(NULL);
	alcDestroyContext(audio->context);

	/*  Release device. */
	alcCloseDevice(audio->device);
	free(audio);
}

static inline ALenum to_al_format(short channels, short samples) {
	bool stereo = (channels > 1);

	switch (samples) {
		case 16:
			if (stereo)
				return AL_FORMAT_STEREO16;
			else
				return AL_FORMAT_MONO16;
		case 8:
			if (stereo)
				return AL_FORMAT_STEREO8;
			else
				return AL_FORMAT_MONO8;
		default:
			return -1;
	}
}



AudioClip *AudioInterface::createAudioClip(AudioClipDesc *desc) {
	OpenALInterfaceObject *audio = (OpenALInterfaceObject *) this->pdata;

	ALuint buffer;

	alGenBuffers((ALuint) 1, &buffer);

	alBufferData(buffer, to_al_format(desc->format, desc->samples),
	             desc->source, desc->size, desc->sampleRate);


	AudioClip *audioClip = new AudioClip();
	ALSource* source = new ALSource();

	source->source = buffer;
	audioClip->pdata  = source;

	return audioClip;
}

void AudioInterface::deleteAudioClip(AudioClip *AudioClip) {
	OpenALInterfaceObject *audio = (OpenALInterfaceObject *) this->pdata;

	alDeleteBuffers(1, NULL);
}

AudioSource *AudioInterface::createAudioSource(AudioSourceDesc *desc) {

	ALuint source;
	alGenSources(1, &source);


	alSourcef(source, AL_PITCH, 1);
// check for errors
	alSourcef(source, AL_GAIN, 1);
// check for errors
	alSource3f(source, AL_POSITION, 0, 0, 0);
// check for errors
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
// check for errors
	alSourcei(source, AL_LOOPING, AL_FALSE);

	AudioSource* audioSource = new AudioSource();
	ALSource* alSource = new ALSource();
	audioSource->pdata = alSource;
	alSource->source = source;

	return audioSource;
	//return obtainMappedObject<AudioSource>(NULL);
}

void AudioInterface::deleteAudioSource(AudioSource *audioSource) {

}

AudioReverb *AudioInterface::createAudioReverb(AudioReverbDesc *desc) {
	OpenALInterfaceObject *audio = (OpenALInterfaceObject *) this->pdata;
	if(!audio->supportEffects)
		throw RuntimeException("");


	return nullptr;
}

void AudioInterface::deleteAudioReverb(AudioReverb *reverb) {

}

AudioListener *AudioInterface::createAudioListener(AudioListenerDesc *desc) {
	//alGetListener3f()
	OpenALInterfaceObject *audio = (OpenALInterfaceObject *) this->pdata;


	AudioListener* listener = new AudioListener();
	//return obtainMappedObject<AudioListener>(NULL);
	listener->setPosition(PVVector3::zero());
	listener->setVelocity(PVVector3::zero());
	listener->setOrientation(PVQuaternion());
}

void AudioInterface::deleteAudioListener(AudioListener *listener) {
	delete listener;
}

void AudioInterface::setAudioListener(AudioListener *listener) {

}

std::vector<AudioPhysicalDevices> AudioInterface::getDevices(void) const {
	OpenALInterfaceObject *audio = (OpenALInterfaceObject *) this->pdata;
	std::vector<AudioPhysicalDevices> listDevices;

	const ALCchar *devices;
	const ALCchar *mices;
	if (alcIsExtensionPresent(NULL, "ALC_enumeration_EXT") == AL_TRUE) {
		if (alcIsExtensionPresent(NULL, "ALC_enumerate_all_EXT") == AL_FALSE)
			devices = (char *) alcGetString(NULL, ALC_DEVICE_SPECIFIER);
		else
			devices = (char *) alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);

		mices = (char *)alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
	}

	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	while (device && *device != '\0' && next && *next != '\0') {
		AudioPhysicalDevices audioPhysicalDevices = AudioPhysicalDevices();
		audioPhysicalDevices.setName(device);
		listDevices.push_back(audioPhysicalDevices);

		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}

	return listDevices;
}

void AudioInterface::setAudioDevice(const AudioPhysicalDevices &device) {
	OpenALInterfaceObject *audio = (OpenALInterfaceObject *) this->pdata;
	ALint attribs[4] = { 0 };

	if (alcGetCurrentContext() != NULL) {
		ALCcontext *context = alcGetCurrentContext();
		ALCdevice *curDevice = alcGetContextsDevice(context);

		// Same device.
		if (strcmp(alcGetString(curDevice, ALC_DEVICE_SPECIFIER), device.getName().c_str()) == 0)
			return;

		// Not same device. continue with selecting audio device.
	}

	if (alcGetCurrentContext() != NULL) {
		/*  */
		if (!alcCloseDevice(audio->device))
			throw RuntimeException(fvformatf("Failed to open audio device %s", device.getName().c_str()));
	}

	/*  */
	audio->device = alcOpenDevice(device.getName().c_str());
	if (!audio->device)
		throw RuntimeException(fvformatf("Failed to open audio device %s", device.getName().c_str()));


	if(alcIsExtensionPresent(audio->device, ALC_EXT_EFX_NAME)){

		audio->alGenEffects=(LPALGENEFFECTS)       alGetProcAddress("alGenEffects");
		audio->alDeleteEffects=(LPALDELETEEFFECTS)      alGetProcAddress("alDeleteEffects");
		audio->alIsEffect=(LPALISEFFECT)       alGetProcAddress("alIsEffect");

		if (!(audio->alGenEffects && audio->alDeleteEffects && audio->alIsEffect))
			audio->supportEffects = false;

		/* Use Context creation hint to request 4 Auxiliary */ /* Sends per Source */
		attribs[0] = ALC_MAX_AUXILIARY_SENDS;
		attribs[1] = 4;

		audio->supportEffects = true;
	}

	/*  Create context. */
	audio->context = alcCreateContext(audio->device, attribs);
	if (!audio->context)
		throw RuntimeException(fvformatf("Failed to create audio context for device %s", device.getName().c_str()));

	if (!alcMakeContextCurrent(audio->context))
		throw RuntimeException(fvformatf("Failed to make current audio device %s", device.getName().c_str()));

	//alcGetIntegerv(audio->device, ALC_MAX_AUXILIARY_SENDS, 1, &iSends);
}

const char *AudioInterface::getVersion(void) const {
	return "";
}

const AudioPhysicalDevices &AudioInterface::getAudioDevice(void) const {
	return AudioPhysicalDevices();
}


extern "C" AudioInterface *createInternalAudioInterface(IConfig *config) {
	return new AudioInterface(config);
}
