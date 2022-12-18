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
		if (std::shared_ptr<T> founded = FindResource<T>(filepath))
			return founded;

		IResource::FileInfo info;
		info.path = bAbsoluteResource ? filepath : FileSystem::JoinPaths(_baseDir, filepath);
		info.name = FileSystem::GetFileName(filepath);
		info.extension = FileSystem::GetFileExtension(filepath);

		std::shared_ptr<T> res = T::LoadFrom(info);
		if (res)
			_resources.insert(std::make_pair(GetHash(filepath), res));
		return res;
	}

	template<class T>
	void SaveResource(std::shared_ptr<IResource>)
	{
		// TODO
	}

	static std::shared_ptr<IResource> FindResource(const std::string& filepath);
	template<class T>
	static std::shared_ptr<T> FindResource(const std::string& filepath)
	{
		return std::dynamic_pointer_cast<T>(FindResource(filepath));
	}

	static std::shared_ptr<IResource> FindResource(size_t hash);
	template<class T>
	static std::shared_ptr<T> FindResource(size_t hash)
	{
		return std::dynamic_pointer_cast<T>(FindResource(hash));
	}

protected:
	static std::string _baseDir;

	static std::map<size_t, std::shared_ptr<IResource>> _resources;
};
}

