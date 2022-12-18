#pragma once
#include <vector>

namespace Inf
{
struct DataPtr
{
	DataPtr();
	DataPtr(void* ptr, int64_t count, int64_t itemSize);

	template<class T>
	DataPtr(const std::vector<T>& items):
		DataPtr((void*)&items[0], items.size(), sizeof(T))
	{}

	template<class T>
	DataPtr(const std::initializer_list<T>& items):
		DataPtr((void*)&items[0], items.size(), sizeof(T))
	{}

	void* Ptr;
	int64_t Count;
	int64_t ItemSize;
};

}
