#include "ResourceManager.h"

#include "Resources/JsonResource.h"

namespace Inf
{
ResourceManager::ResourceManager(const std::string& resourceDir):
	_baseDir(resourceDir)
{

}

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

std::shared_ptr<IResource> ResourceManager::FindResource(const std::string& filepath)
{
	return FindResource(IResource::ComputeHash(filepath));
}

std::shared_ptr<IResource> ResourceManager::FindResource(size_t hash)
{
	const auto it = _resources.find(hash);
	if (it != _resources.end())
		return it->second;

	return nullptr;
}
}
