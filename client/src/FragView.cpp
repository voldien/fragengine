#include"FragView.h"
#include<SDL2/SDL.h>
#include<FragView.h>
#include"Renderer/ProgramPipeline.h"
#include"RenderPipeline/RenderPipelineSandBox.h"
#include<Asset/FileNotify.h>
#include"Core/IO/ZipFile.h"
#include<cassert>
#include<Utils/TextureUtil.h>
#include<Utils/ShaderUtil.h>
#include<Utils/StringUtil.h>
#include <Asset/AssetHandler.h>
#include <Scene/SceneFactory.h>
#include"RenderPipeline/RenderPipelineForward.h"
#include"Exception/RuntimeExecption.h"
#include <Core/IO/FileSystem.h>
#include <Renderer/Query.h>
#include <FontFactory.h>
#include <Core/IO/FileIO.h>
#include"Core/Log.h"
#include"RendererFactory.h"
#include"Scene/Scene.h"
#include"Core/UserEvent.h"
#include"Renderer/ViewPort.h"
#include"Renderer/RenderDesc.h"
#include<hpmcpp/HpmCpp.h>
#include <Core/SystemInfo.h>


FragView::FragView(int argc, const char **argv) {

	/*  Verbose information.    */
	Log::log(Log::eVerbose, "Platform %d\n", SystemInfo::getOperatingSystem());
	Log::log(Log::eVerbose, "Platform %d\n", SystemInfo::getOperatingSystem());

	init(argc, argv);

	/*  Assert dependent variables. */
	assert(this->config && *this->renderer && this->window && this->sch);

	/*  Get rendering capabilities. */
	Capability capability;
	(*this->renderer)->getCapability(&capability);

	bool useSandBox = this->config->get<bool>("sandbox");
	IConfig& resourceConfig = this->config->getSubConfig("");
	//TODO relocate later for improved cohesion.
	if(useSandBox) {
		IConfig& sandBoxSettings = this->config->getSubConfig("render-sandbox-graphic-settings");
		IConfig& sandboxConfig = this->config->getSubConfig("sandbox");

		//RenderPipelineSettings(sandBoxSettings);
		this->renderpipeline = Ref<IRenderPipelineBase>(new RenderPipelineSandBox(this->renderer));

		//TODO improve for the next version of scene and pipeline object.
		/*  Create display renderer.    */
		this->display = new RenderPipeline(this->renderer, this->config);

		/*  Create Scene.   */
		this->scene = SceneFactory::createScene(*this->renderer, SceneFactory::eSandBox);
		this->scene->getTime()->start();

		/*  TODO relocate all shader loading logic to the shader model import.  */
		//ShaderModelImporter importer = ShaderModelImporter(this->renderer);
		//TargetNode* target = importer.createTargetModel(argc, argv);
		//this->scene->getGLSLSandBoxScene()->

		//TODO relocate to its own function.
		/*  Create shaders. */
		for (int i = 0; i < sandboxConfig.get<int>("num_shaders"); i++) {
			ProgramPipeline *shader;

			/*  Check if fragment shader is supported.  */
			if(!capability.sFragmentShader)
				throw RuntimeException(format("Fragment shader is not support for %s\n", (*this->renderer)->getName()));

			std::string path = sandboxConfig.get<std::string>(format("shader%d", i)).c_str();
			IO* ref = FileSystem::openFile(path.c_str(), IO::Mode::READ);

			/*  Load fragment program.  */
			ShaderUtil::loadFragmentProgramPipeline(ref, GLSL, (*this->renderer), &shader);
			scene->getGLSLSandBoxScene()->addShader(shader);
			Log::log(Log::eVerbose, "Loaded Shader: %s\n", path.c_str());

			this->notify->registerAsset(path.c_str(), shader, eShader);

			delete ref;
		}

		/*  Create compute shaders.    */
		for (int i = 0; i < sandboxConfig.get<int>("num_compute"); i++) {
			ProgramPipeline *compute;

			/*  Check if compute shader is supported.  */
			std::string path = sandboxConfig.get<std::string>(format("compute%d", i)).c_str();
			if(!capability.sComputeShader)
				throw RuntimeException(format("Compute shader is not support for %s\n", (*this->renderer)->getName()));

			IO* ref = FileSystem::openFile(path.c_str(), IO::Mode::READ);
			/*  */
			ShaderUtil::loadComputeShader(ref, *this->renderer, &compute);
			scene->getGLSLSandBoxScene()->addCompute(compute);
			Log::log(Log::eVerbose, "Loaded Compute Shader: %s\n", path.c_str());

			this->notify->registerAsset(path.c_str(), compute, eShader);

			delete ref;
		}

		/*  Create textures.    */
		for (int i = 0; i < capability.sMaxTextureUnitActive; i++) {
			Texture *texture;
			const char *path = NULL;
			if (sandboxConfig.isSet(format("texture%d", i))) {
				path = sandboxConfig.get<const char *>(format("texture%d", i));
				if (path) {
					TextureUtil::loadTexture(path, *this->renderer, &texture);
					scene->getGLSLSandBoxScene()->addTexture(texture);
					Log::log(Log::eVerbose, "Loaded texture: %s\n", path);
				}

				this->notify->registerAsset(path, texture, eTexture);
			}
		}
	}else {

		this->scene = SceneFactory::createScene(*this->renderer, SceneFactory::eWorldSpace);
		this->renderpipeline = Ref<IRenderPipelineBase>(new RenderPipelineForward(this->renderer));

		// Read from options for loading the scene.
		ZipFile* internalShader = ZipFile::createZipFileObject("resource-settings");
		delete internalShader;
	}

	// Assert the variables
	assert(this->scene && *this->renderpipeline);
	
	/*  Start the notify change.   */
	this->notify->start();

	/*  Print debug.    */
	if(config->get<bool>("debug"))
		config->printTable();
}

FragView::~FragView(void) {

	const IConfig &resourceConfig = this->config->getSubConfig("resource-settings");
	if (this->config && resourceConfig.get<bool>("save-configuration")) {
		//FileSystem::openFile(this->config->get<const char*>("dump-configuration"), IO::WRITE);
		FileIO fileIo = FileIO(resourceConfig.get<const char *>("dump-configuration"), IO::WRITE);
		this->config->save(&fileIo, Config::XML);
	}

	/*  Release all assets.    */
	this->notify->unRegisterAllAsset();

	/*  Terminate scheduler.    */
	int status = schTerminateTaskSch(this->sch);
	if (status != SCH_OK) {
		throw RuntimeException(format("schTerminateTaskSch failed : %d - %s", status, schErrorMsg(status)));
	}
	status = schReleaseTaskSch(this->sch);
	if (status != SCH_OK) {
		throw RuntimeException(format("schReleaseTaskSch failed : %d - %s", status, schErrorMsg(status)));
	}
	free(this->sch);

	/*  Reduce reference and delete resources.  */
	delete this->display;
	if(this->renderer->deincreemnt())
		delete *this->renderer;
	delete this->scene->getGLSLSandBoxScene();
	delete this->scene;
	delete this->notify;
	delete this->config;

	/*  */
	SDL_QuitSubSystem(SDL_INIT_EVENTS | SDL_INIT_TIMER);
}

void FragView::init(int argc, const char** argv){

	/*  Read first options.   */
	this->config = Config::createConfig(argc, argv, Config::getConfigFilePath(argc, argv));

	int status = SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER);
	if (status != 0)
		throw RuntimeException(format("failed to initialize SDL library : %d - %s", status, SDL_GetError()));

	/*  Initialize HPM.  */
	if (!Hpm::init((Hpm::HPMSIMD) this->config->get<int>("SIMD")))
		throw RuntimeException("Failed to initialize hpm");
	Log::log(Log::eVerbose, "HPM SIMD %s\n", hpm_get_simd_symbol(hpm_get_simd()));

	/*  Create rendering interface. */
	const IConfig& renderConfig = config->getSubConfig("render-driver");
	this->renderer = Ref<IRenderer>(RenderingFactory::createRendering(config->get<const char *>("renderer-dynamicInterface"), &renderConfig));
	Log::log(Log::eVerbose, "Loading Renderer: %s-%s\n", (*this->renderer)->getName(), (*this->renderer)->getVersion());
	Log::log(Log::eVerbose, "API Internal API version: %s\n", (*this->renderer)->getAPIVersion());
	(*this->renderer)->setVSync(renderConfig.get<bool>("v-sync"));

	/*  Create task scheduler.  */
	this->sch = (schTaskSch *) malloc(sizeof(schTaskSch));
	int sch = schCreateTaskPool(this->sch, 2, SCH_FLAG_NO_AFM, 48);
	if (sch != SCH_OK)
		throw RuntimeException(schErrorMsg(status));
	sch = schRunTaskSch(this->sch);
	if (sch != SCH_OK)
		throw RuntimeException(schErrorMsg(status));

	//TODO add support for some kind of filesystem.

	/*  Create file notify.    */
	if (this->config->get<bool>("notify-file"))
		this->notify = new FileNotify(this->sch);

	/*  Create window - default position and size.  */
	const IConfig& windowConfig = this->config->getSubConfig("render-window-settings");
	this->createWindow(windowConfig.get<int>("screen-x"), windowConfig.get<int>("screen-y"),
	                   windowConfig.get<int>("screen-width"), windowConfig.get<int>("screen-height"));
}

void* FragView::createWindow(int x, int y, int width, int height) {
	assert(*this->renderer);

	SDL_DisplayMode current;
	int res;

	/*  Get the current display properties. */
	res = SDL_GetCurrentDisplayMode(0, &current);
	if (res != 0)
		throw RuntimeException(format("Failed get current display mode %s", SDL_GetError()));

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
	this->window = (*this->renderer)->createWindow(x, y, width, height);
	assert(this->window);
	(*this->renderer)->setCurrentWindow(this->window);

	/*  Update default viewport.    */
	(*this->renderer)->getView(0)->setDimensions(0, 0, width, height);

	/*  Set current window title.   */
	std::string title = format("FragView - %s : %s - %s", FragView::getVersion(), (*this->renderer)->getName().c_str(),
	                          (*this->renderer)->getAPIVersion());
	SDL_SetWindowTitle((SDL_Window *)this->window, title.c_str());

	/*  Load icon.  */
	SDL_Surface *surface;
	unsigned int iconw, iconh;
	unsigned long iconSize;
	void *icon;
	std::string iconpath;

	if(FileSystem::exists("./fragview.png"))
		iconpath = "./fragview.png";
	else
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
	const IConfig& windowConfig = this->config->getSubConfig("render-window-settings");
	SDL_SetWindowResizable((SDL_Window *) this->window, (SDL_bool) windowConfig.get<bool>("window-resizable"));
	SDL_SetWindowFullscreen((SDL_Window *) this->window, (SDL_bool) windowConfig.get<bool>("fullscreen"));
	SDL_SetWindowBordered((SDL_Window *) this->window, (SDL_bool) windowConfig.get<bool>("window-bordered"));
	if (windowConfig.get<int>("screen-max-width") > 0 || windowConfig.get<int>("screen-max-height") > 0) {
		const int max_w = windowConfig.get<int>("screen-max-width");
		const int max_h = windowConfig.get<int>("screen-max-height");
		SDL_SetWindowMaximumSize((SDL_Window*)this->window, max_w, max_h);
	}
	if (windowConfig.get<int>("screen-min-width") > 0 || windowConfig.get<int>("screen-min-height") > 0) {
		const int min_w = windowConfig.get<int>("screen-min-width");
		const int min_h = windowConfig.get<int>("screen-min-height");
		SDL_SetWindowMinimumSize((SDL_Window*)this->window, min_w, min_h);
	}
//	SDL_SetWindowBrightness
//  SDL_SetWindowHitTest

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
	const bool renderOutOfFoucs = config->getSubConfig("render-window-settings").get<bool>("background-rendering");

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
							//TODO remove , changed so that it passes throught the event controller.
							width = event.window.data1;
							height = event.window.data2;
							uniform->window.width = (float) width;
							uniform->window.height = (float) height;
							Log::log(Log::eDebug, "viewport resized: %dx%d\n", width, height);
							//this->display->setViewport(0, 0, width, height);
							this->renderpipeline->setViewport(width, height,  *this->renderer);
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
						case SDL_WINDOWEVENT_HIT_TEST:
							break;
						default:
							break;
					}
					break;
				case SDL_QUIT:
					isAlive = SDL_FALSE;
					break;
				case SDL_KEYDOWN:
					//TODO redidect to command buffer.
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
						FrameBuffer *def = (*this->renderer)->getDefaultFramebuffer(window);
						TextureUtil::saveTexture(format("screen - %s.png", FragView2::Time::getDate()).c_str(), *this->renderer, def->getAttachment(0));

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
					uniform->inputs.ay = event.motion.yrel;
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
					/*  Send to task scheduler to deal with.    */
					AssetHandler::handleAssetDrop(event.drop.file);//TODO improve.
					event.drop.file;
					this->sch;
				}
					break;
				case SDL_USEREVENT: {
					if (event.user.code == ASSET_UPDATE) {
						/*  Asset notification handle current graphic context. */
						FileNotificationEvent *objectEvent = (FileNotificationEvent *) event.user.data1;
						try {
							AssetHandler::handleAssetEvent(objectEvent);
						} catch (RuntimeException &err) {
							Log::log(Log::eError, err.what());
						}
						Log::log(Log::eVerbose, "Updating %s\n", objectEvent->path);
						this->notify->eventDone(objectEvent);
						sandbox->updateAllUniformLocations();
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

		// Update Object

		// Update animation

		// Finalize animation

		// Update Video texture

		// Update skinned.

		schWaitTask(this->sch);

		/*	render only if visible of configure too.	*/
		if (visible || renderInBackground) {

			/*  Draw current display on the current scene.  */
			this->renderpipeline->draw(this->scene, this->renderer->getDefaultFramebuffer(this->window), *this->renderer);

			/*  Draw debug. */

			/*  Swap buffer.    */
			(*this->renderer)->swapBuffer();
		}
	}
}

const char *FragView::getVersion(void) {
	return FV_VERSION;
}
