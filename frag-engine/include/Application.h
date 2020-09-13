
#ifndef _FRAG_ENGINE_APPLICATION_H_
#define _FRAG_ENGINE_APPLICATION_H_ 1
#include "Engine.h"

namespace fragengine {

	/**
	 * 
	 */
	class FVDECLSPEC Application {
	public:
		static void focus(void);
		static void unFocus(void);
		static void quit(int status = 0);
		static void captureScreenshot(const char* cfilename, float superSize);

	};
}

#endif

