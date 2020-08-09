#ifndef _FRAG_CORE_AUDIO_TYPES_H_
#define _FRAG_CORE_AUDIO_TYPES_H_ 1

namespace fragcore
{

	enum AudioFormat
	{
		eMono,
		eStero,
	};

	enum AudioSpeakerMode
	{
		Mono,
		Stero,
		Quad,
		Surround,
		Mode5Point1,
		Mode7Point1,
	};

	enum AudioDataMode
	{
		LoadedInMemory,
		Streaming,
		DecompressOnLoad
	};

}
#endif