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
#include<FragCore.h>

namespace fragengine {
	/**
	 *
	 */
	class FVDECLSPEC Time : public fragcore::Object {
	public:
		Time();

		/**
		 * Start time.
		 */
		void start();

		/**
		 * Get delta time since last frame.
		 *
		 * @return seconds.
		 */
		float deltaTime();

		/**
		 * Get smooth delta time. It uses
		 * the average delta time over multiple
		 * frames delta time.
		 * @return
		 */
		float smoothDeltaTime();

		/**
		 * Get time sense engine was initialized.
		 * @return number of seconds.
		 */
		unsigned int time();

		/**
		 * Get time since the engine was initialized.
		 * @return number of seconds and fractions of seconds.
		 */
		float timef();

		/**
		 *
		 * @return
		 */
		double timed();

		/**
		 *	Get unix epoch time stamp.
		 *	@Return
		 */
		long int getUnixTime();

		/**
		 * Get time scale.
		 * @return
		 */
		float getTimeScale();

		/**
		 * Set time scale.
		 * @param scale
		 */
		void setTimeScale(float scale);

		/**
		 *
		 * @return
		 */
		long int getTimeResolution();

		/**
		 *	Get fixed update time in milliseconds.
		 *
		 *	@Return
		 */
		float fixedTime();

		/**
		 *
		 */
		void internalUpdate();

		/**
		 *
		 * @return
		 */
		static Time *getCurrentTime();

		/**
		 *
		 * @param time
		 */
		static void setCurrentTime(Time *time);

		/**
		 *
		 * @return
		 */
		static const char *getDate();

	private:    /*	*/

		float internal_delta_timef();

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