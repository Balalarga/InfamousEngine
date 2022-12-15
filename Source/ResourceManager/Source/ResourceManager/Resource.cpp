#include "Resource.h"

namespace Inf
{
Resource::Resource(std::string resourcePath):
	_resourcePath(std::move(resourcePath)),
	_hash(ComputeHash(_resourcePath))
{
}

size_t Resource::ComputeHash(const std::string& path)
{
	return std::hash<std::string>{}(path);
}
}
