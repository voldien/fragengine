#include"RenderPipeline/RenderPipelineForward.h"
#include <Renderer/Buffer.h>
#include <Renderer/ViewPort.h>
#include <Renderer/FrameBuffer.h>
#include <Renderer/Query.h>
#include <Renderer/ProgramPipeline.h>
#include <Renderer/Sync.h>

using namespace fragcore;

RenderPipelineForward::RenderPipelineForward(Ref<IRenderer> render) {

}

RenderPipelineForward::~RenderPipelineForward(void) {

}

void RenderPipelineForward::draw(Scene *scene, FrameBuffer *frame, IRenderer *render) {

}

void RenderPipelineForward::setRenderer(Ref<IRenderer> &renderer) {

}

const Ref<IRenderer> &RenderPipelineForward::getRenderer(void) const {
	return this->renderer;
}

Ref<IRenderer> RenderPipelineForward::getRenderer(void) {
	return Ref<IRenderer>();
}

void RenderPipelineForward::setViewport(int width, int height, IRenderer *render) {

}


void RenderPipelineForward::drawCamera(Scene *scene, Camera *camera, IRenderer *render) {

}

RenderQueue RenderPipelineForward::getSupportedQueue(void) const {
	return AlphaTest;
}
