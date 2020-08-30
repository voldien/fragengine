#ifndef _FRAG_EDITOR_SPLASHWINDOW_H_
#define _FRAG_EDITOR_SPLASHWINDOW_H_ 1
#include "DialogWindow.h"

namespace frageditor{

	class SplashWindow : public DialogWindow
	{
	public:
		SplashWindow(const char* imagePath);
		~SplashWindow(void);

		void setText(const char* text);
	private:
		
	};
}
#endif