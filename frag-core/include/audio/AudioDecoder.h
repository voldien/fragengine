/**
	FragEngine, A Two layer Game Engine.
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
#ifndef _FRAG_CORE_AUDIO_DECODER_H_
#define _FRAG_CORE_AUDIO_DECODER_H_ 1
#include "../Def.h"
#include "../Core/SmartReference.h"
#include "../Core/Ref.h"
#include "../Core/IO/IO.h"
#include <ogg/ogg.h>
#include <opus/opus.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

namespace fragcore
{
	/**
	 * 
	 */
	class FVDECLSPEC AudioDecoder : public SmartReference
	{
	public:
		AudioDecoder(Ref<IO> &io);
		virtual ~AudioDecoder(void);

		virtual void seek(long int microseconds);

		void *getData(long int *size);

		void *getPage(int i);

	public:
		Ref<IO> io;
		OggVorbis_File *ov;
		//AudioFormat format;
		long int channels;
		long int samples;
	};
}


#endif