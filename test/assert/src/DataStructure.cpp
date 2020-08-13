#include<gtest/gtest.h>
#include"Utils/TextureUtil.h"
#include"Core/dataStructure/PoolAllocator.h"
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

