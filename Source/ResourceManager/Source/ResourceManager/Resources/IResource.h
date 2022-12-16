#pragma once
#include <cassert>
#include <memory>
#include <string>

namespace Inf
{
class IResource
{
public:
	IResource(std::string resourcePath);
	virtual ~IResource() = default;

	static size_t ComputeHash(const std::string& path);

	size_t Hash() const { return _hash; }

private:
	const std::string _resourcePath;
	const size_t _hash;
};

namespace ResourceHandler
{
template<class T>
std::shared_ptr<T> LoadFrom(const std::string& path, const std::string& extension)
{
	assert(false);
	return nullptr;
}
}
}