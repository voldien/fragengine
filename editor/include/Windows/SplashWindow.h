#ifndef _FRAGVIEW_SPLASHWINDOW_H_
#define _FRAGVIEW_SPLASHWINDOW_H_ 1
#include "DialogWindow.h"

class SplashWindow : public DialogWindow
{
public:
	SplashWindow(const char* imagePath);
	~SplashWindow(void);

	void setText(const char* text);
private:
};

#endif