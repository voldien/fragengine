#include<gtest/gtest.h>
#include"Utils/TextureUtil.h"
using namespace fragcore;

TEST(FileNotification, Create){

}

TEST (Asset, Geometry) {

}

TEST (Asset, Shader) {

}

TEST (Asset, Texture) {
	unsigned int width, height;
	void* pixels;
	unsigned long size;

	/*	*/
	EXPECT_THROW(pixels = TextureUtil::loadTextureData("doNotExist.png", &width, &height, &size), std::invalid_argument);
	EXPECT_NO_THROW(pixels = TextureUtil::loadTextureData("../../fragview.png", &width, &height, &size));

	/*	*/
	ASSERT_EQ(width, 1024);
	ASSERT_EQ(height, 1024);
	ASSERT_NE(pixels, NULL);
	ASSERT_GE(size, 0);

	free(pixels);
}