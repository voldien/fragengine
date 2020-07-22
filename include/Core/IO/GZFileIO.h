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
#ifndef _GZ_FILE_H_
#define _GZ_FILE_H_ 1
#include "IO.h"
#include "FileIO.h"
#if defined(FRAGVIEW_CORE_INTERNAL_IMP)	//TODO resolve to a single file or something later
#include <zlib.h>
#endif

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC GZFileIO : public FileIO {
	public:
		long read(long int nbytes, void *pbuffer) override;

		long write(long int nbytes, const void *pbuffer) override;

		long length(void) override;

		bool eof(void) const override;

		void seek(long int nbytes, Seek seek) override;

		unsigned long getPos(void) override;

		bool isWriteable(void) const override;

		bool isReadable(void) const override;

		bool flush(void) override;

		void close(void) override;

		void open(const char *path, Mode mode) override;

	private:
#if defined(FRAGVIEW_CORE_INTERNAL_IMP)
		gzFile gzFile;
	#endif
	public:
		GZFileIO(const char *path, Mode mode);
		//GZFileIO(Ref<IO> &io);
	};
}

#endif
