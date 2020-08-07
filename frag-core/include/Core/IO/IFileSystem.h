
#ifndef _FV_IFILESYSTEM_H_
#define _FV_IFILESYSTEM_H_ 1
#include"ASync.h"
#include<vector>

namespace fragview {

	/**
	 *
	 */
	class FVDECLSPEC IFileSystem : public ASync {
	public:

		//TODO add support for async.
		virtual IO *openFile(const char *path, IO::Mode mode) = 0;   /*  Open based on the filename extension.*/
		virtual ASyncHandle openASyncFile(const char* path, IO::Mode mode){
			Ref<IO> io = Ref<IO>(openFile(path, mode));
			return this->asyncOpen(io);
		}
		virtual void closeFile(IO *io) = 0;
		//void closeFile(ASyncHandle handle);

		virtual void remove(const char *path) = 0;
		virtual void rename(const char *oldPath, const char *newPath) = 0;

		virtual void createFile(const char *path) = 0;
		virtual void createDirectory(const char *path) = 0;

		virtual bool isReadable(const char *path) const = 0;
		virtual bool isWriteable(const char *path) const = 0;
		virtual bool exists(const char *path) const = 0;

		virtual bool isASyncSupported(void) const = 0;

		//virtual FileAccess getFileAccess(const char* path) = 0;
		//virtual DirectoryAccess getDirectoryAccess(const char* path) = 0;

		virtual std::vector<std::string>
		listFiles(const char *directory) const = 0;        /*  Display only files in directory.    */
		virtual std::vector<std::string>
		listDirectories(const char *directory) const = 0;  /*  Display only directories in directory.  */
		virtual std::vector<std::string>
		list(const char *directory) const = 0;              /*  Display everything in directory. */
	public:

	};
}

#endif