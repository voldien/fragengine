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
#ifndef FRAGVIEW_DISPLAY_H_
#define FRAGVIEW_DISPLAY_H_ 1
#include"../Def.h"
#include "Object.h"
#include"../Renderer/RenderDesc.h"
#include<vector>

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC Display : public Object {
	public:

		virtual unsigned int x(void) const = 0;

		virtual unsigned int y(void) const = 0;

		virtual unsigned int width(void) const = 0;

		virtual unsigned int height(void) const = 0;

		virtual unsigned int refreshRate(void) const = 0;

		typedef struct mode_t {
			int x;
			int y;
			unsigned int width;
			unsigned int height;
			unsigned int refreshRate;
			TextureFormat format;
		} Mode;

		typedef struct dpi_t {
			float ddpi;
			float hdpi;
			float vdpi;
		} DPI;

		virtual std::vector<Mode> getModes(void) const = 0;

		virtual void getDPI(DPI *dpi) = 0;

		virtual TextureFormat getFormat(void) = 0;

	public:

//		static int getNumDisplays(void);
//		static Display getDisplay(unsigned int index);
		//static Display getAssociatedDisplay(SDL_Window* windiw9);
		//static void VDAPIENTRY getPrimaryScreenResolutions(int* num, Resolution** resolutions);
	};

}

#endif