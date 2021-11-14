#include"RenderPipeline/RenderPipelineSettings.h"

#include <Buffer.h>
#include <ViewPort.h>
#include <FrameBuffer.h>
#include <Query.h>
//#include <Renderer/ProgramPipeline.h>
#include <Sync.h>

using namespace fragcore;

RenderPipelineSettings::RenderPipelineSettings(const IConfig &other) : IConfig(other) {

}

RenderPipelineSettings::RenderPipelineSettings() {

}

IConfig *RenderPipelineSettings::getSuperInstance() {
	return NULL;
}
