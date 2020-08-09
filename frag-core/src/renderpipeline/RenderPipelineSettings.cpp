#include"RenderPipeline/RenderPipelineSettings.h"
using namespace fragcore;

RenderPipelineSettings::RenderPipelineSettings(const IConfig &other) : IConfig(other) {

}

RenderPipelineSettings::RenderPipelineSettings(void) {

}

IConfig *RenderPipelineSettings::getSuperInstance(void) {
	return NULL;
}
