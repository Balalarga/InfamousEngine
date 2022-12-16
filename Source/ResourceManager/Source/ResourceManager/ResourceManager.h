#pragma once
#include <functional>
#include <map>
#include <string>

#include "Resources/IResource.h"

#include "FileSystem/FileSystem.h"


namespace Inf
{
using ResourceHandler = std::function<std::shared_ptr<IResource>(const std::string&)>;

class ResourceManager
{
public:
	ResourceManager(const std::string& resourceDir);
	ResourceManager(ResourceManager&&) = default;
	ResourceManager(const ResourceManager&) = default;
	virtual ~ResourceManager() = default;

	ResourceHandler* FindTypeHandler(const std::string& type);

	bool AddTypeHandler(const std::string& type, ResourceHandler&& func);
	bool AddTypeHandlers(const std::vector<std::string>& types, ResourceHandler&& handler);

	bool ResetTypeHandler(const std::string& type, ResourceHandler&& func);

	template<class T>
	std::enable_if_t<std::derived_from<T, IResource>, std::shared_ptr<T>>
	LoadResource(const std::string& filepath, bool bAbsoluteResource = false)
	{
		if (const ResourceHandler* handler = FindTypeHandler(FileSystem::GetFileExtension(filepath)))
		{
			const std::shared_ptr<T> castedResource = std::dynamic_pointer_cast<T>(FindResource(filepath));
			if (castedResource)
				return castedResource;

			const std::string path = bAbsoluteResource ? filepath : FileSystem::JoinPaths(_baseDir, filepath);
			std::shared_ptr<IResource> resource = (*handler)(path);
			if (!resource)
				return nullptr;

			const std::shared_ptr<T> requestedResource = std::dynamic_pointer_cast<T>(resource);
			if (requestedResource)
				_resources.insert(std::make_pair(resource->Hash(), resource));

			return requestedResource;
		}

		return nullptr;
	}

	void LoadDefaultResources();

	std::shared_ptr<IResource> FindResource(const std::string& filepath);
	std::shared_ptr<IResource> FindResource(size_t hash);

protected:
	const std::string _baseDir;

	std::map<std::string, ResourceHandler> _resourceHandlers;
	std::map<size_t, std::shared_ptr<IResource>> _resources;
};
}

