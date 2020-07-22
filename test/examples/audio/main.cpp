#include<fragview/FragViewCore.h>
#include <fragview/audio/AudioClip.h>
#include <fragview/audio/AudioSource.h>
#include <fragview/audio/AudioListener.h>

using namespace fragview;
int main(int argc, const char **argv)
{
	IConfig config;
	
	Ref<AudioInterface> iaudio = Ref<AudioInterface>(AudioFactory::createAudioInterface(AudioFactory::OpenAL, &config));

	std::vector<AudioPhysicalDevices> devices = iaudio->getDevices();
	std::vector<AudioPhysicalDevices>::iterator it = devices.begin();

	for (; it != devices.end(); it++){
		printf(fvformatf("%s\n", (*it).getName().c_str()).c_str());
	}

	AudioListenerDesc list_desc = {
		.position = PVVector3(0,0,0),
		.rotation = PVQuaternion::identity()
	};
	Ref<AudioListener> listener = Ref<AudioListener>(iaudio->createAudioListener(&list_desc));

	AudioSourceDesc source_desc = {};
	Ref<AudioSource> audioSource = Ref<AudioSource>(iaudio->createAudioSource(&source_desc));

	AudioClipDesc clip_desc = {};
	Ref<AudioClip> clip = Ref<AudioClip>(iaudio->createAudioClip(&clip_desc));
	audioSource->setClip(*clip);
	audioSource->play();

	while (audioSource->isPlaying()){
		sleep(1);
	}

	
}