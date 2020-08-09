


#ifndef _FRAG_CORE_AUDIO_DECODER_H_
#define _FRAG_CORE_AUDIO_DECODER_H_ 1
#include "../Def.h"
#include "../Core/SmartReference.h"
#include "../Core/Ref.h"
#include "../Core/IO/IO.h"
#include <ogg/ogg.h>
#include <opus/opus.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

namespace fragcore
{
	/**
	 * 
	 */
	class FVDECLSPEC AudioDecoder : public SmartReference
	{
	public:
		AudioDecoder(Ref<IO> &io);
		virtual ~AudioDecoder(void);

		virtual void seek(long int microseconds);

		void *getData(long int *size);

		void *getPage(int i);

	public:
		Ref<IO> io;
		OggVorbis_File *ov;
		//AudioFormat format;
		long int channels;
		long int samples;
	};
}


#endif