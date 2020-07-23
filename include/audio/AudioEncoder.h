
#ifndef _FRAG_CORE_AUDIO_ENCODER_H_ 
#define _FRAG_CORE_AUDIO_ENCODER_H_ 1
#include"../Def.h"
#include"../Core/SmartReference.h"

namespace fragview
{
	class FVDECLSPEC AudioEncoder : public SmartRefrence {
		public:
			AudioEncoder(Ref<IO> &io);
	};
} 


#endif