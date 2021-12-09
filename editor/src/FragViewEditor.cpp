#include "FragEditor.h"
#include "Windows/Label.h"
#include "Windows/SplashWindow.h"
#include <Core/Log.h>
#include <Core/SystemInfo.h>
#include <Engine.h>
#include <RendererFactory.h>

using namespace frageditor;
using namespace fragcore;
using namespace fragengine;

FragEditor::FragEditor(SplashWindow *splashWindow, int argc, const char **argv) {
	Engine::init(argc, argv, Engine::ALL);

	splashWindow->show();

	this->root = new EditorWindow();

	// QPixmap pixmap(":/splash.png");
	// QSplashScreen splash(pixmap);
	this->root->show();
	this->root->focus();
	this->root->setTitle("FragEditor");

	Label();
	// FragViewEditorApp *app;

	// this->config = Config::createConfig(argc, argv, Config::getConfigFilePath(argc, argv));

	// gtk_major_version()
	//	/*  Verbose information.    */
	Log::log(Log::Verbose, "Platform: %s\n", SystemInfo::getOperatingSystemName(SystemInfo::getOperatingSystem()));
	Log::log(Log::Verbose, "Memory: %d MB\n", SystemInfo::systemMemorySize());
	Log::log(Log::Verbose, "Cache line: %d bytes\n", SystemInfo::getCPUCacheLine());

	/*	Close and destroy splash window on finished.*/
	splashWindow->close();
	// delete splashWindow;
}

void FragEditor::run() {
	//	/*  Read first options.   */
	//	this->config = Config::createConfig(argc, argv, Config::getConfigFilePath(argc, argv));
	//
	//	/*  Verbose information.    */
	Log::log(Log::Verbose, "Platform: %s\n", SystemInfo::getOperatingSystemName(SystemInfo::getOperatingSystem()));
	Log::log(Log::Verbose, "Memory: %d MB\n", SystemInfo::systemMemorySize());
	Log::log(Log::Verbose, "Cache line: %d bytes\n", SystemInfo::getCPUCacheLine());

	/*  Create rendering interface. */
	const IConfig &renderConfig = config->getSubConfig("render-driver");
	this->renderer = Ref<IRenderer>(
		RenderingFactory::createRendering(config->get<const char *>("renderer-dynamicInterface"), &renderConfig));
	Log::log(Log::Verbose, "Loading Renderer: %s-%s\n", (*this->renderer)->getName().c_str(),
			 (*this->renderer)->getVersion());
	Log::log(Log::Verbose, "API Internal API version: %s\n", (*this->renderer)->getAPIVersion());
	//(*this->renderer)->setVSync(renderConfig.get<bool>("v-sync"));

	//	/*  Create task scheduler.  */

	//	this->sch = (schTaskSch *) malloc(sizeof(schTaskSch));
	//	int sch = schCreateTaskPool(this->sch, 2, SCH_FLAG_NO_AFM, 48);
	//	if (sch != SCH_OK)
	//		throw RuntimeException(schErrorMsg(status));
	//	sch = schRunTaskSch(this->sch);
	//	if (sch != SCH_OK)
	//		throw RuntimeException(schErrorMsg(status));
	//
	//	//TODO add support for some kind of filesystem.
	//	/*  Create file notify.    */
	//	if (this->config->get<bool>("notify-file"))
	//		this->notify = new FileNotify(this->sch);
}
