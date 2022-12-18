#pragma once
#include <cassert>
#include <memory>
#include <string>

namespace Inf
{
class IResource
{
public:
	struct FileInfo
	{
		std::string path;
		std::string name;
		std::string extension;
	};

	IResource(std::string resourcePath);
	virtual ~IResource() = default;

	static size_t ComputeHash(const std::string& path);

	size_t Hash() const { return _hash; }

	static std::shared_ptr<IResource> LoadFrom(const FileInfo& info)
	{
		assert(false);
		return nullptr;
	}

private:
	const std::string _resourcePath;
	const size_t _hash;
};
}