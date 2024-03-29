#include "Windows/EditorWindow.h"
#include <QDialog>
#include <QDialog>
#include <QMainWindow>
#include <QWindow>
#include <qt5/QtWidgets/QtWidgets>
using namespace frageditor;

EditorWindow::EditorWindow() {
	this->window = new QMainWindow();

	QToolBar *myToolBar = new QToolBar();

	((QMainWindow *)this->window)->addToolBar(myToolBar);
	// QDialog
}

void EditorWindow::show() { ((QMainWindow *)this->window)->show(); }

void EditorWindow::hide() { ((QMainWindow *)this->window)->hide(); }

void EditorWindow::close() { ((QMainWindow *)this->window)->close(); }

void EditorWindow::setTitle(const std::string &title) {
	((QMainWindow *)this->window)->setWindowTitle(QString(title.c_str()));
}

// ((QWindow *)this->window)
// 	->setParent
std::string EditorWindow::getTitle() const { return ""; }

void EditorWindow::getPosition(int *x, int *y) const {}

void EditorWindow::setPosition(int x, int y) {
	//((QMainWindow *)this->window)->setPosition(x, y);
}

void EditorWindow::setSize(int width, int height) {
	//((QMainWindow *)this->window)->resize(width, height);
}

void EditorWindow::getSize(int *width, int *height) const {}

void EditorWindow::setIcon(void *pVoid) {}

void *EditorWindow::getIcon() const { return NULL; }

fragcore::Display *EditorWindow::getCurrentDisplay() const { return NULL; }

float EditorWindow::getGamma() const { return 0; }

void EditorWindow::setGamma(float gamma) {}

void EditorWindow::resizable(bool resizable) {}

void EditorWindow::setFullScreen(bool fullscreen) {}
void EditorWindow::setFullScreen(fragcore::Display &display) {}

bool EditorWindow::isFullScreen() const {}

void EditorWindow::setBordered(bool borded) {
	//((QWindow *)this->window)
}

void EditorWindow::setMinimumSize(int width, int height) {}
void EditorWindow::getMinimumSize(int *width, int *height) {}

void EditorWindow::setMaximumSize(int width, int height) {}
void EditorWindow::getMaximumSize(int *width, int *height) {}

void EditorWindow::focus() {}

void EditorWindow::restore() {}

void EditorWindow::maximize() {}

void EditorWindow::minimize() {}

intptr_t EditorWindow::getNativePtr() const { return 0; }
