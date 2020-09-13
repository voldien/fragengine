/**
	FragEngine, A Two layer Game Engine.
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
#ifndef _FRAG_ENGINE_INPUT_H_
#ifndef _FRAG_ENGINE_INPUT_H_ 1
#include "../Def.h"

namespace fragcore{

	/**
	 *	Abstraction class for accessing
	 *	input data.
	 */
	class FVDECLSPEC Input {
	public:

	
		static float getAxis(const char* opt);
		static PVVector2 location(void);


		static PVVector2 getDelta(void);

	
		static bool isKeyDown(unsigned int key);

	protected:	/*	Internal.	*/

		static void internalUpdate(void);

	};

}

#endif
