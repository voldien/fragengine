#include"Core/IO/GZFileIO.h"
#include<Core/IO/ZipFile.h>
#include<Core/IO/FileIO.h>
#include<Core/IO/ZipFileIO.h>
#include<Core/IO/FileSystem.h>
#include <Core/IO/BufferIO.h>
#include <Core/Display.h>
#include<gtest/gtest.h>
#include <SDL2/SDL.h>
#include<sched.h>
#include<Core/RefPtr.h>
#include<FragViewCore.h>
using namespace fragview;

class IOTest : public testing::Test {
protected:
	void SetUp() override {
		files.push_back("Makefile");
		files.push_back("CMakeLists.txt");
		files.push_back("src/IO.cpp");
		FileWrite = "tmp.txt";

		gzFiles.push_back("");
		gzFiles.push_back("");
		gzFiles.push_back("");
		gzFileWrite = "tmp.gz";

		zipInFiles.push_back("glsl/wave.frag");
		zipInFiles.push_back("glsl/sepia.frag");
		zipInFiles.push_back("glsl/sepia.comp");

		zipFile = "zipfile.zip";
	}

	static void readcallback(ASync* async, ASyncHandle handle) {
		
	}

	static void writecallback(ASync* aSync, ASyncHandle handle){

	}

	std::vector<char *> files;
	char *FileWrite;
	std::vector<char *> gzFiles;
	char *gzFileWrite;
	std::vector<char *> zipInFiles;
	char *zipFile;
};


TEST_F(IOTest, Async) {
	ASyncHandle handle;
	IScheduler* sch;

	/*  Create scheduler.   */
	//ASSERT_EQ(schCreateTaskPool(&sch, 2, SCH_FLAG_NO_AFM, 32), SCH_OK);
	//ASSERT_EQ(schRunTaskSch(&sch), SCH_OK);

	/*  */
	size_t bufSize = 512;
	char *buf = (char *) malloc(bufSize);

	Ref<IScheduler> refPtr = Ref<IScheduler>(sch);

	// BufferIO
	ASync async(refPtr);
	BufferIO bufferIo(bufSize);
	Ref<IO> redBufIO = Ref<IO>(&bufferIo);
	ASSERT_NO_THROW(handle = async.asyncOpen(redBufIO));
	ASSERT_NO_THROW(async.asyncWriteFile(handle, buf, bufSize, writecallback));
	ASSERT_NO_THROW(async.asyncWait(handle));
	ASSERT_NO_THROW(async.asyncClose(handle));

	// FileSystem Async.
	FileSystem *fileSystem;
	ASSERT_NO_THROW(fileSystem = FileSystem::createFileSystem(refPtr));
	ASSERT_NO_THROW(handle = fileSystem->openASyncFile(files[0], IO::READ));
	ASSERT_GE(handle, 0);
	ASSERT_NO_THROW(fileSystem->asyncReadFile(handle, buf, bufSize, readcallback));
	ASSERT_NO_THROW(fileSystem->asyncWait(handle));
	ASSERT_NO_THROW(fileSystem->asyncClose(handle));

	// FileSystem ZIP over IO object.
	Ref<IO> io = Ref<IO>(fileSystem->openFile(zipFile, IO::READ));
	ZipFile* zipFileSystemIO;
	ASSERT_NO_THROW(zipFileSystemIO = ZipFile::createZipFileObject(io, refPtr));
	handle = zipFileSystemIO->openASyncFile(zipInFiles[0], IO::READ);
	ASSERT_GE(handle, 0);
	ASSERT_NO_THROW(zipFileSystemIO->asyncReadFile(handle, buf, bufSize, readcallback));
	ASSERT_NO_THROW(zipFileSystemIO->asyncWait(handle));
	zipFileSystemIO->asyncClose(handle);
	io->close();
	delete zipFileSystemIO;

	/**/
	ZipFile *zipFileSystem = NULL;
	ASSERT_NO_THROW(zipFileSystem = ZipFile::createZipFileObject(zipFile, refPtr));
	handle = zipFileSystemIO->openASyncFile(zipInFiles[0], IO::READ);
	ASSERT_GE(handle, 0);
	ASSERT_NO_THROW(zipFileSystem->asyncReadFile(handle, buf, bufSize, readcallback));
	ASSERT_NO_THROW(zipFileSystem->asyncWait(handle));
	zipFileSystem->asyncClose(handle);

	free(buf);
	//EXPECT_EQ(schReleaseTaskSch(&sch), SCH_OK);
}

TEST_F(IOTest, Std) {
	char buf[] = {'h', 'e', 'l', 'l', 'o', '\n'};
	const unsigned int nBytes = sizeof(buf);

	/*  */
	ASSERT_EQ(stdoutIO->write(nBytes, buf), nBytes);
	EXPECT_NO_THROW(stdoutIO->write(nBytes, buf));
	EXPECT_NO_THROW(stdoutIO->flush());
	ASSERT_STREQ(stdoutIO->getName().c_str(), "stdout");
	ASSERT_FALSE(stdoutIO->isReadable());

	/*  */
	ASSERT_THROW(stdinIO->write(nBytes, buf), RuntimeException);
	ASSERT_STREQ(stdinIO->getName().c_str(), "stdin");
	ASSERT_TRUE(stdinIO->isReadable());

	/*  */
	ASSERT_EQ(stderrIO->write(nBytes, buf), nBytes);
	EXPECT_NO_THROW(stderrIO->write(nBytes, buf));
	EXPECT_NO_THROW(stderrIO->flush());
	ASSERT_STREQ(stderrIO->getName().c_str(), "stderr");

	/*  */
	EXPECT_NO_THROW(stdinIO->close());
	EXPECT_NO_THROW(stderrIO->close());
	EXPECT_NO_THROW(stdoutIO->close());
}

TEST_F(IOTest, Buffer) {
	const char *buffer = "hello world!";
	unsigned int bufLen = strlen(buffer);
	char buf[5];
	BufferIO *bIO;

	EXPECT_NO_THROW(bIO = new BufferIO(buffer, strlen(buffer)));
	EXPECT_EQ(bIO->length(), bufLen);
	EXPECT_EQ(bIO->getPos(), 0);
	EXPECT_TRUE(bIO->isReadable());
	EXPECT_FALSE(bIO->isWriteable());
	EXPECT_NO_THROW(bIO->read(5, buf));
	delete bIO;

	char buf2[512];
	bufLen = sizeof(buf2);
	EXPECT_NO_THROW(bIO = new BufferIO(buf2, bufLen));
	EXPECT_EQ(bIO->length(), bufLen);
	EXPECT_EQ(bIO->getPos(), 0);
	EXPECT_TRUE(bIO->isReadable());
	EXPECT_TRUE(bIO->isWriteable());
	delete bIO;
}

TEST_F(IOTest, IOFile) {
	char buf[512];
	long size;

	FileIO write = FileIO(FileWrite, IO::WRITE);
	ASSERT_FALSE(write.isReadable());
	ASSERT_TRUE(write.isWriteable());

	std::vector<char *>::const_iterator it = files.cbegin();
	for (; it != files.cend(); it++) {
		FileIO *fileIo;
		ASSERT_NO_THROW(fileIo = new FileIO((*it), IO::Mode::READ));
		ASSERT_TRUE(fileIo->isReadable());
		ASSERT_FALSE(fileIo->isWriteable());

		/*  */
		while ((size = fileIo->read(512, buf)) > 0) {
			EXPECT_EQ(stdoutIO->write(size, buf), size);
			EXPECT_EQ(write.write(size, buf), size);
		}
		delete fileIo;
	}

	write.flush();
	ASSERT_NO_THROW(write.close());
}

TEST_F(IOTest, IOGzFile) {
	char buf[512];
	long size;

	// Validate the argument.
	ASSERT_THROW(GZFileIO(NULL, IO::READ), std::invalid_argument);
	ASSERT_THROW(GZFileIO("", IO::READ), RuntimeException);
	ASSERT_THROW(GZFileIO("", (IO::Mode) 33213123), std::invalid_argument);

	GZFileIO write = GZFileIO(gzFileWrite, IO::WRITE);
	ASSERT_FALSE(write.isReadable());
	ASSERT_TRUE(write.isWriteable());

	std::vector<char *>::const_iterator it = gzFiles.cbegin();
	for (; it != gzFiles.cend(); it++) {
		GZFileIO *fileIo;
		ASSERT_NO_THROW(fileIo = new GZFileIO((*it), IO::Mode::READ));
		ASSERT_TRUE(fileIo->isReadable());
		ASSERT_FALSE(fileIo->isWriteable());

		while ((size = fileIo->read(512, buf)) > 0) {
			EXPECT_EQ(stdoutIO->write(size, buf), size);
			EXPECT_EQ(write.write(size, buf), size);
		}
		delete fileIo;
	}

	write.flush();
	ASSERT_NO_THROW(write.close());
}

TEST_F(IOTest, IOGZipFile) {
	ZipFile *zipFile;
	ASSERT_THROW(zipFile = ZipFile::createZipFileObject(""), std::invalid_argument);
	ASSERT_NO_THROW(zipFile = ZipFile::createZipFileObject(this->zipFile));

	//TODO add listing of files.
	std::vector<std::string> baseDir = zipFile->listDirectories("");
	std::vector<std::string>::const_iterator listIt = baseDir.cbegin();
	for (; listIt != baseDir.cend(); listIt++) {
		std::vector<std::string> files = zipFile->listFiles((*listIt).c_str());
		files.size();
	}

	//TODO check the references.
	ZipFileIO *zileFileIo = (ZipFileIO *) zipFile->openFile(zipInFiles[0], IO::READ);
	delete zipFile;
	zileFileIo->close();

	ASSERT_NO_THROW(zipFile = ZipFile::createZipFileObject(this->zipFile));
	ASSERT_THROW(zipFile->openFile("none-existing.txt", IO::READ), std::invalid_argument);

	/*  */
	std::vector<char *>::const_iterator it = zipInFiles.cbegin();
	for (; it != zipInFiles.cend(); it++) {
		char *path = (*it);

		ZipFileIO *zileFileIo = (ZipFileIO *) zipFile->openFile(path, IO::READ);
	}
}

