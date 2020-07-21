#ifndef _FV_AUDIODESC_H_
#define _FV_AUDIODESC_H_ 1
#include"../Def.h"
#include"../Core/IO/IO.h"
#include"../Core/Ref.h"
namespace fragview {

	enum AudioFormat {
		eStero,
		eMono,
	};

	enum AudioSpeakerMode {
		Mono,
		Stero,
		Quad,
		Surround,
		Mode5Point1,
		Mode7Point1,
	};

	typedef struct audio_source_desc_t {
		PVVector3 position;
	} AudioSourceDesc;


	typedef struct audio_clip_desc_t {

		/*  */
		void *source;           /*  */
		size_t size;            /*  */
		int sampleRate;         /*  */

		/*  */
		AudioFormat format;     /*  */
		unsigned int samples;   /*  */
		Ref<IO> io;
	} AudioClipDesc;

	typedef struct audio_listener_desc_t {
		PVVector3 position;
		PVQuaternion rotation;

	} AudioListenerDesc;

	typedef struct audio_reverb_desc_t{

	}AudioReverbDesc;


	typedef struct audio_geometry_desc_t{

	} AudioGeometryDesc;

}
#endif