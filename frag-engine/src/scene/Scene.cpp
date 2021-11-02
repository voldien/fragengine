#include "Scene/Scene.h"
#include "Scene/SubGraph/Node.h"
#include "Scene/SubGraph/Camera.h"
#include "Scene/SubGraph/Light.h"
using namespace fragcore;
using namespace fragengine;

// SandBoxSubScene *Scene::getGLSLSandBoxScene() {
// 	return this->glslSandBoxSubScene;
// }

// void Scene::createGLSLSandBoxScene() {
// 	this->glslSandBoxSubScene = new SandBoxSubScene();
// }

Time *Scene::getTime() const {
	return this->time;
}

Scene::~Scene() {
	delete this->time;
}

Node *Scene::getRoot() {
	Node* node;
	node->getParent();
	return nullptr;
}

Camera *Scene::getMainCamera() {            
	return nullptr;
}
