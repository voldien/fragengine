#include"audio/AudioListener.h"
#include"audio/openal/internal_object_type.h"

using namespace fragview;

intptr_t AudioListener::getNativePtr(void) const {
	return 0;
}

void AudioListener::setVolume(float volume) {
	alListenerf(AL_GAIN, volume);
}

float AudioListener::getVolume(void) const {
	float volume;
	alGetListenerf(AL_GAIN, &volume);
	return volume;
}

void AudioListener::pause(bool pause) {

}

void AudioListener::setPosition(const PVVector3 &position) {
	const PVVector3 *p = &position;
	alListenerfv(AL_POSITION, (const ALfloat *)&p[0]);
}

const PVVector3 &AudioListener::getPosition(void) const {
	PVVector3 position;

	alGetListenerfv(AL_POSITION, &position[0]);
	return position;
}

void AudioListener::setVelocity(const PVVector3 &velocity) {
	const PVVector3 *v = &velocity;
	alListenerfv(AL_VELOCITY, (const ALfloat *)&v[0]);
}

const PVVector3 &AudioListener::getVelocity(void) const {
	PVVector3 velocity;
	alGetListenerfv(AL_VELOCITY, &velocity[0]);
	return velocity;
}

void AudioListener::setOrientation(const PVQuaternion &orientation) {
	PVVector3 forward = orientation.getVector(PVVector3::forward());
	PVVector3 up = orientation.getVector(PVVector3::up());

	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListenerfv(AL_ORIENTATION, (const ALfloat *) &forward[0]);
}

const PVQuaternion &AudioListener::getOrientation(void) const {
	PVQuaternion orientation;
	ALfloat listenerOri[6];
	alGetListenerfv(AL_ORIENTATION, listenerOri);
	return orientation;
}

AudioListener::AudioListener(void) {

}

AudioListener::~AudioListener(void) {

}
