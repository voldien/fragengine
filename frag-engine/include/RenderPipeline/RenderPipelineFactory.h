#ifndef _FRAG_ENGINE_RENDERING_PIPELINE_FACTORY_H_
#define _FRAG_ENGINE_RENDERING_PIPELINE_FACTORY_H_ 1
#include"RenderPipelineBase.h"
#include"Prerequisites.h"


namespace fragengine {
	/**
	 *	Responsible for creating rendering pipeline object.
	*/
	class FVDECLSPEC RenderPipelineFactory{
		friend class RenderPipelineBase;
	public:

		static RenderPipelineBase* createRenderingPipeline(const char* path, IRenderer* renderer);

	private:	/*	Prevent one from creating an instance of this class.	*/

		RenderPipelineFactory(void);
		RenderPipelineFactory(const RenderPipelineFactory& other);
		~RenderPipelineFactory(void);

	};

}

#endif
