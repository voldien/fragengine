#include<fragview/FragViewCore.h>
#include <fragview/audio/AudioClip.h>
#include <fragview/audio/AudioSource.h>
#include <fragview/audio/AudioListener.h>
#include <fragview/audio/AudioDecoder.h>
#include<opus/opus.h>
#include<ogg/ogg.h>
#include<hpmcpp/HpmCpp.h>

using namespace fragview;
int main(int argc, const char **argv)
{
	IConfig config;
	
	Ref<AudioInterface> iaudio = Ref<AudioInterface>(AudioFactory::createAudioInterface(AudioFactory::OpenAL, &config));

	/*  Initialize HPM.  */
	if (!Hpm::init(Hpm::eHPM_SSE2))
		throw RuntimeException("Failed to initialize the hpm library.");

	Ref<IScheduler> sch = Ref<IScheduler>(NULL);
	FileSystem *fileSystem = FileSystem::createFileSystem(sch);

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
	source_desc.position = PVVector3::zero();
	Ref<AudioSource> audioSource = Ref<AudioSource>(iaudio->createAudioSource(&source_desc));

	AudioClipDesc clip_desc = {};
	Ref<IO> f = Ref<IO>(fileSystem->openFile(argv[1], IO::READ));
	AudioDecoder decoder(f);
	decoder.readHeader();
//	clip_desc.source = decoder.getData(&clip_desc.size);
	clip_desc.samples = 44100;
	clip_desc.sampleRate = 160000;
	clip_desc.format = AudioFormat::eStero;

	Ref<AudioClip> clip = Ref<AudioClip>(iaudio->createAudioClip(&clip_desc));
	audioSource->setClip(*clip);
	audioSource->play();

	while (audioSource->isPlaying()){
		sleep(1);
	}

	//delete iaudio;
}