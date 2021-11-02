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
#ifndef _FRAG_ENGINE_SCENEFACTORY_H_
#define _FRAG_ENGINE_SCENEFACTORY_H_ 1
#include "Scene.h"

namespace fragengine {
	/**
	 *	Responsible for creating scene object
	 *	where object will be added in order for them
	 *	be part of physic simulation and rendered to screen.
	 */
	class FVDECLSPEC SceneFactory {
	public:

		/**
		 *
		 */
		enum WorldScene {
			eSandBox = 0x1,     /*  Shader sandbox. */
			eWorldSpace = 0x2,  /*  World space for 3D geometry objects.    */
		};

		/**
		 * Create scene.
		 * @param rendering rendering interface assoicated with the scene.
		 * @param world
		 * @return non-null scene object.
		 */
		static Scene *createScene(fragcore::IRenderer *rendering, WorldScene world);

	private:    /*	Prevent one from creating an instance of this class.	*/

		SceneFactory();
		SceneFactory(const SceneFactory &other);
	};
}

#endif
