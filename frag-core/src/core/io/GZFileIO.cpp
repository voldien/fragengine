#include"Core/IO/GZFileIO.h"
#include<zlib.h>
#include <stdexcept>
#include <Utils/StringUtil.h>
#include <Exception/InvalidArgumentException.h>
#include <Exception/RuntimeExecption.h>

using namespace fragcore;

void GZFileIO::open(const char *path, Mode mode) {
	FileIO::open(path, mode);

	//TODO add other access modes.
	const char *m = NULL;
	switch (mode & ACCESS) {
		case READ:
			m = "rb";
			break;
		case WRITE:
			m = "wb";
			break;
		default:
			throw InvalidArgumentException("Invalid IO mode.");
	}

	/*  */
	this->gzFile = gzdopen(fileno(this->file), m);
	if (this->gzFile == NULL) {
		int error;
		const char *errMsg = gzerror(this->gzFile, &error);
		throw RuntimeException(fvformatf("Failed to open %s - error: %d | %s", path, error, errMsg));
	}

	/*  Set buffer size.    */
	gzbuffer(this->gzFile, 8192);
	if (mode & WRITE) {
		//gzsetparams
	}
}

void GZFileIO::close(void) {
	int error;
	error = gzclose(this->gzFile);
	if (error != Z_OK) {
		FileIO::close();
		throw RuntimeException(fvformatf("Failed to close gzfile %s", zError(error)));
	}
	FileIO::close();
}

long GZFileIO::read(long int nbytes, void *pbuffer) {
	long int nreadBytes = gzfread(pbuffer, 1, nbytes, this->gzFile);
	return nreadBytes;
}

long GZFileIO::write(long int nbytes, const void *pbuffer) {
	long int nWrittenBytes = gzfwrite(pbuffer, 1, nbytes, this->gzFile);
	if (nWrittenBytes == 0)
		throw RuntimeException(fvformatf("Failed to write to  gz file %s", gzerror(this->gzFile, NULL)));
	return nWrittenBytes;
}

long GZFileIO::length(void) {
	long size;
	unsigned long curPos = getPos();
	FileIO::seek(0, SET);
	//FileIO::read(4, info);
	return FileIO::length();
}


bool GZFileIO::eof(void) const {
	return FileIO::eof();
}


void GZFileIO::seek(long int nbytes, Seek seek) {
	//gzrewind
	FileIO::seek(nbytes, seek);
}


unsigned long GZFileIO::getPos(void) {
	//gzeof
	//gztell
	return FileIO::getPos();
}

bool GZFileIO::isWriteable(void) const {
	return FileIO::isWriteable();
}

bool GZFileIO::isReadable(void) const {
	return FileIO::isReadable();
}

bool GZFileIO::flush(void) {

	if (this->mode & WRITE) {
		int error;
		error = gzflush(this->gzFile, Z_FINISH);
		if (error != Z_OK)
			throw RuntimeException(zError(error));
		return true;
	}
	return false;
}

GZFileIO::GZFileIO(const char *path, Mode mode) {
	this->open(path, mode);
}
