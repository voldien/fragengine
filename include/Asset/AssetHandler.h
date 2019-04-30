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
#ifndef _FRAGVIEW_ASSETHANDLER_H_
#define _FRAGVIEW_ASSETHANDLER_H_ 1
#include "FileNotify.h"

/**
 *
 */
class AssetHandler {
public:

	/**
	 * Handle asset change event.
	 * @param event
	 * @throws invalid_argument if event null or size less or equal to zero.
	 */
	static void handleAssetEvent(FileNotificationEvent* event);

	/**
	 * Handle drop asset.
	 * @param filepath
	 */
	static void handleAssetDrop(const char* filepath);
};


#endif