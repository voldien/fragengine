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
#ifndef _FRAG_EDITOR_FRAGVIEWEDITOR_H_
#define _FRAG_EDITOR_FRAGVIEWEDITOR_H_ 1
#include "Windows/EditorRenderWindow.h"
#include "Windows/EditorWindow.h"
#include "Windows/SplashWindow.h"
#include <Core/Ref.h>
#include <Core/TaskScheduler/TaskScheduler.h>
#include <Def.h>
#include <FragCore.h>
#include <RendererWindow.h>
#include <Scene/Scene.h>

namespace frageditor {
	/**
	 *
	 */
	class FVDECLSPEC FragEditor {
	  public:
		FragEditor(SplashWindow *splashWindow, int argc, const char **argv);
		void run();

	  protected:
		void init();

	  private:
		EditorWindow *root;

		fragcore::Ref<fragcore::RendererWindow> renderWindow;
		fragcore::Ref<fragcore::TaskScheduler> taskSch;
		fragcore::IConfig *config;
		fragcore::Ref<fragcore::IRenderer> renderer;
		fragcore::Ref<fragengine::Scene> scene;
	};
} // namespace frageditor
#endif
