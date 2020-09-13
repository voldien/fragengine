#include <execinfo.h>
#include <signal.h>
#include "Windows/SplashWindow.h"
#include"FragEditor.h"
#if defined(FRAG_GTK_WINDOW_MANAGER)
//#include <Core/gtkconfig.h>
#elif defined(FRAG_QT_WINDOW_MANAGER)
#include <QApplication>
#endif

using namespace frageditor;

void *createSplashScreen(char *image_path, int time, int width, int height) {

// 	GtkWidget *image, *window;
// 	GError *error = 0;
// 	GdkPixbuf *pixbuf;

// 	if (width == -1 && height == -1) {
// 		// get the default size
// 	}

// 	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
// 	gtk_window_set_title(GTK_WINDOW(window), "Shader Editor");
// 	gtk_widget_set_size_request(window, width, height);
// 	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
// 	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
// 	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
// 	pixbuf = gdk_pixbuf_new_from_file_at_size(image_path, width, height, &error);
// 	if (!pixbuf) {
// 		g_print("Error %s\n", error->message);
// 		g_error_free(error);
// 	}
// 	image = gtk_image_new_from_pixbuf(pixbuf);
// 	g_object_unref(pixbuf);
// 	gtk_widget_set_size_request(image, width, height);
// 	gtk_container_add(GTK_CONTAINER(window), image);

// //	/* Connect the main window to the destroy and delete-event signals. */
// //	g_signal_connect (G_OBJECT (window), "destroy",
// //	                  G_CALLBACK (destroy), NULL);
// //	g_signal_connect (G_OBJECT (window), "delete_event",
// //	                  G_CALLBACK (delete_event), NULL);


// 	/*	wait intill screen get visible	*/
// 	gtk_widget_show_all(window);
// 	gtk_main();
// 	//g_thread_new
}

void handler(int sig) {
	switch (sig) {
		case SIGABRT:
		case SIGILL:
		case SIGTERM:
		case SIGSEGV: {
			void *array[128];
			const int nArrays = sizeof(array) / sizeof(array[0]);
			size_t size;

			// get void*'s for all entries on the stack
			size = backtrace(array, nArrays);

			// print out all the frames to stderr
			fprintf(stderr, "Error: signal %d:\n", sig);
			backtrace_symbols_fd(array, size, STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		default:
			break;
	}
}

#if defined(FRAG_QT_WINDOW_MANAGER)
QCoreApplication *createApplication(int &argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		if (!qstrcmp(argv[i], "-no-gui"))
			return new QCoreApplication(argc, argv);
	}
	return new QApplication(argc, argv);
}
#endif

int main(int argc, char **argv) {

	/*  Add debug functionality for signal associated with error.    */
	signal(SIGABRT, handler);
	signal(SIGILL, handler);
	signal(SIGTERM, handler);
	signal(SIGSEGV, handler);

	try {

		/* init gtk */
		#ifdef FRAG_GTK_WINDOW_MANAGER
		//gtk_init(&argc, &argv);
		#elif defined(FRAG_QT_WINDOW_MANAGER)
		QScopedPointer<QCoreApplication> app(createApplication(argc, argv));

		if (qobject_cast<QApplication *>(app.data()))
		{
			// start GUI version...
		}
		else
		{
			// start non-GUI version...
		}
#endif
		SplashWindow splashWindow("/home/voldie/Pictures/neko.jpg");
		FragEditor fragViewEditor(&splashWindow, argc, (const char **) argv);
		fragViewEditor.run();
		#if defined(FRAG_QT_WINDOW_MANAGER)
		app->exec();
#endif
		return EXIT_SUCCESS;
	} catch (fragcore::IException &ex) {
		std::cerr << "Internal exception: " << ex.getName() << std::endl;
		std::cerr << ex.what() << std::endl;
		std::cerr << ex.getBackTrace() << std::endl;
		return EXIT_FAILURE;

	} catch (std::exception &ex) {
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
}