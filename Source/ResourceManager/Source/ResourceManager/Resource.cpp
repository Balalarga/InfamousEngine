#include "Resource.h"

Resource::Resource(std::string resourcePath):
	_resourcePath(std::move(resourcePath)),
	_hash(std::hash<std::string>{}(_resourcePath))
{
}
