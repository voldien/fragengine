#include <Utils/StringUtil.h>
#include <FragViewCore.h>
#include"Windows/SplashWindow.h"

SplashWindow::SplashWindow(const char *imagePath) {
	GtkWidget *image, *window;
	GError *error = 0;
	GdkPixbuf *pixbuf;
	int width, height;

	width = 512;
	height = 512;

	/*  */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "FragView Editor");
	gtk_widget_set_size_request(window, width, height);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	pixbuf = gdk_pixbuf_new_from_file_at_size(imagePath, width, height, &error);
	if (!pixbuf) {
		throw fragview::RuntimeException(fvformatf("Error %s\n", error->message));
		g_error_free(error);
	}
	image = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	gtk_widget_set_size_request(image, width, height);
	// Resize based on the display size.
	GdkRectangle workarea = {0};

	height = gdk_monitor_get_height_mm(gdk_display_get_primary_monitor(gdk_display_get_default()));
	gtk_widget_set_size_request(image, width, height);
	gtk_container_add(GTK_CONTAINER(window), image);

	/* Connect the main window to the destroy and delete-event signals. */
//	g_signal_connect (G_OBJECT (window), "destroy",
//	                  G_CALLBACK (destroy), NULL);
//	g_signal_connect (G_OBJECT (window), "delete_event",
//	                  G_CALLBACK (delete_event), NULL);

	/*	wait intill screen get visible	*/
	gtk_widget_show_all(window);
	while (gtk_events_pending())
		gtk_main_iteration();

	//g_thread_exit(0);
	//g_thread_new
}

SplashWindow::~SplashWindow(void) {

}

void SplashWindow::setText(const char *text) {

}
