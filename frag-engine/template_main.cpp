
// void Engine::run(void) {
// 	SDL_Event event = {0};

// 	/*	TODO relocate to camera.    */
// 	RenderPipelineBase *renderpath =
// RenderPipelineFactory::createRenderingPipeline(RenderPipelineFactory::eForward,
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
// 						case
// SDL_WINDOWEVENT_SIZE_CHANGED: 							width = event.window.data1; 							height =
// event.window.data2; 							renderpath->setViewport(width, height, renderer); 							break;
// 						case SDL_WINDOWEVENT_HIDDEN:
// 							visable = false;
// 							break;
// 						case SDL_WINDOWEVENT_EXPOSED:
// 						case SDL_WINDOWEVENT_SHOWN:
// 							visable = true;
// 							break;
// 						case SDL_WINDOWEVENT_ENTER:
// 							renderInBackground = renderOutOfFoucs ?
// true : false; 							break; 						case SDL_WINDOWEVENT_LEAVE: 							renderInBackground =
// renderOutOfFoucs ? true : false; 							break; 						case SDL_WINDOWEVENT_CLOSE: 							return;
// /*	Quit application.	*/ 						default: 							break;
// 					}
// 					break;
// 				case SDL_QUIT:
// 					isAlive = SDL_FALSE;
// 					break;
// 				case SDL_KEYDOWN:
// 					if (event.key.keysym.sym == SDLK_RETURN &&
// (event.key.keysym.mod & SDLK_LCTRL)) { 						if
// (!Engine::getConfig()->get<int>("isFullscreen")) {
// 							SDL_SetWindowFullscreen(SDL_GL_GetCurrentWindow(),
// SDL_WINDOW_FULLSCREEN_DESKTOP); 							Engine::getConfig()->set<int>("isFullscreen",
// 1); 						} else { 							SDL_SetWindowFullscreen(SDL_GL_GetCurrentWindow(), 0);
// 							Engine::getConfig()->set<int>("isFullscreen",
// 0);
// 						}
// 					}

// 					break;
// 				case SDL_KEYUP:
// 					cmdcontroller->enqueue(CommandKey(event.key.keysym.sym,
// 					                                  event.key.keysym.mod
// & (SDLK_LCTRL | SDLK_LSHIFT), 					                                  scene)); 					cmdcontroller->dequeue(); 					break; 				case
// SDL_MOUSEBUTTONDOWN:
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
// 					// AssetImporter assloader = AssetImporter(scene,
// renderer, physic);

// 					// /*	*/
// 					// node =
// assloader.loadSceneNode(event.drop.file);
// 					// if (node) {
// 					//
// node->setPosition(scene->getMainCamera()->getPosition());
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
// 			physic->simulate(scene->getTime()->deltaTime() *
// scene->getTime()->getTimeScale()); 			physic->sync();

// 			/*	*/
// 			//TimeModule::getCurrentTime()->internalUpdate();
// 			Input::internalUpdate();

// 			/*	render only if visible of configure too.
// */
// 			// if ((visable || renderInBackground) &&
// TimeModule::getCurrentTime()->getTimeScale() > 0.0f) {

// 			// 	/*	render scene to default framebuffer.
// */
// 			// 	renderpath->draw(scene, renderer);

// 			// 	renderer->swapBuffer();
// 			// }
// 		}
// 	}

// 	Debug::log("Quit run loop.\n");
// }
