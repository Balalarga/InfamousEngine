#include "IResource.h"

namespace Inf
{
IResource::IResource(std::string resourcePath):
	_resourcePath(std::move(resourcePath)),
	_hash(ComputeHash(_resourcePath))
{
}

size_t IResource::ComputeHash(const std::string& path)
{
	return std::hash<std::string>{}(path);
}
}
