
#ifndef _FRAG_CORE_AUDIO_ENCODER_H_ 
#define _FRAG_CORE_AUDIO_ENCODER_H_ 1
#include"../Def.h"
#include"../Core/SmartReference.h"
#include "../Core/Ref.h"
#include"../Core/IO/IO.h"

namespace fragcore
{
	class FVDECLSPEC AudioEncoder : public SmartReference {
	public:
		AudioEncoder(Ref<IO> &io);
	};
} 


#endif