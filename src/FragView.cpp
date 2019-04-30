#include"FragView.h"
#include<SDL2/SDL.h>
#include<FragView.h>
#include"Renderer/ProgramPipeline.h"
#include<Asset/FileNotify.h>
#include<cassert>
#include<Utils/TextureUtil.h>
#include<Utils/ShaderUtil.h>
#include<Utils/StringUtil.h>
#include <Asset/AssetHandler.h>
#include <Scene/SceneFactory.h>
#include <ShaderModel/ShaderModelImporter.h>
#include"Core/Log.h"
#include"RendererFactory.h"
#include"Scene/Scene.h"
#include"Core/UserEvent.h"

FragView::FragView(int argc, const char **argv) {

	/*  Read first options.   */
	this->config = Config::createConfig(argc, argv, Config::getConfigFilePath(argc, argv));

	int status = SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER);
	if (status != 0)
		throw std::runtime_error(format("failed to initialize SDL library : %d - %s", status, SDL_GetError()));

	/*  Create rendering interface. */
	this->renderer = RenderingFactory::createRendering(config->get<const char *>("renderer-dynamicInterface"), config);
	Log::log(Log::eVerbose, "Loading Renderer: %s-%s\n", this->renderer->getName(), this->renderer->getVersion());
	this->renderer->setVSync(true);

	/*  Get rendering capabilities. */
	Capability capability;
	this->renderer->getCapability(&capability);

	/*  Create task scheduler.  */
	this->sch = (schTaskSch *) malloc(sizeof(schTaskSch));
	int sch = schCreateTaskPool(this->sch, 2, SCH_FLAG_NO_AFM, 32);
	if (sch != SCH_OK)
		throw std::runtime_error(schErrorMsg(status));
	sch = schRunTaskSch(this->sch);
	if (sch != SCH_OK)
		throw std::runtime_error(schErrorMsg(status));

	/*  Create file notify.    */
	if (this->config->get<bool>("notify-file"))
		this->notify = new FileNotify(this->sch);

	/*  Create window - default position and size.  */
	this->createWindow(this->config->get<int>("screen-x"), this->config->get<int>("screen-y"),
	                   this->config->get<int>("screen-width"), this->config->get<int>("screen-height"));

	/*  Create display renderer.    */
	this->display = new RenderPipeline(this->renderer, this->config);

	/*  Create Scene.   */
	this->scene = SceneFactory::createScene(this->renderer, SceneFactory::eSandBox);
	this->scene->getTime()->start();

	/*  TODO relocate all shader loading logic to the shader model import.  */
	//ShaderModelImporter importer = ShaderModelImporter(this->renderer);
	//TargetNode* target = importer.createTargetModel(argc, argv);
	//this->scene->getGLSLSandBoxScene()->

	/*  Create shaders. */
	for (int i = 0; i < config->get<int>("num_shaders"); i++) {
		ProgramPipeline *shader;

		/*  Check if fragment shader is supported.  */
		if(!capability.sFragmentShader)
			throw std::runtime_error(format("Fragment shader is not support for %s\n", this->renderer->getName()));

		std::string path = config->get<std::string>(format("shader%d", i)).c_str();

		/*  Load fragment program.  */
		ShaderUtil::loadFragmentProgramPipeline(path.c_str(), this->renderer, &shader);
		scene->getGLSLSandBoxScene()->addShader(shader);
		Log::log(Log::eVerbose, "Loaded Shader: %s\n", path.c_str());

		this->notify->registerAsset(path.c_str(), shader, eShader);
	}

	/*  Create compute shaders.    */
	for (int i = 0; i < config->get<int>("num_compute"); i++) {
		ProgramPipeline *compute;

		/*  Check if compute shader is supported.  */
		std::string path = config->get<std::string>(format("compute%d", i)).c_str();
		if(!capability.sComputeShader)
			throw std::runtime_error(format("Compute shader is not support for %s\n", this->renderer->getName()));

		/*  */
		ShaderUtil::loadComputeShader(path.c_str(), this->renderer, &compute);
		scene->getGLSLSandBoxScene()->addCompute(compute);
		Log::log(Log::eVerbose, "Loaded Compute Shader: %s\n", path.c_str());

		this->notify->registerAsset(path.c_str(), compute, eShader);
	}

	/*  Create textures.    */
	for (int i = 0; i < capability.sMaxTextureUnitActive; i++) {
		Texture *texture;
		const char *path = NULL;
		try {
			path = config->get<const char *>(format("texture%d", i));
			if (path) {
				TextureUtil::loadTexture(path, this->renderer, &texture);
				scene->getGLSLSandBoxScene()->addTexture(texture);
				Log::log(Log::eVerbose, "Loaded texture: %s\n", path);
			}
		} catch (std::exception &ex) {
			continue;
		}
		this->notify->registerAsset(path, texture, eTexture);
	}

	/*  Start the notify change.   */
	this->notify->start();
	
	if(config->get<bool>("debug"))
		config->printTable();
}

FragView::~FragView(void) {
	if (this->config && config->get<bool>("save-configuration"))
		this->config->save(this->config->get<const char *>("dump-configuration"), Config::YAML);

	/*  Release all assets.    */
	this->notify->unRegisterAllAsset();

	/*  Terminate scheduler.    */
	int status = schTerminateTaskSch(this->sch);
	if (status != SCH_OK) {
		throw std::runtime_error(format("schTerminateTaskSch failed : %d - %s", status, schErrorMsg(status)));
	}
	status = schReleaseTaskSch(this->sch);
	if (status != SCH_OK) {
		throw std::runtime_error(format("schReleaseTaskSch failed : %d - %s", status, schErrorMsg(status)));
	}
	free(this->sch);


	delete this->display;
	delete this->renderer;
	delete this->scene->getGLSLSandBoxScene();
	delete this->scene;
	delete this->notify;
	delete this->config;

	/*  */
	SDL_QuitSubSystem(SDL_INIT_EVENTS | SDL_INIT_TIMER);
}

void* FragView::createWindow(int x, int y, int width, int height) {
	assert(this->renderer);

	SDL_DisplayMode current;
	int res;

	res = SDL_GetCurrentDisplayMode(0, &current);
	if (res != 0)
		throw std::runtime_error(format("Failed get current display mode %s", SDL_GetError()));

	/*  Compute screen size and location if default value provided.   */
	if (width == -1) {
		width = current.w / 2;
	}
	if (height == -1) {
		height = current.h / 2;
	}
	if (x == -1) {
		x = current.w / 4;
	}
	if (y == -1) {
		y = current.h / 4;
	}

	/*  Create window.  */
	this->window = this->renderer->createWindow(x, y, width, height);
	assert(this->window);
	this->renderer->setCurrentWindow(this->window);

	/*  Update viewport.    */
	this->renderer->setViewport(0, 0, width, height);

	/*  Set current window title.   */
	SDL_SetWindowTitle((SDL_Window *) this->window,
	                   format("FragView - %s : %s - %s", FragView::getVersion(), this->renderer->getName(),
	                          this->renderer->getAPIVersion()).c_str());

	/*  Load icon.  */
	SDL_Surface *surface;
	unsigned int iconw, iconh;
	unsigned long iconSize;
	void *icon;
	std::string iconpath = format("%s/fragview.png", config->get<const char *>("shaddir"));
	icon = TextureUtil::loadTextureData(iconpath.c_str(), &iconw, &iconh, &iconSize);
	if (icon && iconw > 0 && iconh > 0) {
		const uint32_t iconBytes = (iconSize / (iconw * iconh));
		const uint32_t iconBits = iconBytes * 8;
		surface = SDL_CreateRGBSurfaceFrom(icon, iconw, iconh, iconBits, iconw * iconBytes, 0x00ff0000, 0x0000ff00,
		                                   0x000000ff, iconBits == 32 ? 0xff000000 : 0x0);
		if (surface) {
			SDL_SetWindowIcon((SDL_Window *) this->window, surface);
			SDL_FreeSurface(surface);
		}
		free(icon);
	}

	/*  Set window properties.  */
	SDL_SetWindowResizable((SDL_Window *) this->window, (SDL_bool) config->get<bool>("window-resizable"));
	SDL_SetWindowFullscreen((SDL_Window *) this->window, (SDL_bool) config->get<bool>("fullscreen"));
	SDL_SetWindowBordered((SDL_Window *) this->window, (SDL_bool) config->get<bool>("window-bordered"));

	/*  Display window. */
	SDL_ShowWindow((SDL_Window *) this->window);

	return this->window;
}

void FragView::run(void) {
	SDL_Event event = {};

	/*	*/
	unsigned int width;
	unsigned int height;

	/*	*/
	bool isAlive = true;                    /*	*/
	bool visible = true;                    /*	*/

	/*  */
	bool renderInBackground = true;
	const bool renderOutOfFoucs = config->get<bool>("background-rendering");

	/*  Main logic loop.    */
	while (isAlive) {
		Scene *currentScene = this->scene;
		SandBoxSubScene *sandbox = currentScene->getGLSLSandBoxScene();
		FragGraphicUniform *uniform = sandbox->getFragUniform();

		while (SDL_PollEvent(&event)) {

			switch (event.type) {
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							width = (float) event.window.data1;
							height = (float) event.window.data2;
							uniform->window.width = width;
							uniform->window.height = height;
							this->display->setViewport(0,0, width, height);
							break;
						case SDL_WINDOWEVENT_MOVED:
							uniform->window.x = (float) event.window.data1;
							uniform->window.y = (float) event.window.data2;
							break;
						case SDL_WINDOWEVENT_HIDDEN:
							visible = false;
							break;
						case SDL_WINDOWEVENT_EXPOSED:
						case SDL_WINDOWEVENT_SHOWN:
							visible = true;
							break;
						case SDL_WINDOWEVENT_ENTER:
							renderInBackground = renderOutOfFoucs;
							break;
						case SDL_WINDOWEVENT_LEAVE:
							renderInBackground = renderOutOfFoucs;
							break;
						case SDL_WINDOWEVENT_CLOSE:
							return;    /*	Quit application.	*/
						default:
							break;
					}
					break;
				case SDL_QUIT:
					isAlive = SDL_FALSE;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_RETURN && (event.key.keysym.mod & SDLK_LCTRL)) {
						if (!this->config->get<int>("isFullscreen")) {
							SDL_SetWindowFullscreen(SDL_GL_GetCurrentWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
							this->config->set<int>("isFullscreen", 1);
						} else {
							SDL_SetWindowFullscreen(SDL_GL_GetCurrentWindow(), 0);
							this->config->set<int>("isFullscreen", 0);
						}
					} else if (event.key.keysym.sym == SDLK_F12) {
						/* Save current framebuffer.  */
						FrameBuffer *def = this->renderer->getDefaultFramebuffer(window);
						TextureUtil::saveTexture(format("screen - %s.png", Time::getDate()).c_str(), this->renderer, def->getAttachment(0));

					} else {

					}
					break;
				case SDL_KEYUP:
					break;
				case SDL_MOUSEBUTTONDOWN:
					break;
				case SDL_MOUSEMOTION:
					uniform->inputs.x = event.motion.x;
					uniform->inputs.y = event.motion.y;
					uniform->inputs.ax = event.motion.xrel;
					uniform->inputs.y = event.motion.yrel;
					break;
				case SDL_MOUSEWHEEL:{
					const float delta = 0.01f;
					uniform->inputs.wheel += (float) event.wheel.y * delta;
					uniform->inputs.wheelacc = (float) event.wheel.y * delta;
				}break;
				case SDL_JOYAXISMOTION:
					uniform->inputs.ax = event.jaxis.value;
					break;
				case SDL_JOYBUTTONDOWN:
					break;
				case SDL_FINGERMOTION:
					uniform->inputs.x = event.tfinger.x;
					uniform->inputs.y = event.tfinger.y;
					uniform->inputs.ax = event.tfinger.dx;
					uniform->inputs.ay = event.tfinger.dy;
					break;
				case SDL_DROPFILE: {
					/*  Determine what file.  */
					/*  Send to task scheduler to deal with.*/
				}
					break;
				case SDL_USEREVENT: {
					if (event.user.code == ASSET_UPDATE) {
						/*  Asset notification handle current graphic context. */
						FileNotificationEvent *objectEvent = (FileNotificationEvent *) event.user.data1;
						try {
							AssetHandler::handleAssetEvent(objectEvent);
						} catch (std::runtime_error &err) {
							Log::log(Log::eError, err.what());
						}
						Log::log(Log::eVerbose, "Updating %s\n", objectEvent->path);
						this->notify->eventDone(objectEvent);
						sandbox->updateAllUniforms();
					}
				}
					break;
				default:
					break;
			}
		}

		/*  */
		scene->getTime()->internalUpdate();
		uniform->time.time = scene->getTime()->timef();

		/*	render only if visible of configure too.	*/
		if (visible || renderInBackground) {

			/*  Rendering logic.    */
			renderer->clear(eColor | eDepth);
			renderer->clearColor(1, 0.5, 0.4, 1.0f);

			/*  Draw current display.   */
			this->display->draw(this->scene);

			/*  Swap buffer.    */
			renderer->swapBuffer();
		}
	}
}

const char *FragView::getVersion(void) {
	return FV_VERSION;
}
