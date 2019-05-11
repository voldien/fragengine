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
#ifndef _OBJECT_H_
#define _OBJECT_H_ 1
#include"Def.h"
#include"UIDObject.h"
#include<string>
#include<string.h>

/**
 *	Base abstract object for scene
 *	objects.
 */
class FVDECLSPEC Object : public UIDObject {
public:

	inline Object(void) {
	}

	void setName(const std::string &name) {
		this->name = name;
	}

	std::string getName(void) const {
		return this->name;
	}

protected:	/*	*/

	Object& operator=(const Object& object){
		this->setName(object.getName());
		this->name = object.name;
	}

	unsigned int type;
private:	/*	Attributes.	*/

	std::string name;
};

#endif