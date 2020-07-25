#ifndef _FRAG_CORE_AUDIODESC_H_
#define _FRAG_CORE_AUDIODESC_H_ 1
#include "../Def.h"
#include"AudioTypes.h"
#include "../Core/IO/IO.h"
#include "../Core/Ref.h"

namespace fragview
{
	typedef struct audio_source_desc_t
	{
		PVVector3 position;
	} AudioSourceDesc;

	class AudioDecoder;
	typedef struct audio_clip_desc_t
	{

		/*  */
		void *source;	/*  */
		size_t size;	/*  */
		int sampleRate; /*  */

		/*  */
		AudioFormat format;	  /*  */
		unsigned int samples; /*  */
		bool streaming;		  //TODO change to a enum.
		Ref<AudioDecoder> decoder;
		AudioDataMode datamode;
	} AudioClipDesc;

	typedef struct audio_listener_desc_t
	{
		PVVector3 position;
		PVQuaternion rotation;

	} AudioListenerDesc;

	typedef struct audio_reverb_desc_t
	{

	} AudioReverbDesc;

	typedef struct audio_geometry_desc_t
	{

	} AudioGeometryDesc;

}

#endif