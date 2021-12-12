/*
 *	FragEngine - Fragment Engine
 *	Copyright (C) 2016  Valdemar Lindberg
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _FRAG_ENGINE_ENGINE_H_
#define _FRAG_ENGINE_ENGINE_H_ 1
#include "App.h"
#include <Core/Singleton.h>
#include <Core/SmartReference.h>
#include <FragCore.h>
#include <RenderPrerequisites.h>

namespace fragengine {
	using namespace fragcore;
	/**
	 *	Engine class. Responsible for
	 *	combining each component.
	 */
	class FVDECLSPEC Engine : Object {
	  public:
		enum SubSystem {
			ALL = 0,
		};

		/**
		 * Initialize the engine.
		 * @param argc
		 * @param argv
		 * @param renderinginterface
		 * @param physicinterface
		 * @param config
		 */
		void init(int argc, const char **argv, SubSystem subsystems);

		void initSubSystem(SubSystem subsytem);

		void quit();

		void registerModule(Module &module);
		void unregisterModule(Module &module);

		const char *getVersion();

		void registerApp(App &app);

		RendererWindow *createWindow(IRenderer *renderer, const char *title, int x, int y, int width, int height);

		// TODO add event registers.
		Engine() = default;

	  protected: /*	Engine attributes.	*/
		std::map<unsigned int, App &> apps;

	  private: /*	Prevent one from creating an instance of this class.	*/

		Engine(const Engine &other);
	};
} // namespace fragengine
#endif
