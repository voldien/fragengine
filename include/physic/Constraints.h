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
#ifndef _CONSTRAINTS_H_
#define _CONSTRAINTS_H_ 1
#include"../Def.h"


namespace fragview {
	class RigidBody;
	/**
	 *
	 */
	class FVDECLSPEC Constraints {
		friend class DynamicInterface;
	private:
		inline Constraints(void){}

		virtual ~Constraints(void);
	public:

		/**
		 *
		 * @param r1
		 * @param r2
		 */
		inline void attachRigidbody(RigidBody* r1,
		        RigidBody*  r2){
	//		attachRigidbody(getMappedObject(), r1, r2);
		}

	protected:

		virtual void attachRigidbody(void*  pobj,
				RigidBody*  r1, RigidBody*  r2);

	};
}
#endif
