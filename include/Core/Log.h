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
#include"IO/IO.h"
#include"Ref.h"

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC Log {
	public:
		/**
		 *	Verbosity level of the program.
		 */
		 //TODO add map flagging.
		enum VERBOSITY {
			eQuite      = 0,    /*  */
			eError      = 1,    /*  */
			eVerbose    = 2,    /*  */
			eWarning    = 3,    /*  */
			eDebug      = 16,   /*  */
		};

		/**
		 *
		 */
		enum LogMappingFlag {
			fQuite      = (1 << eQuite),
			fError      = (1 << eError),
			fVerbose    = (1 << eVerbose),
			fWarning    = (1 << eWarning),
			fDebug      = (1 << eDebug),
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

		/*  TOOD improve the design.    */
		//TODO add support.
		static void addIOOutput(Ref<IO>& io, const VERBOSITY mapping);
		static void removeIOOutPut(Ref<IO>& io);
		static void clearIO(void);

	private:
		static int logv(VERBOSITY verbosity, const char *format, va_list va);
	};
}

#endif