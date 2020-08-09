/**
    Simple physic simulation with a server-client model support.
    Copyright (C) 2016  Valdemar Lindberg

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
#ifndef _RENDER_PIPELINE_FORWARD_H_
#define _RENDER_PIPELINE_FORWARD_H_ 1
#include"RenderPipelineBase.h"
#include"../Core/Ref.h"

namespace fragcore {
	/**
	 *	Responsible for rendering scene to default
	 *	framebuffer.
	 */
	class FVDECLSPEC RenderPipelineForward : public RenderPipelineBase {
	public:


		void draw(Scene *scene, FrameBuffer *frame, IRenderer *render) override;

		void setRenderer(Ref<IRenderer> &renderer) override;

		const Ref<IRenderer> &getRenderer(void) const override;

		Ref<IRenderer> getRenderer(void) override;

		void setViewport(int width, int height, IRenderer *render) override;

//	/**
//	 *	Draw scene from camera view.
//	 *
//	 */
//	virtual void drawCamera(Scene * scene,
//	                        Camera * camera,
		RenderQueue getSupportedQueue(void) const override;

		void drawCamera(Scene *scene, Camera *camera, IRenderer *render) override;
//	                        IRenderer * render);
//
//	/**
//	 *
//	 */
//	virtual void drawShadow(Scene *scene, Camera *camera, IRenderer *render);
//
//	virtual void drawOverlay(Scene*  scene,
//	                         Camera* camera,
//	                         IRenderer* render);

	public:

		RenderPipelineForward(Ref<IRenderer> render);

		virtual ~RenderPipelineForward(void);

	protected:    /*	Prevent one from creating an instance of this class.	*/


	};
}

//
//	//TODO move to the rendering pipeline.
//	/*  Uniform.    */
//	BufferDesc matrixDesc = {};
//	matrixDesc.type = BufferDesc::eUniform;
//	matrixDesc.data = NULL;
//	matrixDesc.size = (sizeof(float) * 16) * 512;
//	matrixDesc.hint = (BufferDesc::BufferHint)(BufferDesc::eWrite | BufferDesc::eStream);
//	matrixDesc.marker.markerName = "Matrix Uniform";
//	this->uniformMatrices = Ref<Buffer>(this->renderer->createBuffer(&matrixDesc));

#endif
