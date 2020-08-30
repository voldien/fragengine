#include <cstdio>
#include <cassert>
#include <malloc.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <Utils/StringUtil.h>
#include <Core/IO/FileSystem.h>
#include <Core/IO/GZFileIO.h>
#include <Exception/InvalidArgumentException.h>
#include <Exception/RuntimeExecption.h>
#include <Core/SystemInfo.h>
#include"Core/IO/FileSystem.h"

using namespace fragcore;

IO *FileSystem::openFile(const char *path, IO::Mode mode) {
	const char *extension = FileSystem::getFileExtension(path);

	// Parse if possible IO type exists.
	if (strcmp(extension, "gz") == 0)
		return new GZFileIO(path, mode);
	// Open default as IO file.
	return new FileIO(path, mode);
}

void FileSystem::closeFile(IO *io) {
	io->close();
	//TODO determine what shall be done more.
	//TODO determine how it can be released in a proper manner.
}
const char *FileSystem::getBaseName(const char *path) {
	return basename(path);  //TODO relocate to the OS IO table lookup.
}


void FileSystem::remove(const char *path) {
	if (::remove(path) != 0)
		throw RuntimeException(fvformatf("%s", strerror(errno)));
}

void FileSystem::rename(const char *oldPath, const char *newPath) {
	if (::rename(oldPath, newPath) != 0)
		throw RuntimeException(fvformatf("%s", strerror(errno)));
}

bool FileSystem::exists(const char *path) const {
	FILE *f = fopen(path, "r+");
	if (f) {
		fclose(f);
		return true;
	}
	return false;
}


bool FileSystem::isReadable(const char *path) const {
	FILE *f = fopen(path, "r+");
	if (f) {
		fclose(f);
		return true;
	}
	return false;
}

bool FileSystem::isWriteable(const char *path) const {
	FILE *f = fopen(path, "w+");
	if (f) {
		fclose(f);
		return true;
	}
	return false;
}

std::string FileSystem::getAbsolutePath(const char *path)
{
	char resolved_path[PATH_MAX];
	realpath(path, resolved_path);
	return resolved_path;
}

std::string FileSystem::getRelativePath(const char *path)
{
	
}

const char *FileSystem::getFileExtension(const char *path) {
	const char *dot = strrchr(path, '.');
	if (!dot || dot == path) return "";
	return dot + 1;
}

void FileSystem::createFile(const char *path) {
	FILE *f = fopen(path, "ab+");
	if(f == NULL)
		throw RuntimeException(fvformatf("Failed to open file %s, %s.\n", path, strerror(errno)));
	fclose(f);
}

void FileSystem::createDirectory(const char *path) {
	//mkdir(path);
}

bool FileSystem::isASyncSupported(void) const{
	return *this->getScheduler() != NULL;
}

std::vector<std::string> FileSystem::listFiles(const char *directory) const {
	return std::vector<std::string>();
}

std::vector<std::string> FileSystem::listDirectories(const char *directory) const {
	return std::vector<std::string>();
}

std::vector<std::string> FileSystem::list(const char *directory) const {
	return std::vector<std::string>();
}

static FileSystem *fileSystem = NULL;
FileSystem *FileSystem::getFileSystem(void) {
	if (fileSystem == NULL)
		throw RuntimeException("FileSystem must created before utilizing it.");
	return fileSystem;
}

FileSystem *FileSystem::createFileSystem(Ref<IScheduler> &ref)
{
	fileSystem = new FileSystem(ref);
	return fileSystem;
}

FileSystem::FileSystem(Ref<IScheduler> &ref) : IFileSystem()
{

	/*  Lookup system io functions.  */
	switch(SystemInfo::getOperatingSystem()){
		default:
			break;
	}

	this->setScheduleReference(ref);
}

FileSystem::~FileSystem(void) {
	/*  Release all resources.  */
}


