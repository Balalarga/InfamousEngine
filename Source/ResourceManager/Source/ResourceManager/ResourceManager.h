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
	ResourceManager() = default;
	ResourceManager(ResourceManager&&) = default;
	ResourceManager(const ResourceManager&) = default;
	virtual ~ResourceManager() = default;

	ResourceHandler* FindTypeHandler(const std::string& type);

	bool AddTypeHandler(const std::string& type, ResourceHandler&& func);
	bool AddTypeHandlers(const std::vector<std::string>& types, ResourceHandler&& handler);

	bool ResetTypeHandler(const std::string& type, ResourceHandler&& func);

	template<class T>
	std::shared_ptr<T> LoadResource(const std::string& filepath)
	{
		if (const ResourceHandler* handler = FindTypeHandler(FileSystem::GetFileExtension(filepath)))
		{
			if (std::shared_ptr<T> castedResource = std::dynamic_pointer_cast<T>(FindResource(filepath)))
				return castedResource;

			std::shared_ptr<T> resource = std::dynamic_pointer_cast<T>((*handler)(filepath));
			if (resource)
				_resources.insert(std::make_pair(resource->Hash(), resource));

			return resource;
		}

		return nullptr;
	}

	void LoadDefaultResources();

	std::shared_ptr<IResource> FindResource(const std::string& filepath);
	std::shared_ptr<IResource> FindResource(size_t hash);

protected:
	std::map<std::string, ResourceHandler> _resourceHandlers;
	std::map<size_t, std::shared_ptr<IResource>> _resources;
};
}

