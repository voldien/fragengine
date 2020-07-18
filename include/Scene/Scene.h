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
#ifndef _FRAGVIEW_SCENE_H_
#define _FRAGVIEW_SCENE_H_ 1
#include"Def.h"
#include"Time.h"
#include"Prerequisites.h"
#include"Renderer/Buffer.h"
#include"SandBoxSubScene.h"

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC Scene : public SmartReference {
		friend class SceneFactory;

	protected:

		/**
		 * Create fragment sandbox.
		 */
		void createGLSLSandBoxScene(void);

	public:
		/**
		 * Get current fragment sandbox.
		 *
		 * @return
		 */
		SandBoxSubScene *getGLSLSandBoxScene(void);

		/**
		 *
		 * @return
		 */
		Time *getTime(void) const;

	private:

		SandBoxSubScene *glslSandBoxSubScene;
		Time *time;

		/*  Camera. */

		/*  Node.   */

		/*  Geometry Objects.   */
	public:

		Node *getRoot(void);

		Camera *getMainCamera(void);

	public:
		~Scene(void);
	};
}

//TODO relocate.
//extern UIDGenerator scene;
//extern UIDGenerator renderer;
//extern UIDGenerator irenderer;
//extern UIDGenerator system;

#endif
