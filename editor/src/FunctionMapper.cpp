// #include"input/KeyMap.h"
// #include"Scene.h"
// #include"Debug.h"
// #include"Engine.h"
// #include"TimeModule.h"
// #include"RenderingSetting.h"
// #include<SDL2/SDL.h>



// /**
//  *	Forward decleration.
//  */
// static int fullscreen(Scene* scene, const Command& command);
// static int nextRenderPipeLine(Scene* scene, const Command& command);
// static int nextCamera(Scene* scene, const Command& command);
// static int setCameraDebug(Scene* scene, const Command& command);
// static int enableFog(Scene* scene, const Command& command);
// static int setFullScreen(Scene* scene, const Command& command);
// static int setDebug(Scene* scene, const Command& command);


// /**/
// static int createCube(Scene* scene, const Command& command);
// static int createSphere(Scene* scene, const Command& command);


// /*	*/
// static int createScene(void);
// static int scene0(Scene* scene, const Command& command);
// static int scene1(Scene* scene, const Command& command);
// static int scene2(Scene* scene, const Command& command);
// static int scene3(Scene* scene, const Command& command);
// static int scene4(Scene* scene, const Command& command);
// static int scene5(Scene* scene, const Command& command);
// static int nextScene(Scene* scene, const Command& command);
// static int prevScene(Scene* scene, const Command& command);

// /*	*/
// static int pause(Scene* scene, const Command& command);
// static int reduceTime(Scene* scene, const Command& command);
// static int increaseTime(Scene* scene, const Command& command);

// /**
//  *
//  */
// std::map<std::string, KeyMap::keycodeaction> keymapper = {
// 		/*	*/
// 		{"debugcamera", setCameraDebug},
// 		{"enablefog", enableFog },
// 		{"nextCamera", nextCamera },
// 		//{"enableRenderingDebug", setDebug},

// 		/*	*/
// 		{"fullscreen", fullscreen },

// 		/*	*/
// 		{"createCube", createCube},
// 		{"createSphere", createSphere},

// 		/*	*/
// 		{"scene0", scene0},
// 		{"scene1", scene1},
// 		{"scene2", scene2},
// 		{"scene3", scene3},
// 		{"scene4", NULL},
// 		{"scene5", NULL},
// 		{"scene6", NULL},
// 		{"nextScene", NULL},
// 		{"prevScene", NULL},

// 		/*	*/
// 		{"pause", pause},
// 		{"reduce-time", reduceTime},
// 		{"increase-time", increaseTime},

// };

// static int scene0(Scene *scene, const Command& command) {

// //	Engine::setScene(scene);
// 	Debug::log("Selecting Scene 0\n");
// }

// static int scene1(Scene *scene, const Command& command) {
// 	/*  If not scene exists. create.    */
// 	//Engine::setScene(scene);
// 	Debug::log("Selecting Scene 1\n");
// }

// static int scene2(Scene *scene, const Command& command) {
// 	//Engine::setScene(scene);
// 	Debug::log("Selecting Scene 2\n");
// }

// static int scene3(Scene *scene, const Command& command) {

// 	//Engine::setScene(scene);
// 	Debug::log("Selecting Scene 3\n");
// }

// static int fullscreen(Scene *scene, const Command& command) {
// 	if (!Engine::getConfig()->get<bool>("isFullscreen")) {
// 		SDL_SetWindowFullscreen(SDL_GL_GetCurrentWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
// 		Engine::getConfig()->set<bool>("isFullscreen", true);
// 	} else {
// 		SDL_SetWindowFullscreen(SDL_GL_GetCurrentWindow(), 0);
// 		Engine::getConfig()->set<bool>("isFullscreen", false);
// 	}
// 	return 1;
// }


// static int nextCamera(Scene *scene, const Command& command) {

// 	return 0;
// }

// static int setCameraDebug(Scene *scene, const Command& command) {
// 	if (Debug::getDebugCamera())
// 		Debug::removeDebugCamera();
// 	else
// 		Debug::createDebugCamera();
// 	return 0;
// }

// static int enableFog(Scene *scene, const Command& command) {
// 	int fog = ((int)scene->getRenderingSettings()->getFogType());
// 	fog++;
// 	fog %= (RenderingSettings::eAtmospheric + 1);
// 	scene->getRenderingSettings()->setFogType((RenderingSettings::FogType)fog);
// 	return 0;
// }

// int createCube(Scene *scene, const Command& command) {
// 	Debug::log("Creating Rigidbody Cube.\n");
// 	//scene->addDynamicObject()
// 	return 0;
// }

// int createSphere(Scene *scene, const Command& command) {
// 	Debug::log("Creating Rigidbody Sphere.\n");
// 	return 0;
// }


// int pause(Scene *scene, const Command& command) {
// 	static float prevTime = scene->getTime()->getTimeScale();
// 	if (scene->getTime()->getTimeScale() > 0.0f)
// 		scene->getTime()->setTimeScale(0.0f);
// 	else
// 		scene->getTime()->setTimeScale(prevTime);
// }

// int reduceTime(Scene *scene, const Command& command) {
// 	static float prevTime = scene->getTime()->getTimeScale();
// 	scene->getTime()->setTimeScale(prevTime - 0.01f);

// 	return 0;
// }

// int increaseTime(Scene *scene, const Command& command) {
// 	static float prevTime = scene->getTime()->getTimeScale();
// 	scene->getTime()->setTimeScale(prevTime + 0.01f);
// 	return 0;
// }


