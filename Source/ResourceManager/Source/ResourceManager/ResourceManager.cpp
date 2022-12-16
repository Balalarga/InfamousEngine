#include "ResourceManager.h"

#include <utility>

#include "Resources/JsonResource.h"

namespace Inf
{
std::string ResourceManager::_baseDir = "Assets";
std::map<size_t, std::shared_ptr<IResource>> ResourceManager::_resources{};

size_t ResourceManager::GetHash(const std::string& filepath)
{
	return std::hash<std::string>{}(filepath);
}

void ResourceManager::SetResourceDir(std::string resourceDir)
{
	_baseDir = std::move(resourceDir);
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
