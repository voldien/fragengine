
#ifndef _FRAG_CORE_AUDIOOBJECT_H_
#define _FRAG_CORE_AUDIOOBJECT_H_ 1
#include"Prerequisites.h"
#include"../Core/SmartReference.h"
#include"../Core/Ref.h"

namespace fragview {
	class AudioInterface; //TODO relocate.
	//TODO add based on a dynamic interface object class. Similar to the rendering and possibliy physic.
	/**
	 *
	 */
	class AudioObject : public SmartReference {
	public:
		FV_ALWAYS_INLINE AudioInterface *getAudio(void) const {
			return this->audioInterface;
		}

		FV_ALWAYS_INLINE void *getObject(void) {
			return this->pdata;
		}

		FV_ALWAYS_INLINE void *getObject(void) const {
			return this->pdata;
		}

		virtual intptr_t getNativePtr(void) const = 0;

	protected:  /*  */
		void *pdata;
		AudioInterface *audioInterface;   //TOOD change to ref.
	};
}


#endif