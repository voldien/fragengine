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
#ifndef _NOT_IMPLEMENTED_EXCEPTION_H_
#define _NOT_IMPLEMENTED_EXCEPTION_H_ 1
#include<stdexcept>
#include<string>
#include "IException.h"

namespace fragview {
	/**
	 *	Class responsible for showing
	 *	the method is not implemented and thus
	 *	not supported.
	 */
	class NotImplementedException : public IException {
	public:

		NotImplementedException(void) : IException("Not implemented yet!") {}

		NotImplementedException(const std::string &arg) : IException(arg) {}

		const char *getName(void) const override {
			return typeid(this).name();
		}
	};
}

#endif