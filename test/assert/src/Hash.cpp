#include"Core/IO/GZFileIO.h"
#include<Core/IO/ZipFile.h>
#include<Core/IO/FileIO.h>
#include<Core/IO/ZipFileIO.h>
#include<Core/IO/FileSystem.h>
#include <Core/IO/BufferIO.h>
#include <Core/Display.h>
#include<gtest/gtest.h>
#include <SDL2/SDL.h>
#include<Core/RefPtr.h>
#include<FragCore.h>
#include <Core/Hash.h>

using namespace fragcore;


TEST(Hash, Hash){
	Hash hash(Hash::ALGORITHM::MD5);
	const char *data = "Hello World!";
	EXPECT_NO_THROW (hash.update(data, sizeof(data)));
	ASSERT_EQ(hash.getByteRead(), sizeof(data));
	std::vector<unsigned char> md5;
	EXPECT_NO_THROW(hash.final(md5));
	//TODO add assertion that the value is correct.

	ASSERT_ANY_THROW(Hash badhashType((Hash::ALGORITHM)100));

}


