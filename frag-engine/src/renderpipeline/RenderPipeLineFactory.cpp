//
//#include <RenderPipeline/RenderPipelineBase.h>
//#include <RenderPipeline/RenderPipelineFactory.h>
//#include <stdexcept>
//
//RenderPipelineBase *RenderPipelineFactory::createRenderingPipeline(
//		RenderingPath ePath, IRenderer*renderer) {
//
//	switch (ePath) {
//		case eForward: {
////			RenderPipelineForward *renderPipelineForward = new RenderPipelineForward(renderer);
////			renderPipelineForward->qualitySettings = PipelineQualitySettings::createQualitySettings(renderer);
////
////			renderPipelineForward->postTarget = RenderTargetFactory::createColor(renderer, 1024, 1024);
////			renderPipelineForward->renderTarget = RenderTargetFactory::createHDR(renderer, 1024, 1024);
////
////			renderPipelineForward->shadows.resize(2);
////			renderPipelineForward->shadows[0] = RenderTargetFactory::createShadow(renderer, 1024, 1024);
////			renderPipelineForward->shadows[1] = RenderTargetFactory::createShadow(renderer, 1024, 1024);
//
//
//			//return renderPipelineForward;
//		}
//		case eDeferred: {
////			return new RenderPipelineDeferred(renderer);
//		}
//		default:
//			throw std::invalid_argument("Non supported rendering pipline");
//	}
//}
//
//RenderPipelineBase *RenderPipelineFactory::createRenderingPipeline(const char *path, IRenderer *renderer) {
//
//
////	Library library;
////	RenderPipelineBase *interface = NULL;
////	const char *funcsymbol = "createInternalAudioInterface";
////	pcreateinternalaudio pfunc;
////
////	/*	Validate paramaters.	*/
////	if (cpathlib == NULL || resources == NULL || config == NULL)
////		throw std::exception();
////
////	assert(cpathlib);
////
////	/*	Open library and validate.	*/
////	library.open(cpathlib);
////	if (library.isValid()) {
////
////		/*	Get factory function for creating rendering dynamicInterface instance.	*/
////		pfunc = (pcreateinternalaudio) library.getfunc(funcsymbol);
////		interface = pfunc(config);
////
////		/*	Assign resource object in order to work.	*/
////		interface->setResource(resources);
////	} else {
////		Debug::error("Failed loading %s library for creating rendering dynamicInterface.\n", cpathlib);
////	}
////
////	return interface;
//
//
//}
//
