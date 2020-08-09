#include"audio/AudioInterface.h"
#include"audio/openal/internal_object_type.h"
#include <audio/AudioClip.h>
#include <audio/AudioSource.h>
#include "audio/AudioClip.h"
#include <audio/AudioPhysicalDevice.h>
#include "audio/AudioListener.h"
#include "Core/Math.h"
#include <Utils/StringUtil.h>
#include <FragViewCore.h>

using namespace fragcore;
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
	//AL_SOURCE_TYPE
	//TODO add support
	//const char* device = config->get<const char*>("device");

	const ALchar *defaultDevice = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	AudioPhysicalDevice audioPhysicalDevices;
	audioPhysicalDevices.setName(defaultDevice);
	setAudioDevice(audioPhysicalDevices);

	Ref<IScheduler> scheduler = Ref<IScheduler>(new TaskScheduler(Math::clamp(SystemInfo::getCPUCoreCount(), 1, 2), 48));
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

#include<AL/alext.h>
static inline ALenum to_al_format(short channels, short samples) {
	bool stereo = (channels > 1);
//	AL_FORMAT_STER
	switch (samples) {
		case 32:
			if(stereo)
				return AL_FORMAT_STEREO_FLOAT32;
			else
				return AL_FORMAT_MONO_FLOAT32;
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
			throw RuntimeException("Invalid format.");
	}
}

static const char* openAlErrorToString(int err)
{
	switch (err)
	{
	case AL_NO_ERROR:
		return "AL_NO_ERROR";
	case AL_INVALID_ENUM:
		return "AL_INVALID_ENUM";
	case AL_INVALID_VALUE:
		return "AL_INVALID_VALUE";
	case AL_OUT_OF_MEMORY:
		return "AL_OUT_OF_MEMORY";
	default:
		return "Unknown error code";
	}
}

AudioClip *AudioInterface::createAudioClip(AudioClipDesc *desc){
	OpenALInterfaceObject *audio = (OpenALInterfaceObject *)this->pdata;

	ALuint buffer;

	alGenBuffers((ALuint)1, &buffer);

	/*	TODO based on the loading type.	*/
	if(desc->datamode == AudioDataMode::LoadedInMemory){
		long int size;
		void *data = desc->decoder->getData(&size);

		/*	*/
		alBufferData(buffer, to_al_format(desc->format, desc->samples),
					data, size, desc->sampleRate);

		free(data);
	}
	else{

	}

	int err = alGetError();
	if (err != ALC_NO_ERROR)
		throw RuntimeException(fvformatf("%s", openAlErrorToString(err)));

	AudioClip *audioClip = new AudioClip();
	ALClip *source = new ALClip();

	Ref<AudioDecoder> decoder;
	source->source = buffer;
	source->decoder = desc->decoder;
	audioClip->pdata = source;

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

AudioCapture *AudioInterface::createAudioCapture(void){
	return NULL;
}

std::vector<AudioPhysicalDevice> AudioInterface::getDevices(void) const
{
	OpenALInterfaceObject *audio = (OpenALInterfaceObject *) this->pdata;
	std::vector<AudioPhysicalDevice> listDevices;

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
		AudioPhysicalDevice audioPhysicalDevices = AudioPhysicalDevice();
		audioPhysicalDevices.setName(device);
		listDevices.push_back(audioPhysicalDevices);

		/*	*/
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}

	return listDevices;
}

void AudioInterface::setAudioDevice(const AudioPhysicalDevice &device)
{
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

const AudioPhysicalDevice &AudioInterface::getAudioDevice(void) const
{
	ALCdevice* dv = alcGetContextsDevice(alcGetCurrentContext());
	AudioPhysicalDevice device = AudioPhysicalDevice();
	device.setName(alcGetString(dv, ALC_DEVICE_SPECIFIER));

	return device;
}

extern "C" AudioInterface *createInternalAudioInterface(IConfig *config) {
	return new AudioInterface(config);
}
