#include"RenderPipeline/RenderPipelineSettings.h"

#include <Renderer/Buffer.h>
#include <Renderer/ViewPort.h>
#include <Renderer/FrameBuffer.h>
#include <Renderer/Query.h>
#include <Renderer/ProgramPipeline.h>
#include <Renderer/Sync.h>

using namespace fragcore;

RenderPipelineSettings::RenderPipelineSettings(const IConfig &other) : IConfig(other) {

}

RenderPipelineSettings::RenderPipelineSettings(void) {

}

IConfig *RenderPipelineSettings::getSuperInstance(void) {
	return NULL;
}
