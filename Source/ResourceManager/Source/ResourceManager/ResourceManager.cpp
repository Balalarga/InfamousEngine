#include "ResourceManager.h"

#include "Resource.h"
#include "FileSystem/FileSystem.h"

namespace Inf
{
ResourceHandler* ResourceManager::FindTypeHandler(const std::string& type)
{
	const auto it = _resourceHandlers.find(type);
	if (it != _resourceHandlers.end())
		return &it->second;
	return nullptr;
}

bool ResourceManager::AddTypeHandler(const std::string& type, ResourceHandler&& func)
{
	if (FindTypeHandler(type))
		return false;

	_resourceHandlers.insert(std::make_pair(type, func));
	return true;
}

bool ResourceManager::AddTypeHandlers(const std::vector<std::string>& types, ResourceHandler&& handler)
{
	bool status = true;
	for (const std::string& type : types)
		status &= AddTypeHandler(type, std::forward<ResourceHandler>(handler));
	return status;
}

bool ResourceManager::ResetTypeHandler(const std::string& type, ResourceHandler&& func)
{
	if (ResourceHandler* handler = FindTypeHandler(type))
	{
		*handler = func;
		return true;
	}

	return false;
}

std::shared_ptr<Resource> ResourceManager::LoadResource(const std::string& filepath)
{
	if (const ResourceHandler* handler = FindTypeHandler(FileSystem::GetFileExtension(filepath)))
	{
		if (std::shared_ptr<Resource> foundedResource = FindResource(filepath))
			return foundedResource;

		std::shared_ptr<Resource> resource = (*handler)(filepath);
		if (resource)
			_resources.insert(std::make_pair(resource->Hash(), resource));

		return resource;
	}

	return nullptr;
}

std::shared_ptr<Resource> ResourceManager::FindResource(const std::string& filepath)
{
	return FindResource(Resource::ComputeHash(filepath));
}

std::shared_ptr<Resource> ResourceManager::FindResource(size_t hash)
{
	const auto it = _resources.find(hash);
	if (it != _resources.end())
		return it->second;

	return nullptr;
}
}
