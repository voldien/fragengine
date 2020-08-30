#ifndef _FRAG_CORE_WINDOW_MANAGER_H_
#define _FRAG_CORE_WINDOW_MANAGER_H_ 1
#include"../Core/Display.h"
#include"../Core/Window.h"
#include"../Core/Ref.h"

namespace fragcore{

	/**
	 * 
	 */
	class FVDECLSPEC WindowManager {
	public:
		Display* getDisplay(int index);
		static int getNumDisplays(void);
		static Display* getAssociatedDisplay(Ref<Window>& window);
	};
}

#endif