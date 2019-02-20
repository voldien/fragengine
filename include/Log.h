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
#ifndef _FRAGVIEW_LOG_H_
#define _FRAGVIEW_LOG_H_ 1

/**
 *
 */
class Log {
public:
	/**
	 *	Verbosity level of the program.
	 */
	enum VERBOSITY {
		eQuite		= 0,	/**/
		eError      = 1,
		eVerbose	= 2,	/**/
		eDebug		= 16,   /**/
	};

	/**
	 * Set verbosity
	 * @param verbosity
	 */
	static void setVerbosity(VERBOSITY verbosity);

	/**
	 *
	 * @return
	 */
	static VERBOSITY getVerbosity(void);

	/**
	 *
	 * @param verbosity
	 * @param format
	 * @param ...
	 */
	static int log(VERBOSITY verbosity, const char *format, ...);

	/**
	 *
	 * @param format
	 * @param ...
	 * @return
	 */
	static int log(const char *format, ...);

	/**
	 *
	 * @param format
	 * @param ...
	 * @return
	 */
	static int error(const char *format, ...);

private:
	static int logv(VERBOSITY verbosity, const char *format, va_list va);
};

#endif