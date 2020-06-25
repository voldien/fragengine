/**

    Copyright (C) 2014  Valdemar Lindberg

    This getProgram() is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This getProgram() is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this getProgram().  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _VIDEO_TEXTURE_H_
#define _VIDEO_TEXTURE_H_ 1
#include "Renderer/Texture.h"

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC VideoTexture : public SmartReference {
	public:

		VideoTexture(void);

		~VideoTexture(void);

		virtual bool isPlaying(void) const;

		virtual void play(void);

		virtual void stop(void);

		virtual void pause(void);

		virtual float getCurrentPosition(void) const;

		/*	Total length in seconds*/
		virtual float getTotalLength(void) const;

		virtual double getDuration(void) const;

		virtual double getTime(void) const;

		virtual bool isReadyToPlay(void) const;

		virtual Texture* getTexture(void) const;

	protected:
		void *pVideoData;
		//AudioClip* audioClip;
	};
}

#endif