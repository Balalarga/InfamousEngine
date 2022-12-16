#pragma once
#include <map>
#include <string>

#include "Resources/IResource.h"

#include "FileSystem/FileSystem.h"

namespace Inf
{
class ResourceManager
{
public:
	static size_t GetHash(const std::string& filepath);

	static void SetResourceDir(std::string resourceDir);

	template<class T>
	static std::enable_if_t<std::derived_from<T, IResource>, std::shared_ptr<T>>
	LoadResource(const std::string& filepath, bool bAbsoluteResource = false)
	{
		std::string path = bAbsoluteResource ? filepath : FileSystem::JoinPaths(_baseDir, filepath);
		std::shared_ptr<T> res = ResourceHandler::LoadFrom<T>(path, FileSystem::GetFileExtension(filepath));
		if (res)
			_resources.insert(std::make_pair(GetHash(filepath), res));
		return res;
	}

	static std::shared_ptr<IResource> FindResource(const std::string& filepath);
	static std::shared_ptr<IResource> FindResource(size_t hash);


protected:
	static std::string _baseDir;

	static std::map<size_t, std::shared_ptr<IResource>> _resources;
};
}

