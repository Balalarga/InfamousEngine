#include "DataPtr.h"

namespace Inf
{
DataPtr::DataPtr():
	Ptr(nullptr),
	Count(0),
	ItemSize(0)
{

}

DataPtr::DataPtr(void* ptr, int64_t count, int64_t itemSize):
	Ptr(ptr),
	Count(count),
	ItemSize(itemSize)
{

}
}