#include"audio/AudioClip.h"
#include"audio/openal/internal_object_type.h"

using namespace fragview;

AudioClip::~AudioClip(void) {

}

AudioClip::AudioClip(void) {

}

intptr_t AudioClip::getNativePtr(void) const {
	ALClip *alClip = (ALClip *) this->getObject();
	return alClip->source;
}

unsigned long int AudioClip::getSampleRate(void) const {
	ALClip *alClip = (ALClip *) this->getObject();
	ALint sampleRate;
	alGetBufferi(alClip->source, AL_BITS, &sampleRate);
	return sampleRate;
}

unsigned long int AudioClip::getFrequency(void) const {
	ALClip *alClip = (ALClip *) this->getObject();
	ALint freq;
	alGetBufferi(alClip->source, AL_FREQUENCY, &freq);
	return freq;
}

AudioFormat AudioClip::getAudioFormat(void) const {
	ALClip *alClip = (ALClip *) this->getObject();
	ALint format;
	alGetBufferi(alClip->source, AL_INTERNAL_FORMAT_SOFT, &format);
	switch (format) {
		case AL_MONO_SOFT:
			return eMono;
		case AL_STEREO_SOFT:
			return eStero;
		case AL_REAR_SOFT:
			return eStero;
		default:
			return eMono;
	}
}

unsigned int AudioClip::getNumberChannels(void) const {
	ALClip *alClip = (ALClip *) this->getObject();
	ALint channels;
	alGetBufferi(alClip->source, AL_CHANNELS, &channels);
	return channels;
}

unsigned long AudioClip::getSize(void) const {
	ALClip *alClip = (ALClip *) this->getObject();
	ALint size;
	alGetBufferi(alClip->source, AL_SIZE, &size);
	return size;
}

float AudioClip::length(void) const {
	ALClip *alClip = (ALClip *) this->getObject();
	//TODO add equation for compute length from sample, format and size and etc.
	return 0;
}

void AudioClip::getData(void *pData, unsigned int nsamples, unsigned int offset) {
	//alBufferData
}

void AudioClip::setData(void *pData, unsigned int nsamples, unsigned int offset) {
	ALClip *alClip = (ALClip *) this->getObject();
	//alBufferData(alClip->source, 0, pdata, nsamples, freq);
	//alBufferData()
}

