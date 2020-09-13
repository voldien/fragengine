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
#include <Def.h>
#include<Core/Ref.h>
#include<Scene/Scene.h>
#include<FragCore.h>
#include "Windows/EditorWindow.h"
#include"Windows/EditorRenderWindow.h"

namespace frageditor
{
	/**
     *
     */
	class FVDECLSPEC FragEditor {
	public:
		FragEditor(SplashWindow *splashWindow, int argc, const char **argv);
		void run(void);

	protected:
		void init(void);

	private:
		EditorWindow *root;
		//GTKRendererWindow* rendererWindow;  //TODO improve and etc.
		//fragview::Ref<EditorRendererWindow> renderWindow;
		fragcore::IConfig *config;
		fragcore::Ref<fragcore::IRenderer> renderer;
		fragcore::Ref<fragengine::Scene> scene;
	};
}
#endif