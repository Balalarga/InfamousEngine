#pragma once
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
}