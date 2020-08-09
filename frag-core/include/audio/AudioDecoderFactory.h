

#ifndef _FRAG_CORE_AUDIO_FACTORY_H_
#define _FRAG_CORE_AUDIO_FACTORY_H_ 1
#include"../Def.h"
#include"../Core/IO/IO.h"
#include"../Core/Ref.h"
#include"AudioDecoderFactory.h"

namespace fragcore {

	enum AudioDecoderCodec
	{
		Ogg,
		Mp3,
		Wav,
	};

	class FVDECLSPEC AudioDecoderFactory {
		public:
			AudioDecoder *createDecoder(AudioDecoderCodec codec, Ref<IO> &io);

		private: /*	Prevent one from creating an instance of this class.	*/
			AudioDecoderFactory(void) = default;
			AudioDecoderFactory(const AudioDecoderFactory &other) = default;
	};
}
#endif