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
#ifndef _DEBUG_CAMERA_H_
#define _DEBUG_CAMERA_H_ 1
#include"Camera.h"

namespace fragview {
/**
 *	TODO this class will be able to have access to the gizmo class.
 *
 *	This camera will always be able to override the main camera at
 *	any given point in time.
 *
 */
	class DebugCamera : public Camera {
	public:
		DebugCamera(void);

		DebugCamera(const DebugCamera &other);

		~DebugCamera(void);

		/**
		 *	Update camera.
		 */
		void update(void);

	private:
		float Xsensity;
		float Ysensity;

	};
}

#endif
