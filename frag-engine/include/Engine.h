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
	class FVDECLSPEC Engine : public Singleton<Engine> { // TODO determine if shall use singleton.
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
		static void init(int argc, const char **argv, SubSystem subsystems);

		static void initSubSystem(SubSystem subsytem);

		static void quit();

		static void registerModule(Module &module);
		static void unregisterModule(Module &module);

		static const char *getVersion();

		static RendererWindow *createWindow(IRenderer *renderer, const char *title, int x, int y, int width,
											int height);

		// TODO add event registers.

	  protected: /*	Engine attributes.	*/
	  private:	 /*	Prevent one from creating an instance of this class.	*/
		Engine();
		Engine(const Engine &other);
	};
} // namespace fragengine
#endif
