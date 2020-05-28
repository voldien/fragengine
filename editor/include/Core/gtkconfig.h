#ifndef FRAGVIEW_GTKCONFIG_H_
#define FRAGVIEW_GTKCONFIG_H_ 1
#include<gtk/gtk.h>
#include<gdk/gdk.h>
#include<gdk/gdkx.h>

struct _FragViewEditorApp {
	GtkApplication parent;
};

struct _FragViewEditorAppWindow
{
	GtkApplicationWindow parent;
};

/**
 *
 */
#define FRAGVIEW_GET_APP_TYPE (fragview_editor_app_get_type ())
G_DECLARE_FINAL_TYPE (FragViewEditorApp, fragview_editor_app, FRAGVIEWEDITOR, APP, GtkApplication)

FragViewEditorApp     *fragview_editor_app_new(void);


#define FRAGVIEW_EDITOR_APP_WINDOW_TYPE (fragview_editor_app_window_get_type ())
G_DECLARE_FINAL_TYPE (FragViewEditorAppWindow, fragview_app_window, FRAGVIEWEDITOR, APP_WINDOW, GtkApplicationWindow)

FragViewEditorAppWindow       *example_app_window_new          (FragViewEditorApp *app);
void                    example_app_window_open         (FragViewEditorAppWindow *win,
                                                         GFile            *file);


#endif