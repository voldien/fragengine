#include<FragCore.h>
#include"Windows/SplashWindow.h"

using namespace frageditor;

SplashWindow::SplashWindow(const char *imagePath) {

	this->setBordered(false);
	this->setSize(1280, 720);
}

SplashWindow::~SplashWindow() {

}

void SplashWindow::setText(const char *text) {

}
