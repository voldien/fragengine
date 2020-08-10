#include <Utils/StringUtil.h>
#include <FragViewCore.h>
#include"Windows/SplashWindow.h"

using namespace frageditor;

SplashWindow::SplashWindow(const char *imagePath) {

	this->setBordered(false);
	this->setSize(1280, 720);
}

SplashWindow::~SplashWindow(void) {

}

void SplashWindow::setText(const char *text) {

}
