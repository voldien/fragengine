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
#ifndef _ABSTRACT_IO_H_
#define _ABSTRACT_IO_H_ 1
#include "FileAccess.h"
#include"../../Prerequisites.h"

namespace fragview {

	/**
	 *
	 */
	class FVDECLSPEC IO : public FileAccess {
	public:
		enum Seek {
			SET = 0x0,  /*  From beginning position.    */
			CUR = 0x1,  /*  Current position.   */
			END = 0x2   /*  From end position.  */
		};

		enum Mode {
			READ    = 0x1,              /*  */
			WRITE   = 0x2,              /*  */
			ACCESS = (READ | WRITE),    /*  */
			APPEND  = 0x4               /*  Set mode to append with WRITE.  */
		};

	public:
		//virtual ~IO(void);

		virtual void close(void) = 0;

		virtual long int read(long int nbytes, void *pbuffer) = 0;

		virtual long int write(long int nbytes, const void *pbuffer) = 0;

		//virtual long int format(const char* fvformatf, ...) = 0;	//TODO move to IOUtil

		virtual bool eof(void) const = 0;

		virtual long int length(void) = 0;

		virtual void seek(long int nbytes, Seek seek) = 0;

		virtual unsigned long getPos(void) = 0;

		virtual bool isWriteable(void) const = 0;

		virtual bool isReadable(void) const = 0;

		virtual bool flush(void) = 0;

//		virtual String get_path() const { return ""; } /// returns the path for the current open file
//		virtual String get_path_absolute() const { return ""; } /// returns the absolute path for the current open file

//		virtual void set_endian_swap(bool p_swap) { endian_swap = p_swap; }
//		inline bool get_endian_swap() const { return endian_swap; }

		//virtual IFileSystem* getFileSystem(void);
		enum IOOperation
		{
			OP_ALL,
			OP_READ,
			OP_WRITE,
			OP_EOF,
			OP_LENGTH,
			OP_SEEK,
			OP_GETPOS,
			OP_FLUSH,
		};
		//virtual isOperationSupported(void);

	protected:  /*  Internal methods.   */
		virtual void open(const char* path, Mode mode) = 0;
	};

}

#endif