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
#ifndef _RENDERER_H_
#define _RENDERER_H_  1
#include"Renderer.h"
#include"Node.h"
#include"Material.h"

#include<vector>
namespace fragengine{
	/**
	 *	Responsible for containing
	*	geometries and shaders.
	*/
	class PVDECLSPEC Renderer : public Node
	{
	public:
		Renderer();

		/**
		 *
		 * @param material
		 * @param index
		 */
		void setMaterial(Material *material, int index = 0);

		/**
		 *
		 * @param geometry
		 * @param index
		 */
		void setGeometry(GeometryObject *geometry, int index = 0);

		/**
		 *
		 * @param index
		 * @return
		 */
		Material *getMaterial(int index);

		/**
		 *
		 * @param index
		 * @return
		 */
		GeometryObject *getGeometry(int index);

		/**
		 *
		 * @return
		 */
		int getNumGeometry() const;

		/**
		 *
		 * @return
		 */
		int getNumMaterial() const;


		/*  TODO add properties */
	private:    /*	Attributes.	*/

		std::vector<Material *> materials;
		std::vector<GeometryObject *> geometries;
		int numGeometry;                /*	*/
		int numMaterial;
	};
}
#endif
