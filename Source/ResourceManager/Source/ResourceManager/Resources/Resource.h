#pragma once
#include <string>

namespace Inf
{
template<class T>
class Resource
{
public:
	Resource(std::string resourcePath, T res):
		_resourcePath(std::move(resourcePath)),
		_hash(ComputeHash(_resourcePath)),
		_resource(std::move(res))
	{
	}

	static size_t ComputeHash(const std::string& path)
	{
		return std::hash<std::string>{}(path);
	}

	size_t Hash() const { return _hash; }

	T& operator*() { return _resource; }
	T& Get() { return _resource; }

	const T& operator*() const { return _resource; }
	const T& Get() const { return _resource; }

private:
	const std::string _resourcePath;
	const size_t _hash;
	T _resource;
};
}