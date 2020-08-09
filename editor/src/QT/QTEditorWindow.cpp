#include"Windows/EditorWindow.h"
#include <QDialog>
#include<qt5/QtWidgets/QtWidgets>
#include <QWindow>
#include<QDialog>
#include <QMainWindow>

EditorWindow::EditorWindow(){
	this->window = new QMainWindow();

	QToolBar *myToolBar = new QToolBar();

	((QMainWindow *)this->window)->addToolBar(myToolBar);
	//QDialog
}

void EditorWindow::showWindow(void) {

	((QMainWindow *)this->window)->show();
}

void EditorWindow::hideWindow(void) {
	((QMainWindow *)this->window)->hide();
}

void EditorWindow::closeWindow(void) {
	((QMainWindow *)this->window)->close();
}

void EditorWindow::setTitle(const char *title){
	((QMainWindow *)this->window)->setWindowTitle(QString(title));
}

// ((QWindow *)this->window)
// 	->setParent
const char *EditorWindow::getTitle(void) const
{
	return nullptr;
}

void EditorWindow::getPosition(int *x, int *y) const {

}

void EditorWindow::setPosition(int x, int y) {
	//((QMainWindow *)this->window)->setPosition(x, y);
}

void EditorWindow::setSize(int width, int height) {
	//((QMainWindow *)this->window)->resize(width, height);
}

void EditorWindow::getSize(int *width, int *height) const {

}


void EditorWindow::setIcon(void *pVoid) {

}

void *EditorWindow::getIcon(void) const {
	return NULL;
}

fragcore::Display* EditorWindow::getCurrentDisplay(void) const {
	return NULL;
}

float EditorWindow::getGamma(void) const {
	return 0;
}

void EditorWindow::setGamma(float gamma) {

}

void EditorWindow::resizable(bool resizable) {

}

void EditorWindow::setFullScreen(bool fullscreen) {

}

void EditorWindow::isFullScreen(void) const{
	
}

void EditorWindow::setBordered(bool borded) {
	//((QWindow *)this->window)
}

void EditorWindow::setMinimumSize(int width, int height) {

}

void EditorWindow::setMaximumSize(int width, int height) {

}

void EditorWindow::focus(void) {
	
}

void EditorWindow::restore(void) {

}

void EditorWindow::maximize(void) {

}

void EditorWindow::minimize(void) {

}

intptr_t EditorWindow::getNativePtr(void) const {
	return 0;
}
