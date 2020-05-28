//
// Created by voldie on 01/03/19.
//

#ifndef FRAGVIEW_TARGETNODE_H
#define FRAGVIEW_TARGETNODE_H
#include <Renderer/ProgramPipeline.h>
#include"IShaderNode.h"

namespace fragview {
/**
 *
 */
	class TargetNode : public IShaderNode {
	public:
		void setProgramShader(ProgramPipeline *program) {
//		this->target = Ref<ProgramPipeline>(program);
		}

	private:
//	Ref<ProgramPipeline> target;
//	Ref<FrameBuffer> post;
	};
}

#endif
