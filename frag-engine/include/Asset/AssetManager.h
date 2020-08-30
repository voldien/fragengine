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
#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_ 1
#include"../Prerequisites.h"

namespace fragengine{
	/**
	 *
	 *
	 */
	class AssetManager{
	public:

		/**
		 *
		 */
		void setRootPath(const char* path);

		/**
		 * 
		 */
		const char* getRootPath(void);


		/**
		 *
		 * @return
		 */
		const std::vector<std::string> getSearchPaths(void) const;

	private:
	};
} // namespace fragengine

#endif
