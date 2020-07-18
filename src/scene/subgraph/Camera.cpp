#include "Scene/SubGraph/Camera.h"
//#include "RenderingInterface.h"

using namespace fragview;

Camera::Camera(void)
{
	this->setObjectType(Object::eCamera);
	this->clear = SkyBox;
	this->pipeline = NULL;
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

void Camera::setRenderingPath(RenderPipelineBase *pipeline)
{
	this->pipeline = pipeline;
}

RenderPipelineBase *Camera::getRenderingPath(void) const
{
	return this->pipeline;
}

void Camera::setRenderTarget(FrameBufferObject *target)
{
	this->target = target;
}

FrameBufferObject *Camera::getRenderTarget(void) const
{
	return this->target;
}