#include "Scene/Scene.h"
#include "Scene/SubGraph/Node.h"
#include "Scene/SubGraph/Camera.h"
#include "Scene/SubGraph/Light.h"
using namespace fragcore;
using namespace fragengine;

// SandBoxSubScene *Scene::getGLSLSandBoxScene(void) {
// 	return this->glslSandBoxSubScene;
// }

// void Scene::createGLSLSandBoxScene(void) {
// 	this->glslSandBoxSubScene = new SandBoxSubScene();
// }

Time *Scene::getTime(void) const {
	return this->time;
}

Scene::~Scene(void) {
	delete this->time;
}

Node *Scene::getRoot(void) {
	Node* node;
	node->getParent();
	return nullptr;
}

Camera *Scene::getMainCamera(void) {            
	return nullptr;
}
