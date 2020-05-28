#ifndef FRAGVIEW_SPLASHWINDOW_H_
#define FRAGVIEW_SPLASHWINDOW_H_ 1
#include "EditorWindow.h"

class SplashWindow : public EditorWindow {
public:
	SplashWindow(const char* imagePath);
	~SplashWindow(void);

	void setText(const char* text);
private:

};

#endif