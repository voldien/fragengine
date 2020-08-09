#include"Windows/GTKRendererWindow.h"
#include"Core/gtkconfig.h"
#include<gtk/gtkglarea.h>

void GTKRendererWindow::showWindow(void) {

}

void GTKRendererWindow::hideWindow(void) {

}

void GTKRendererWindow::swapBuffer(void) {

}

void GTKRendererWindow::getPosition(int *x, int *y) const {

}

void GTKRendererWindow::setPosition(int x, int y) {

}

void GTKRendererWindow::setSize(int width, int height) {

}

void GTKRendererWindow::getSize(int *width, int *height) const {

}

void GTKRendererWindow::vsync(bool state) {

}

fragcore::Display* GTKRendererWindow::getCurrentDisplay(void) const {
	return NULL;
}

float GTKRendererWindow::getGamma(void) const {
	return 0;
}

void GTKRendererWindow::setGamma(float gamma) {

}

static void
on_realize (GtkGLArea *area)
{
	// We need to make the context current if we want to
	// call GL API
	gtk_gl_area_make_current (area);

	// If there were errors during the initialization or
	// when trying to make the context current, this
	// function will return a #GError for you to catch
	if (gtk_gl_area_get_error (area) != NULL)
		return;

//	// You can also use gtk_gl_area_set_error() in order
//	// to show eventual initialization errors on the
//	// GtkGLArea widget itself
//	GError *internal_error = NULL;
//	init_buffer_objects (&error);
//	if (error != NULL)
//	{
//		gtk_gl_area_set_error (area, error);
//		g_error_free (error);
//		return;
//	}
//
//	init_shaders (&error);
//	if (error != NULL)
//	{
//		gtk_gl_area_set_error (area, error);
//		g_error_free (error);
//		return;
//	}
}

bool GTKRendererWindow::assertConfigAttributes(const fragview::IConfig *iConfig) {
	//	for (int i = 0; i < numReqConfigKeys; i++){
//	if(!iConfig->isSet(reqConfigKey[i]))
//
//	}
	return false;
}

void GTKRendererWindow::createWindow(int x, int y, int width, int height, const char *api) {
// create a GtkGLArea instance
	GtkWidget *gl_area = gtk_gl_area_new ();

// connect to the "render" signal
	g_signal_connect (gl_area, "render", G_CALLBACK (NULL), NULL);
}

void GTKRendererWindow::useWindow(void *data) {

	gtk_gl_area_make_current(data);
}

void GTKRendererWindow::closeWindow(void) {
	EditorWindow::closeWindow();
}

void GTKRendererWindow::setTitle(const char *title) {
	EditorWindow::setTitle(title);
}

void GTKRendererWindow::resizable(bool resizable) {
	EditorWindow::resizable(resizable);
}

const char *GTKRendererWindow::getTitle(void) const {
	return EditorWindow::getTitle();
}
