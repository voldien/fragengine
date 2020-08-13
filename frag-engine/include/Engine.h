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
#ifndef _FRAG_ENGINE_ENGINE_H_
#define _FRAG_ENGINE_ENGINE_H_ 1
#include<FragCore.h>
#include<Core/SmartReference.h>

// namespace fragengine {
// 	using namespace fragview;
// 	/**
// 	 *	Engine class. Responsible for
// 	*	combining each component.
// 	*/
// 	class FVDECLSPEC Engine : public SmartReference { 
// 	public:

// 		/**
// 		 * Initialize the engine.
// 		 * @param argc
// 		 * @param argv
// 		 * @param renderinginterface
// 		 * @param physicinterface
// 		 * @param config
// 		 */
// 		static void init(int argc,
// 				const char** argv,
// 				Ref<Config>& config = NULL);

// 		/**
// 		 * 	Get version of the engine.
// 		 *
// 		 *	@Return non-null terminated string.
// 		*/
// 		static const char* getVersion(void);

// 		/*	TODO make engine class a expert object for rendering and physic dynamicInterface.	*/
// 		/**
// 		 *	Create a renderable window from the current set rendering interface.
// 		*
// 		*	@Return SDL_Window pointer data type.
// 		*/
// 		static void* createWindow(RenderingInterface* renderer, const char* title, int x, int y, int width, int height);

// 		/**
// 		 *
// 		 * @param commandController
// 		 */
// 		static void setCommandController(CommandController* commandController);

// 		/**
// 		 *
// 		 * @return
// 		 */
// 		static SceneManager* getSceneManager(void);

// 		/**
// 		 *	Get engine configuration of the program.
// 		*	@Return non-null if exists.
// 		*/
// 		static Ref<Config> getConfig(void);

// 		/**
// 		 * Start running.
// 		 */
// 		static void run(void);

// 	protected:	/*	Engine attributes.	*/

// 		static Ref<SceneManager> sceneManager;      /*  */
// 		static Ref<CommandController> controller;   /*  */
// 		static Ref<Config> config;					/*	*/
// 		static std::vector<Scene*> scenes;      /*  */ //TODO remove

// 	private:	/*	Prevent one from creating an instance of this class.	*/

// 		Engine(void);
// 		Engine(const Engine& other);

// 	};
// } // namespace fragengine
#endif
