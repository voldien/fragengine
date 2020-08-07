
#ifndef _FRAG_CORE_MODULE_H_
#define _FRAG_CORE_MODULE_H_ 1
#include"SmartReference.h"

namespace fragview {
	/**
	 * 
	 */
	class FVDECLSPEC Module : SmartReference {
		public:
			virtual void OnInitialization(void);
			virtual void OnDestruction(void);
			/**/
	};
}

#endif