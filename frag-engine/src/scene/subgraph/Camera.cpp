#include "Scene/SubGraph/Camera.h"
//#include "RenderingInterface.h"
#include <Sync.h>
using namespace fragcore;
using namespace fragengine;

Camera::Camera() : Frustum() {
	// this->setObjectType(Object::eCamera);
	this->clear = SkyBox;
	this->overrideRenderer = NULL;
}

Camera::Camera(const Camera &other) { /**this = other;*/ }

Camera::~Camera() {}

Camera::ClearMode Camera::clearMask() const { return this->clear; }

void Camera::setClearMask(ClearMode mask) { this->clear = mask; }

void Camera::useHDR(bool use) { this->hdr = use; }

bool Camera::useHDR() const { return this->hdr; }

Camera::ProjectionMode Camera::getProjection() const { return projection; }

void Camera::setProjection(Camera::ProjectionMode projection) { Camera::projection = projection; }

void Camera::setRenderingPath(Ref<IRenderPipelineBase> &pipeline) { this->overrideRenderer = pipeline; }

Ref<IRenderPipelineBase> Camera::getRenderingPath() const { return this->overrideRenderer; }

// void Camera::setRenderTarget(FrameBufferObject *target)
// {
// 	this->target = target;
// }

// FrameBufferObject *Camera::getRenderTarget() const
// {
// 	return this->target;
// }
