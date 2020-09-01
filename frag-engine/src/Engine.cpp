#include"Engine.h"
#include<Renderer/IRenderer.h>

#include<HpmCpp.h>
#include<SDL2/SDL.h>
#include<getopt.h>
#include<signal.h>
#include<Utils/StringUtil.h>


// Config* Engine::config = NULL;
// SceneManager* Engine::sceneManager = NULL;
// CommandController* Engine::controller = NULL;

// static void catchsignal(int signal) {

// 	SDL_Event event = {0};

// 	switch (signal) {
// 		case SIGINT:
// 		case SIGQUIT:
// 			event.type = SDL_QUIT;
// 			SDL_PushEvent(&event);
// 			break;
// 		default:
// 			break;
// 	}

// 	/*	Save current configuration file.	*/
// 	/*	TODO relocate to on exit function callback.	*/
// 	try {
// 		Engine::getConfig()->save(".pvengine/settings.xml");
// 	} catch (std::exception &ex) {
// 		Debug::error("%s.\n", ex.what());
// 	}
// }

// void Engine::init(int argc, const char **argv, Config *config) {

//     int result;
//     SDL_version sdlver;

//     /*	Set software interrupts.	*/
//     signal(SIGINT, catchsignal);
//     signal(SIGQUIT, catchsignal);

//     /*	Initialize SDL.	*/
//     SDL_GetVersion(&sdlver);
//     Debug::log("SDL version %d.%d.%d.\n", sdlver.major, sdlver.minor, sdlver.patch);

//     /*	Initialize the engine.	*/
//     result = SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS);
//     if (result != 0) {
//     	throw std::runtime_error(format("Error %s", SDL_GetError()));
//     }

// 	/*  Initialize HPM.  */
// 	if (!Hpm::init((Hpm::HPMSIMD)this->config->get<int>("SIMD")))
// 		throw RuntimeException("Failed to initialize the hpm library.");
// 	Log::log(Log::Verbose, "HPM SIMD using: %s\n", hpm_get_simd_symbol(hpm_get_simd()));

// 	/*  */
//     Engine::config = config;

//     Engine::sceneManager = new SceneManager();
// }

// const char *Engine::getVersion(void) {
// 	return PV_VERSION;
// }

// void *Engine::createWindow(RenderingInterface* renderer, const char *title, int x, int y, int width, int height) {

// 	void *window;

// 	SDL_DisplayMode current;
// 	int res;

// 	res = SDL_GetCurrentDisplayMode(0, &current);
// 	if (res != 0) {
// 		throw std::runtime_error(format("Failed get current display mode %s", SDL_GetError()));
// 	}

// 	/*  Compute screen size and location if default value provided.   */
// 	if (width == -1) {
// 		width = current.w / 2;
// 	}
// 	if (height == -1) {
// 		height = current.h / 2;
// 	}
// 	if (x == -1) {
// 		x = current.w / 4;
// 	}
// 	if (y == -1) {
// 		y = current.h / 4;
// 	}

// 	/*	Create window.	*/
// 	window = renderer->createWindow(x, y, width, height);
// 	assert(window);

// 	/*	Set window title.	*/
// 	SDL_SetWindowTitle((SDL_Window *) window, title);

// 	/*  Set window properties.  */
// 	SDL_SetWindowResizable((SDL_Window *) window, (SDL_bool) config->get<bool>("window-resizable"));
// 	SDL_SetWindowFullscreen((SDL_Window *) window, (SDL_bool) config->get<bool>("fullscreen"));
// 	SDL_SetWindowBordered((SDL_Window *) window, (SDL_bool) config->get<bool>("window-bordered"));

// 	/*  Load icon.  */
// 	SDL_Surface *surface;
// 	unsigned int iconw = 0, iconh = 0;
// 	unsigned long iconSize;
// 	void *icon;
// 	std::string iconpath = format("%s/icon.png", config->get<const char *>("shaddir"));
// 	icon = NULL;
// 	if (icon && iconw > 0 && iconh > 0) {
// 		const uint32_t iconBytes = (iconSize / (iconw * iconh));
// 		const uint32_t iconBits = iconBytes * 8;
// 		surface = SDL_CreateRGBSurfaceFrom(icon, iconw, iconh, iconBits, iconw * iconBytes, 0x00ff0000, 0x0000ff00,
// 		                                   0x000000ff, iconBits == 32 ? 0xff000000 : 0x0);
// 		if (surface) {
// 			SDL_SetWindowIcon((SDL_Window *) window, surface);
// 			SDL_FreeSurface(surface);
// 		}
// 		free(icon);
// 	}

// 	return window;
// }


// SceneManager *Engine::getSceneManager(void) {
// 	return Engine::sceneManager;
// }

// void Engine::setCommandController(CommandController *commandController) {
// 	Engine::controller = commandController;

// 	assert(commandController);

// 	/*	Create command controller for handling input for current scene.	*/
// 	commandController->setCommandMask(Command::eKeyBoardInput);
// 	commandController->setKeyMap(KeyMap::loadKeyMap(format("%s/%s", config->get<const char*>("shaddir"), config->get<const char*>("keymap")).c_str()));
// }


// Config *Engine::getConfig(void) {
//     return Engine::config;
// }

// void Engine::run(void) {
// 	SDL_Event event = {0};

// 	/*	TODO relocate to camera.    */
// 	RenderPipelineBase *renderpath = RenderPipelineFactory::createRenderingPipeline(RenderPipelineFactory::eForward,
// 	                                                                                sceneManager->getCurrentScene()->getRenderingInterface());

// 	/*	*/
// 	bool isAlive = true;                /*	*/
// 	bool visable = true;                /*	*/
// 	bool renderInBackground = true;        /*	*/
// 	bool renderOutOfFoucs = false;        /*	*/

// 	/*	*/
// 	unsigned int width;
// 	unsigned int height;

// 	while (isAlive) {
// 		/*  Get current scene to process.   */
// 		CommandController *cmdcontroller = Engine::controller;
// 		Scene *scene = Engine::sceneManager->getCurrentScene();
// 		PhysicInterface *physic = scene->getPhysicInterface();
// 		RenderingInterface *renderer = scene->getRenderingInterface();

// 		while (SDL_PollEvent(&event)) {

// 			switch (event.type) {
// 				case SDL_WINDOWEVENT:
// 					switch (event.window.event) {
// 						case SDL_WINDOWEVENT_SIZE_CHANGED:
// 							width = event.window.data1;
// 							height = event.window.data2;
// 							renderpath->setViewport(width, height, renderer);
// 							break;
// 						case SDL_WINDOWEVENT_HIDDEN:
// 							visable = false;
// 							break;
// 						case SDL_WINDOWEVENT_EXPOSED:
// 						case SDL_WINDOWEVENT_SHOWN:
// 							visable = true;
// 							break;
// 						case SDL_WINDOWEVENT_ENTER:
// 							renderInBackground = renderOutOfFoucs ? true : false;
// 							break;
// 						case SDL_WINDOWEVENT_LEAVE:
// 							renderInBackground = renderOutOfFoucs ? true : false;
// 							break;
// 						case SDL_WINDOWEVENT_CLOSE:
// 							return;    /*	Quit application.	*/
// 						default:
// 							break;
// 					}
// 					break;
// 				case SDL_QUIT:
// 					isAlive = SDL_FALSE;
// 					break;
// 				case SDL_KEYDOWN:
// 					if (event.key.keysym.sym == SDLK_RETURN && (event.key.keysym.mod & SDLK_LCTRL)) {
// 						if (!Engine::getConfig()->get<int>("isFullscreen")) {
// 							SDL_SetWindowFullscreen(SDL_GL_GetCurrentWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
// 							Engine::getConfig()->set<int>("isFullscreen", 1);
// 						} else {
// 							SDL_SetWindowFullscreen(SDL_GL_GetCurrentWindow(), 0);
// 							Engine::getConfig()->set<int>("isFullscreen", 0);
// 						}
// 					}

// 					break;
// 				case SDL_KEYUP:
// 					cmdcontroller->enqueue(CommandKey(event.key.keysym.sym,
// 					                                  event.key.keysym.mod & (SDLK_LCTRL | SDLK_LSHIFT),
// 					                                  scene));
// 					cmdcontroller->dequeue();
// 					break;
// 				case SDL_MOUSEBUTTONDOWN:
// //					cmdcontroller->enqueue();
// 					break;
// 				case SDL_MOUSEMOTION:
// 					break;
// 				case SDL_MOUSEWHEEL:
// 					break;
// 				case SDL_JOYAXISMOTION:
// 					break;
// 				case SDL_JOYBUTTONDOWN:
// 					break;
// 				case SDL_FINGERMOTION:
// 					break;
// 				case SDL_DROPFILE: {

// 					/*  TODO add an command.    */

// 					// /*	Check what to do here.	*/
// 					// Node *node;
// 					// AssetImporter assloader = AssetImporter(scene, renderer, physic);

// 					// /*	*/
// 					// node = assloader.loadSceneNode(event.drop.file);
// 					// if (node) {
// 					// 	node->setPosition(scene->getMainCamera()->getPosition());
// 					// 	scene->addStaticObject(node);
// 					// }

// 				}
// 					break;
// 				case SDL_USEREVENT:
// 					/*  Get */
// 					break;
// 			}

// 		}

// 		if (scene) {
// 			TimeModule::setCurrentTime(scene->getTime());
// 			/*	Fetch and update simulate	*/
// 			physic->simulate(scene->getTime()->deltaTime() * scene->getTime()->getTimeScale());
// 			physic->sync();

// 			/*	*/
// 			//TimeModule::getCurrentTime()->internalUpdate();
// 			Input::internalUpdate();

// 			/*	render only if visible of configure too.	*/
// 			// if ((visable || renderInBackground) && TimeModule::getCurrentTime()->getTimeScale() > 0.0f) {

// 			// 	/*	render scene to default framebuffer.	*/
// 			// 	renderpath->draw(scene, renderer);

// 			// 	renderer->swapBuffer();
// 			// }
// 		}
// 	}

// 	Debug::log("Quit run loop.\n");
// }

