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
#ifndef _PV_COMMAND_H_
#define _PV_COMMAND_H_ 1
#include <PoolAllactor.h>
#include"Def.h"
#include"Prerequisites.h"

/**
 *	Single command object. The command is assoicated with
 *	a scene for which the command has affect on.
 *	Where the command is based on HID (Human input devices).
 */
class FVDECLSPEC Command {
public:

	virtual void execute() = 0;
	virtual void undo() = 0;

	/**
	 * Get command associated with.
	 * @return non-null scene.
	 */
	Scene *getScene() const;

protected:	/*	*/

	Command();
	Command(Scene* scene);
	Command(const Command& other);
	virtual ~Command();

//	Scene* scene;			/*	Scene associated with the command.  */
//	CommandType type;
};

#endif
