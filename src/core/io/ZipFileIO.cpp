#include"Core/IO/ZipFileIO.h"
#include"Core/IO/ZipFile.h"
#include<zlib.h>
#include<zip.h>
#include <stdexcept>
#include <Utils/StringUtil.h>
#include <Exception/RuntimeExecption.h>
#include <Exception/NotImplementedException.h>
#include <Exception/InvalidArgumentException.h>

using namespace fragview;

ZipFileIO::ZipFileIO(zip_file_t *file, zip_int64_t index, Ref<ZipFile> ref) {
	this->file = file;
	this->zipfile = ref;
	this->index = index;
	this->zipfile->increment();
}

ZipFileIO::ZipFileIO(void) {
	this->file = NULL;
}

ZipFileIO::ZipFileIO(const ZipFileIO &other) {
	this->file = other.file;
}

ZipFileIO::~ZipFileIO(void) {

}

void ZipFileIO::open(const char *path, Mode mode) {

}

void ZipFileIO::close(void) {
	int err;

	err = zip_fclose(this->file);
	if (err != ZIP_ER_OK) {
		char buf[1024];
		zip_error_to_str(buf, sizeof(buf), err, errno);
		throw RuntimeException(fvformatf("Failed to close zip file %s", buf));
	}

	//zip_file_add

	if (this->zipfile->deincreemnt()) {
		this->zipfile->release();
		delete this->zipfile.ptr();
	}
}

long ZipFileIO::read(long int nbytes, void *pbuffer) {
	nbytes = zip_fread(this->file, pbuffer, nbytes);
	if (nbytes == -1) {
		char buf[1024];
		zip_error_to_str(buf, sizeof(buf), nbytes, errno);
		throw RuntimeException(fvformatf("Failed to close zip file %s", buf));
	}
	return nbytes;
}

long ZipFileIO::write(long int nbytes, const void *pbuffer) {
	throw NotImplementedException("Write is not supported");
	return nbytes;
}

bool ZipFileIO::eof(void) const {
	return false;
}

long ZipFileIO::length(void) {
	zip_int64_t prev;
	zip_int64_t len;

//	prev = zip_ftell(this->file);
//
//	zip_fseek(this->file, 0, SEEK_END);
//	len = zip_ftell(this->file);
//	zip_fseek(this->file, prev, 0);
	return len;
}

void ZipFileIO::seek(long int nbytes, Seek seek) {
	int whence;
	switch (seek) {
		case SET:
			whence = SEEK_SET;
			break;
		case CUR:
			whence = SEEK_CUR;
			break;
		case END:
			whence = SEEK_END;
			break;
		default:
			throw InvalidArgumentException("Invalid seek enumerator.");
	}

//	zip_int8_t err = zip_fseek(this->file, nbytes, whence);
//	if (err != 0) {
//		char buf[1024];
//		int sys_err;
////		zip_error_get(zip, &err, &sys_err);
////		zip_error_to_str(buf, sizeof(buf), err, errno);
////		throw InvalidArgumentException(fvformatf("can't open `%s':\n\t%s\n", path, buf));
//	}
//	//zip_fseek
}


unsigned long ZipFileIO::getPos(void) {
	return 0;//zip_ftell(this->file);
}

bool ZipFileIO::isWriteable(void) const {
	zip_uint32_t attr;
	//int err = zip_file_get_external_attributes((zip_t*)this->zipfile->getZipObject(), 0, ZIP_OPSYS_UNIX, NULL, &attr);

	return true;
}

bool ZipFileIO::isReadable(void) const {
	//ZIP_RDONLY
	return true;
}

bool ZipFileIO::flush(void) {

	return false;
}
