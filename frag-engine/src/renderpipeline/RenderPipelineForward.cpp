#include"RenderPipeline/RenderPipelineForward.h"
#include"Prerequisites.h"
#include <Renderer/Buffer.h>
#include <Renderer/ViewPort.h>
#include <Renderer/FrameBuffer.h>
#include <Renderer/Query.h>
#include <Renderer/ProgramPipeline.h>
#include <Renderer/Sync.h>

using namespace fragcore;
using namespace fragengine;

RenderPipelineForward::RenderPipelineForward(Ref<IRenderer> render) {

}

RenderPipelineForward::~RenderPipelineForward() {

}

void RenderPipelineForward::draw(Scene *scene, FrameBuffer *frame, IRenderer *render) {

}

void RenderPipelineForward::setRenderer(Ref<IRenderer> &renderer) {

}

const Ref<IRenderer> &RenderPipelineForward::getRenderer() const {
	return this->renderer;
}

Ref<IRenderer> RenderPipelineForward::getRenderer() {
	return Ref<IRenderer>();
}

void RenderPipelineForward::setViewport(int width, int height, IRenderer *render) {

}


void RenderPipelineForward::drawCamera(Scene *scene, Camera *camera, IRenderer *render) {

}

RenderQueue RenderPipelineForward::getSupportedQueue() const {
	return AlphaTest;
}
