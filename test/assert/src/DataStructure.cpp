#include<gtest/gtest.h>
#include"Utils/TextureUtil.h"
#include"Core/dataStructure/PoolAllocator.h"
#include<Core/dataStructure/StackAllactor.h>
#include<Core/dataStructure/DoubleBufferedAllocator.h>
using namespace fragcore;

TEST (DataStructure, PoolAllocator) {
	PoolAllocator<int> allocator(32);
	std::vector<int*> pointers;

	const int s = allocator.reserved();
	for(int i = 0; i < s; i++){
		int* p = allocator.obtain();
		pointers.push_back(p);
	}

	for(int i = 0; i < pointers.size(); i++){
		allocator.Return(pointers[i]);
	}

	allocator.resize(allocator.reserved() * 2 );

}

TEST(DataStructure, StackAllocator){
	const int s_size = 128;
	StackAllocator stackAllocator(s_size);
	/*	Test initial state.	*/
	GTEST_ASSERT_EQ(stackAllocator.getSize(), s_size);
	GTEST_ASSERT_EQ(stackAllocator.getMarker(), 0);

	/*	*/
	void *p = stackAllocator.allocateAligned(84, 8);
	GTEST_ASSERT_NE(p, NULL);
	GTEST_ASSERT_EQ(stackAllocator.getMarker(), 0);
	GTEST_ASSERT_EQ(stackAllocator.getSize(), 88);

	/*	*/
	stackAllocator.freeToMarker(64);
	GTEST_ASSERT_EQ(stackAllocator.getMarker(), 64);

	DoubleBufferedAllocator dobuleStackAllocator;
}
