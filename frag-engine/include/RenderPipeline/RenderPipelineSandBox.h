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
#ifndef _FRAGENGINE_RENDERPIPELINE_SANDBOX_H_
#define _FRAGENGINE_RENDERPIPELINE_SANDBOX_H_ 1
#include "IRenderPipelineBase.h"

namespace fragcore {
	/**
	 *
	 */
	class FVDECLSPEC RenderPipelineSandBox : public IRenderPipelineBase {
	public:
		RenderPipelineSandBox(Ref<IRenderer> &renderer);

		virtual ~RenderPipelineSandBox(void);

		void setRenderer(Ref<IRenderer> &renderer) override;

		const Ref<IRenderer> &getRenderer(void) const override;

		Ref<IRenderer> getRenderer(void) override;

		void setViewport(int width, int height, IRenderer *render) override;

		virtual void draw(Scene *scene, FrameBuffer *frame, IRenderer *render) override;

		RenderQueue getSupportedQueue(void) const override;

	protected:
		virtual void createFrameTexture(IRenderer *renderer, unsigned int width, unsigned height);

		virtual void init(Ref<IRenderer> &renderer, const IConfig *config);
		//virtual void updateUniform(void);

	private:

		Ref<GeometryObject> quadDisplay;
		Ref<Buffer> quadDisplayIndirect;
		Ref<ProgramPipeline> displayShader;

		/*  Compute shader objects. */
		Ref<Texture> compute;
		Ref<Texture> computeView;
		Ref<Buffer> computeIndirect;
		bool supportComputeShader;

		Ref<FrameBuffer> frameBuffer;
		ViewPort *viewPort;
		Capability capability;
	};
}

#endif