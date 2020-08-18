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
//TODO determine if shall be relocated to the engine.
#ifndef _PV_INPUT_H_
#define _PV_INPUT_H_ 1
#include "../Def.h"

namespace fragcore{


	/**
	 *	Abstraction class for accessing
	*	input data.
	*/
	class FVDECLSPEC Input {
	public:

		/**
		 *	@Return
		*/
		static float getAxis(const char* opt);

		/**
		 *	Get location of mouse in window position of
		*	the application.
		*
		*	@Return
		*/
		static PVVector2 location(void);

		/**
		 *	Get delta motion.
		*
		*	@Return
		*/
		static PVVector2 getDelta(void);

		/**
		 *	Check if key is pressed.
		*/
		static bool isKeyDown(unsigned int key);

	protected:	/*	Internal.	*/

		/**
		 *	Update internal input associated
		*	data.
		*/
		static void internalUpdate(void);

	};

}

#endif
