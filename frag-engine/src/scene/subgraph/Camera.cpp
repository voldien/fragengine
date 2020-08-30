#include "Scene/SubGraph/Camera.h"
//#include "RenderingInterface.h"

using namespace fragcore;
using namespace fragengine;

Camera::Camera(void)
{
	//this->setObjectType(Object::eCamera);
	this->clear = SkyBox;
	this->overrideRenderer = NULL;
}

Camera::Camera(const Camera &other)
{
	*this = other;
}

Camera::~Camera(void)
{
}

Camera::ClearMode Camera::clearMask(void) const
{
	return this->clear;
}

void Camera::setClearMask(ClearMode mask)
{
	this->clear = mask;
}

void Camera::useHDR(bool use)
{
	this->hdr = use;
}

bool Camera::useHDR(void) const
{
	return this->hdr;
}

Camera::ProjectionMode Camera::getProjection(void) const
{
	return projection;
}

void Camera::setProjection(Camera::ProjectionMode projection)
{
	Camera::projection = projection;
}

void Camera::setRenderingPath(Ref<IRenderPipelineBase> &pipeline)
{
	this->overrideRenderer = pipeline;
}

Ref<IRenderPipelineBase> Camera::getRenderingPath(void) const
{
	return this->overrideRenderer;
}

// void Camera::setRenderTarget(FrameBufferObject *target)
// {
// 	this->target = target;
// }

// FrameBufferObject *Camera::getRenderTarget(void) const
// {
// 	return this->target;
// }