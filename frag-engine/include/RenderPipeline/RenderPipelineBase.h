/**
    FrameView for rendering shaders in screen space.
    Copyright (C) 2018  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _RENDER_PIPELINE_BASE_H_
#define _RENDER_PIPELINE_BASE_H_ 1
#include <FragCore.h>
#include "IRenderPipelineBase.h"
#include "RenderQueue.h"

namespace fragcore {
/**
 *	Responsible for rendering scene to default
 *	framebuffer.
 */
	class FVDECLSPEC RenderPipelineBase : public IRenderPipelineBase {
	public:

//
//	/**
//	 *
//	 * @param scene
//	 * @param camera
//	 * @param render
//	 */
//	virtual void prepareDraw(Scene *FV_RESTRICT scene,
//	                         Camera *FV_RESTRICT camera,
//	                         IRenderer *FV_RESTRICT render);
//
//	/**
//	 * Check all lights that has influence inside the camera frustum.
//	 * @param scene
//	 * @param camera
//	 * @param render
//	 */
//	virtual void prepareLight(Scene* FV_RESTRICT scene,
//	                          Camera* FV_RESTRICT camera,
//	                          IRenderer* FV_RESTRICT render);
//
//
//	/**
//	 * TODO rename.
//	 * @param root
//	 * @param camera
//	 * @param rendering
//	 * @param base
//	 */
//	virtual void frustumCullRoot(Node *root, Camera *camera,
//	                             IRenderer *rendering, RenderPipelineBase *base);
//
		/**
		 * Draw scene from camera view.
		 * @param scene
		 * @param camera
		 * @param render
		 */
		virtual void drawCamera(Scene *scene,
		                        Camera *camera,
		                        IRenderer *render) = 0;
//
//	/**
//	 *
//	 * @param scene
//	 * @param camera
//	 * @param render
//	 */
//	virtual void drawOverlay(Scene* FV_RESTRICT scene,
//	                         Camera* FV_RESTRICT camera,
//	                         IRenderer* FV_RESTRICT render) = 0;
//
//	/**
//	 * Check if light is in camera view.
//	 * @param camera
//	 * @param light
//	 * @return
//	 */
//	//virtual bool checkLight(Camera* camera, Light* light);

		/**
		 *
		 */
		//virtual void sortDrawQueues(void);
//
//	/**
//	 * Draw shadow elements inside camera
//	 * frustum.
//	 * @param camera
//	 */
//	virtual void drawShadow(Scene* FV_RESTRICT scene, Camera* FV_RESTRICT camera, IRenderer* FV_RESTRICT render) = 0;
//
//	/**
//	 * Draw skybox to current view.
//	 * @param render
//	 * @param scene
//	 */
//	virtual void drawSkybox(RenderingInterface* PV_RESTRICT render, Scene* PV_RESTRICT scene);
//
//	/**
//	 * Draw GUI elements.
//	 * @param scene
//	 * @param camera
//	 * @param render
//	 */
//	virtual void drawGUI(Scene* PV_RESTRICT scene,
//			Camera* PV_RESTRICT camera,
//			RenderingInterface* PV_RESTRICT render);


//
//	/**
//	 *	Get rendering queue.
//	 */
//	Queue<Renderer *> &getRenderQueue(RenderQueue queue = Geometry);
//
//	/**
//	 *
//	 * @return
//	 */
//	const Queue<Renderer *> &getRenderQueue(RenderQueue queue = Geometry) const;
//
//	/**
//	 *	Get main render target.
//	 *	@Return non-null render target.
//	 */
//	inline FrameBufferObject* getRenderTarget(void){
//		return this->renderTarget;
//	}
//
//	/**
//	 *
//	 * @return
//	 */
//	inline PipelineQualitySettings* getQuality(void){
//		return this->qualitySettings;
//	}
//
//public:
//	static void draw(Scene* scene);
//
//protected:
//
//	RenderPipelineBase(IRenderer* renderer);
//	virtual ~RenderPipelineBase(void);
//
//protected:	/*	Prevent one from creating an instance of this class.	*/
//
//	/*  */
//	BufferObject* lightStateBuffer;
//	BufferObject* shadowStateBuffer;
//
//	/*  Optimization buffer.    */
//	/*  TODO resolve.   */
//	BufferObject* matricesBuffer;
//	BufferObject* boneBuffer;
//	BufferObject* materialBuffer;
//
//	/*  */
//	PipelineQualitySettings* qualitySettings;
//
//	/*  */
//	Queue<Renderer*>* queues;           /*  */
//	Queue<Renderer*> rqueue;	        /*  Opqaue. */
//	Queue<Renderer*> oqueue;            /*  Translucent.    */
//	Queue<Light*> lqueue;	            /*  Lights. */
//
//	/*  */
//	Queue<PostEffectObject*> overlay;   /*  */
//	std::vector<FrameBufferObject*> shadows;
//
//	/*  */
//	FrameBufferObject* postTarget;      /*  */
//	FrameBufferObject* renderTarget;    /*  */
//
//	/*  HDR shader. */
//	ShaderObject* hdr;
//	ShaderObject* gamma;
//
//	/*  */
//	GeometryObject* boundbox;

	};
}

#endif
