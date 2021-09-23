#include "Engine.h"
#include "FragCore.h"
#include <Renderer/IRenderer.h>
//#include<HpmCpp.h>
#include <Renderer/RendererWindow.h>
#include<hpmcpp/Hpm.hpp>
#include <Utils/TextureUtil.h>
#include <getopt.h>
#include <signal.h>

using namespace fragengine;
using namespace fragcore;

// Config* Engine::config = NULL;
// SceneManager* Engine::sceneManager = NULL;
// CommandController* Engine::controller = NULL;

static void catchsignal(int signal) {

	// SDL_Event event = {0};

	// switch (signal) {
	// 	case SIGINT:
	// 	case SIGQUIT:
	// 		event.type = SDL_QUIT;
	// 		SDL_PushEvent(&event);
	// 		break;
	// 	default:
	// 		break;
	// }

	// /*	Save current configuration file.	*/
	// /*	TODO relocate to on exit function callback.	*/
	// try {
	// 	Engine::getConfig()->save(".pvengine/settings.xml");
	// } catch (std::exception &ex) {
	// 	Debug::error("%s.\n", ex.what());
	// }
}

void Engine::init(int argc, const char **argv, SubSystem subsytem) {

	// int result;
	// SDL_version sdlver;

	Log::log(Log::Verbose, "Platform: %s\n", SystemInfo::getOperatingSystemName(SystemInfo::getOperatingSystem()));
	Log::log(Log::Verbose, "Memory: %d MB\n", SystemInfo::systemMemorySize());
	Log::log(Log::Verbose, "Cache line: %d bytes\n", SystemInfo::getCPUCacheLine());

	// /*	Set software interrupts.	*/
	// signal(SIGINT, catchsignal);
	// signal(SIGQUIT, catchsignal);
	initSubSystem(subsytem);

	// /*	Initialize SDL.	*/
	// SDL_GetVersion(&sdlver);
	// Debug::log("SDL version %d.%d.%d.\n", sdlver.major, sdlver.minor, sdlver.patch);

	// /*	Initialize the engine.	*/
	// result = SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS);
	// if (result != 0) {
	// 	throw std::runtime_error(format("Error %s", SDL_GetError()));
	// }

	// /*  Initialize HPM.  */
	// if (!Hpm::init((Hpm::HPMSIMD)this->config->get<int>("SIMD")))
	// 	throw RuntimeException("Failed to initialize the hpm library.");
	// Log::log(Log::Verbose, "HPM SIMD using: %s\n", hpm_get_simd_symbol(hpm_get_simd()));

	// /*  */
	// Engine::config = config;

	// Engine::sceneManager = new SceneManager();
}

void Engine::initSubSystem(SubSystem subsytem) {
	LIBHPM::Hpm::init(LIBHPM::Hpm::eHPM_DEFAULT);
	WindowManager::getInstance();
}

void Engine::quit(void) {}

void Engine::registerModule(Module &module) {}
void Engine::unregisterModule(Module &module) {}

const char *Engine::getVersion(void) { return FV_VERSION; }

RendererWindow *Engine::createWindow(IRenderer *renderer, const char *title, int x, int y, int width, int height) {
	Display *display = WindowManager::getInstance()->getDisplay(0);
	RendererWindow *window = renderer->createWindow(x, y, width, height);
	window->setTitle(title);

	/*	Load the default icon.	*/
	// /*  Set window properties.  */
	// SDL_SetWindowResizable((SDL_Window *) window, (SDL_bool)
	// config->get<bool>("window-resizable"));
	// SDL_SetWindowFullscreen((SDL_Window *) window, (SDL_bool)
	// config->get<bool>("fullscreen")); SDL_SetWindowBordered((SDL_Window *)
	// window, (SDL_bool) config->get<bool>("window-bordered"));

	/*  Start loading the icon. */
	std::string iconpath;
	void *iconBuffer;
	bool foundIcon = false;
	const IFileSystem *fileSystem = FileSystem::getFileSystem();

	/*  Search for the file path for the icon. Top bottom on most common location  */
	const char *iconFileName = "fragview.png";
	/*  Local directory of the executable.  */
	if (fileSystem->exists(iconFileName)) {
		iconpath = iconFileName;
		foundIcon = true;
	} else {
		// TODO determine based on platform for which directory to search.
		/*  Share directory.    */
		// iconpath = fvformatf("%s/%s", resourceConfig.get<const char *>("shaddir"), iconFileName);
		// if (fileSystem->exists(iconpath.c_str())) {
		// 	foundIcon = true;
		// }
	}

	ASyncHandle iconHandle = NULL;
	/*  Load icon.  */
	if (foundIcon) {
		unsigned int iconw, iconh, len;
		try {
			// TODO extract IO status.
			fileSystem->asyncWait(iconHandle);
			ASync::IOStatus status = fileSystem->getIOStatus(iconHandle);
			fileSystem->asyncClose(iconHandle);

			void *icon = TextureUtil::loadTextureData(iconBuffer, status.nbytes, &iconw, &iconh);
			if (icon && iconw > 0 && iconh > 0) {
				// TODO change type once it has been decided.
				window->setIcon(icon);
			}
			free(icon);
			free(iconBuffer);
		} catch (InvalidArgumentException &ex) {
			Log::error("Failed to load icon on path: %s\n", iconpath.c_str());
		}
	}

	return window;
}

// SceneManager *Engine::getSceneManager(void) {
// 	return Engine::sceneManager;
// }

// void Engine::setCommandController(CommandController *commandController) {
// 	Engine::controller = commandController;

// 	assert(commandController);

// 	/*	Create command controller for handling input for current scene.	*/
// 	commandController->setCommandMask(Command::eKeyBoardInput);
// 	commandController->setKeyMap(KeyMap::loadKeyMap(format("%s/%s", config->get<const char*>("shaddir"),
// config->get<const char*>("keymap")).c_str()));
// }

// Config *Engine::getConfig(void) {
//     return Engine::config;
// }
