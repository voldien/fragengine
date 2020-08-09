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
#ifndef _FRAG_ENGINE_TIME_H_
#define _FRAG_ENGINE_TIME_H_ 1
#include"Def.h"
#include"../Core/Object.h"

namespace fragcore {
	/**
	 *
	 */
	class FVDECLSPEC Time : public Object {
	public:
		Time(void);

		/**
		 * Start time.
		 */
		void start(void);

		/**
		 * Get delta time since last frame.
		 *
		 * @return seconds.
		 */
		float deltaTime(void);

		/**
		 * Get smooth delta time. It uses
		 * the average delta time over multiple
		 * frames delta time.
		 * @return
		 */
		float smoothDeltaTime(void);

		/**
		 * Get time sense engine was initialized.
		 * @return number of seconds.
		 */
		unsigned int time(void);

		/**
		 * Get time since the engine was initialized.
		 * @return number of seconds and fractions of seconds.
		 */
		float timef(void);

		/**
		 *
		 * @return
		 */
		double timed(void);

		/**
		 *	Get unix epoch time stamp.
		 *	@Return
		 */
		long int getUnixTime(void);

		/**
		 * Get time scale.
		 * @return
		 */
		float getTimeScale(void);

		/**
		 * Set time scale.
		 * @param scale
		 */
		void setTimeScale(float scale);

		/**
		 *
		 * @return
		 */
		long int getTimeResolution(void);

		/**
		 *	Get fixed update time in milliseconds.
		 *
		 *	@Return
		 */
		float fixedTime(void);

		/**
		 *
		 */
		void internalUpdate(void);

		/**
		 *
		 * @return
		 */
		static Time *getCurrentTime(void);

		/**
		 *
		 * @param time
		 */
		static void setCurrentTime(Time *time);

		/**
		 *
		 * @return
		 */
		static const char *getDate(void);

	private:    /*	*/

		float internal_delta_timef(void);

		/*  */
		long int ticks;
		float scale;
		float fixed;

		/*	TODO clean up later by relocating it to the time class.*/
		float gc_fdelta;
		float delta_data[5];
		unsigned int nDeltaTime = sizeof(delta_data) / sizeof(delta_data[0]);
		unsigned int idelta;

		/*  */
		static Time *curTime;
		unsigned long timeResolution;
		unsigned long _private_level_startup;
	};
}

#endif