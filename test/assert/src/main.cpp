#include<gtest/gtest.h>
#include <Core/Config.h>
#include <RendererFactory.h>

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}