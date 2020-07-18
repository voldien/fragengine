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
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_ 1
#include"Def.h"
#include"Scene.h"


namespace fragview{
	/**
	 *
	 */
	class FVDECLSPEC SceneManager {
	public:
		SceneManager(void);

		SceneManager(const SceneManager &scene);

		~SceneManager(void);

		/**
		 *
		 * @return
		 */
		Scene *getCurrentScene(void) const;

		/**
		 *
		 * @param scene
		 */
		void setCurrentScene(Scene *scene);

		/**
		 *
		 * @param index
		 * @param scene
		 */
		void setScene(int index, Scene *scene);

		/**
		 *
		 * @param index
		 * @return
		 */
		Scene *getScene(int index);

		/**
		 *
		 * @return
		 */
		Scene *getNextScene(void);

		/**
		 *
		 * @return
		 */
		Scene *getPreviousScene(void);

		void loadScene(int index);
		void loadSceneAsync(int index);
		void loadScene(const std::string &name);
		void loadSceneAsync(const std::string &name);

	private:
		std::vector<Scene *> scenes;
		std::vector<Scene *>::iterator current;
	};
}

#endif