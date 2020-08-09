#include"Core/Ref.h"
#include"Core/Object.h"
#include<gtest/gtest.h>
#include<Renderer/Texture.h>
using namespace fragcore;

TEST(References, SmartReference){

	SmartReference smartReference;

	ASSERT_TRUE(smartReference.increment());
	ASSERT_EQ(smartReference.getIndexCount(), 2);
	ASSERT_EQ(smartReference.deincreemnt(), false);
	ASSERT_TRUE(smartReference.deincreemnt());
	ASSERT_EQ(smartReference.getIndexCount(), 1);
	ASSERT_FALSE(smartReference.deincreemnt());
	ASSERT_EQ(smartReference.getIndexCount(), 0);
}

TEST (References, RefCounter) {

//	Ref<Object> ref;

	/*  */
//	ASSERT_EQ(ref.ptr(), NULL);
//	ASSERT_EQ(ref.operator->(), NULL);
//	Shader* = new Object();
//	Ref<Object> ref(obj);

//	ASSERT_EQ(ref.ptr(), obj);
//	ASSERT_EQ(ref->)
}