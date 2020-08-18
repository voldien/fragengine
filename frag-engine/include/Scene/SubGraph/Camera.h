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
#ifndef _FV_CAMERA_H_
#define _FV_CAMERA_H_ 1
#include"Frustum.h"
#include"../../RenderPipeline/IRenderPipelineBase.h"

namespace fragengine {
	using namespace fragcore;
	/**
	 *	Camera responsible for configuring the
	 *	view in rendering.
	 */
	class FVDECLSPEC Camera : public Frustum {
	public:
		enum ClearMode {
			DontClear = (1 << 0),     /*	*/
			Clear = (1 << 1),     /*	*/
			SkyBox = (1 << 2)      /*	*/
		};

		enum ProjectionMode {
			Perspective = (1 << 0),     /*	*/
			Orthographic = (1 << 1),     /*	*/
		};

	public:
		Camera(void);

		Camera(const Camera &other);

		~Camera(void);

		/**
		 * Get clearing masking flag.
		 * @return
		 */
		ClearMode clearMask(void) const;

		/**
		 * Set clearing masking flag.
		 * @param mask
		 */
		void setClearMask(ClearMode mask);

		/**
		 *
		 * @return
		 */
		ProjectionMode getProjection(void) const;

		//pixelHeight
		//pixelRect
		//pixelWidth
		/**
		 *
		 * @param projection
		 */
		void setProjection(ProjectionMode projection);

		/*	Real camera attributes.	*/
		void setfocalLength(float f);
		/**
		 *
		 * @param use
		 */
		void
		useHDR(bool use);

		float aspect();

		/**
		 *
		 * @return
		 */
		bool
		useHDR(void) const;

		//	/**
		//	 *	Set post effect.
		//	 */
		//	void setPostEffect(PostEffectObject *post, int index = -1);
		//
		//	PostEffectObject *getPostEffect(int index);
		//
		//
			/**
			 *
			 * @param pipeline
			 */
		void setRenderingPath(Ref<IRenderPipelineBase>& pipeline);

		/**
			 *
			 * @return
			 */
		Ref<IRenderPipelineBase> getRenderingPath(void) const;
		//
		//
		//	/**
		//	 *
		//	 * @param target
		//	 */
		//	void setRenderTarget(FrameBufferObject *target);
		//
		//	/**
		//	 *
		//	 * @return
		//	 */
		//	FrameBufferObject *getRenderTarget(void) const;

	protected:    /*	Attributes.	*/

		ClearMode clear;                    /*	*/
		ProjectionMode projection;          /*  */
		bool hdr;                           /*  */
//
//	/*  TODO resolve.   */
//	PostEffectObject *effects[16];     /*	Post effects.	*/
//	RenderPipelineBase *pipeline;
//	FrameBufferObject *target;
		Ref<IRenderPipelineBase> overrideRenderer;
	};
}
#endif
