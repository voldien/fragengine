#include"Windows/EditorWindow.h"
#include"Core/gtkconfig.h"

G_DEFINE_TYPE(FragViewEditorAppWindow, fragview_app_window, GTK_TYPE_APPLICATION_WINDOW)

static void
fragview_app_window_init (FragViewEditorAppWindow *app)
{
}

static void
fragview_app_window_class_init (FragViewEditorAppWindowClass *clasts){

	gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS (clasts),
	"/org/gtk/fragview-editor-app/window.ui");

	//gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (clasts), FragViewEditorAppWindow, stack);
}

FragViewEditorAppWindow *
fragview_window_new (FragViewEditorApp *app)
{
	//return g_object_new (FRAGVIEWEDITOR_APP _WINDOW_TYPE, "application", app, NULL);
}

void EditorWindow::showWindow(void) {
	//gtk_window_show(this->window);
}

void EditorWindow::hideWindow(void) {

}

void EditorWindow::closeWindow(void) {

}

void EditorWindow::setTitle(const char *title) {
	gtk_window_set_title(&this->window->parent.parent_instance, (const gchar*)title);
}

const char *EditorWindow::getTitle(void) const {
	return nullptr;
}

void EditorWindow::getPosition(int *x, int *y) const {

}

void EditorWindow::setPosition(int x, int y) {

}

void EditorWindow::setSize(int width, int height) {

}

void EditorWindow::getSize(int *width, int *height) const {

}


void EditorWindow::setIcon(void *pVoid) {

}

void *EditorWindow::getIcon(void) const {
	return nullptr;
}


fragview::Display* EditorWindow::getCurrentDisplay(void) const {
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

void EditorWindow::setBordered(bool borded) {

}

void EditorWindow::setMinimumSize(int width, int height) {

}

void EditorWindow::setMaximumSize(int width, int height) {

}

void EditorWindow::focus(void) {
	gtk_window_set_focus_visible(&this->window->parent.parent_instance, true);
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
