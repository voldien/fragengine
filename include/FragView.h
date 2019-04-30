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
#ifndef _FRAG_VIEW_H_
#define _FRAG_VIEW_H_ 1
#include "Renderer/IRenderer.h"
#include "Asset/FileNotify.h"
#include "RenderPipeline.h"
#include "Core/Config.h"
#include <taskSch.h>

/**
 * Main class for the fragment viewer
 * executable program.
 */
class FVDECLSPEC FragView {
public:
    FragView(int argc, const char** argv);
    ~FragView(void);

    /**
     * Run the application.
     */
    void run(void);

	/**
	 * Get version of fragview program.
	 * @return non-null terminated string.
	 */
    static const char* getVersion(void);

protected:

	/**
	 * Create window for displaying.
	 */
    void* createWindow(int x, int y, int width, int height);

private:    /*  */

    IRenderer* renderer;                /*  Low level rendering API interface.  */
    RenderPipeline* display;            /*  Perform rendering.  */
    Config* config;                     /*  Current config.    */
	FileNotify* notify;                 /*  Notify Asset changes.  */
	schTaskSch* sch;                    /*  Scheduler.  */
    void* window;                       /*  Window pointer reference.   */
	Scene *scene;                       /*  Current scene.  */
};

#endif