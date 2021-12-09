#include "FragEditor.h"
#include "Windows/SplashWindow.h"
#include <QApplication>
#include <QPixmap>
#include <signal.h>
using namespace frageditor;

QCoreApplication *createApplication(int &argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
		if (!qstrcmp(argv[i], "-no-gui"))
			return new QCoreApplication(argc, argv);
	}
	return new QApplication(argc, argv);
}

void sharedLogOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {}

int main(int argc, char **argv) {

	/*  Add debug functionality for signal associated with error.    */

	try {
		QCoreApplication::setAttribute(Qt::AA_X11InitThreads);

		qInstallMessageHandler(sharedLogOutput);

		QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
		QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

		QScopedPointer<QCoreApplication> app(createApplication(argc, argv));

		/*	Splash dialog.	*/
		QPixmap pixmap(":/logo.svg");
		SplashWindow splashWindow("/home/voldie/Pictures/neko.jpg");
		// SplashDialog splash(pixmap);
		// splash.show();

		// app.setStyle(QStyleFactory::create("Fusion"));
		//	app.setStyle();
		// splash.showMessage("Loading Style");
		QCoreApplication::processEvents();

		if (qobject_cast<QApplication *>(app.data())) {
			// start GUI version...
		} else {
			// start non-GUI version...
		}

		FragEditor fragViewEditor(&splashWindow, argc, (const char **)argv);
		fragViewEditor.run();

		app->exec();

		return EXIT_SUCCESS;
	} catch (std::exception &ex) {
		std::cerr << cxxexcept::getStackMessage(ex);
		return EXIT_FAILURE;
	}
}
