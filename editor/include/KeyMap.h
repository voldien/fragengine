/**
    Simple physic simulation with a server-client model support.
    Copyright (C) 2017  Valdemar Lindberg

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
#ifndef _FRAG_EDITOR_KEY_MAP_H_
#define _FRAG_EDITOR_KEY_MAP_H_ 1
#include"System.h"
#include "CommandKey.h"
#include "CommandMouse.h"

namespace fragengine_editor{
	
}

/**
 *	Responsible for mapping key to
 *	function. Used for enabling remapping of
 *	the key to different function and external
 *	functionality via dynamic library plugin.
 */
class FVDECLSPEC KeyMap {
public:
	~KeyMap();

	typedef struct keyaction{

	}KeyAction;

	/*TODO TODO add additional parameter for adding more flexibility.*/
	/**
	 *
	 */
	typedef int (inputAction)(Scene* scene, const Command& command);
	typedef int (*keycodeaction)(Scene* scene, const Command& mouse);
	typedef int (*mousecodeaction)(Scene* scene, const Command& command);

	/**
	 * Map key code to action function.
	 * @param mod
	 * @param key
	 * @param action
	 */
	void setKeyBoardAction(unsigned int mod, unsigned int key, keycodeaction *action);

	/**
	 *	Get function pointer mapped by the modification and key
	 *
	 *	@Return non-null if function exists.
	 */
	keycodeaction getMapFunction(unsigned int mod, unsigned int key);

	/**
	 *
	 *
	 *	@Return non-null if function exists.
	 *	@Throws NotImplementedException
	 */
	keycodeaction getInverseMapFunction(unsigned int mod, unsigned int key);

public:	/*	Factory method for creating KeyMap objecct.*/

	/**
	 *	Load keymap from xml configuration file.
	 *	@Return non-null if successfully.
	 */
	static KeyMap* loadKeyMap(const char* cpath);

private:	/*	Prevent one from creating an instance of this class.	*/

	KeyMap();
	KeyMap(const KeyMap& other);

	/*	*/
	std::map<unsigned int, std::map<unsigned int, keycodeaction>> action;

};

#endif
