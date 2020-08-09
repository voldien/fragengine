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
#ifndef _FRAGVIEW_WINDOWRENDERER_H_
#define _FRAGVIEW_WINDOWRENDERER_H_ 1

#include "../Def.h"
#include "../Core/Display.h""
#include "../Core/Ref.h"
#include "../Prerequisites.h"
#include "../Core/SmartReference.h"
#include "../Core/Window.h"
#include "IRenderer.h"

namespace fragcore {
	/**
	 *
	 */
	class FVDECLSPEC RendererWindow : public Window {
		friend class IRenderer;
	public:
		virtual void swapBuffer(void) = 0;
		virtual void vsync(bool state) = 0;

		//virtual const char* getRendererAPI(void);

	protected:  /*  Renderer methods.   */
		virtual bool assertConfigAttributes(const IConfig *iConfig) = 0;
		virtual void createWindow(int x, int y, int width, int height, const char *api) = 0;
		virtual void useWindow(void *data) = 0;

	protected:  /*  */
		const char *api;
		Ref<IRenderer> renderer;
	};

}

#endif
