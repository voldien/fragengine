#include<gtest/gtest.h>
#include<Scene/Layer.h>
using namespace fragcore;
using namespace fragengine;

TEST(Layer, Layer_Default_Constructor){
	Layer layer;
	ASSERT_EQ(layer.getIndex(), 0);
}

TEST(Layer, Layer_Add_Layer){
	Layer::setIndextName(0, "");
}

TEST(Layer, Layer_Remove_Layer)
{
	Layer::setIndextName(0, "");
}