


#ifndef _FRAG_CORE_AUDIO_DECODER_H_
#define _FRAG_CORE_AUDIO_DECODER_H_ 1
#include "../Def.h"
#include "../Core/SmartReference.h"
#include "../Core/Ref.h"
#include "../Core/IO/IO.h"

namespace fragview
{
	class FVDECLSPEC AudioDecoder : public SmartReference
	{
	public:
		AudioDecoder(Ref<IO> &io);

		virtual void seek(int i);

		void *getData(long int *size);

		virtual void readHeader(void);

	public:
		Ref<IO> io;
		//AudioFormat format;
		long int channels;
		long int format;
		long int samples;
		long int sampleRate;
	};
}


#endif