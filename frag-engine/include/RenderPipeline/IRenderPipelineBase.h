

#ifndef _FRAG_ENGINE_IRENDER_PIPELINE_BASE_H_
#define _FRAG_ENGINE_IRENDER_PIPELINE_BASE_H_ 1
#include "Prerequisites.h"
#include "RenderPipelineSettings.h"
#include "RenderQueue.h"
#include "Scene/Scene.h"
#include <Core/Ref.h>
#include <Core/SmartReference.h>
#include <Geometry.h>
#include <RenderPrerequisites.h>

namespace fragengine {
	using namespace fragcore;
	/**
	 *	Responsible for rendering scene to default
	 *	framebuffer.
	 */
	class FVDECLSPEC IRenderPipelineBase : public SmartReference {
		friend class RenderPipelineFactory;

	  public:
		/**
		 * Draw scene, iterate through each camera
		 * and renderer the scene using the selected
		 * rendering interface in respect to the current settings.
		 *
		 * @param scene
		 * @param render
		 */
		virtual void draw(Scene *scene, FrameBuffer *frame, IRenderer *render) = 0;

		virtual void setRenderer(Ref<IRenderer> &renderer) = 0;

		virtual const Ref<IRenderer> &getRenderer() const = 0;

		virtual Ref<IRenderer> getRenderer() = 0;

		//	virtual void setSettings(Ref<RenderPipelineSettings> settings);
		//	virtual Ref<RenderPipelineSettings>& getSettings() const;
		//	virtual Ref<RenderPipelineSettings> getSettings();

		virtual void setViewport(int width, int height, IRenderer *render) = 0;

		virtual RenderQueue getSupportedQueue() const = 0;

	  protected:
		/*  Basic internal components.  */
		Ref<IRenderer> renderer; /*  Main rendering API interface.  */
		Ref<Sync> syncObject;	 /*  Sync object.    */
		ViewPort *viewPort;		 // TODO determine what to do

		Ref<RenderPipelineSettings> renderQuality;

		Ref<fragcore::Geometry> quadDisplay; /*  Quad display.   */
		Ref<Buffer> quadDisplayIndirect;	 /*  Quad indirect buffer.    */
											 // Ref<ProgramPipeline> displayShader; /*  Quad display shader.    */
	};
} // namespace fragengine

/*  Plugin interface function for creating custom rendering pipeline.   */
extern "C" fragengine::IRenderPipelineBase *createPipeLine(fragcore::IRenderer *interface);

#endif
