#include "ResourceManager.h"


namespace Inf
{

ResourceManager::ResourceManager()
{
}

bool ResourceManager::AddMountedPath(const std::filesystem::path& Name, const std::filesystem::path& Source)
{
	auto it = _mountedDirs.try_emplace(Name, Source);
	if (!it.second)
		return false;

	return true;
}

std::filesystem::path ResourceManager::GetMountedPath(std::filesystem::path Path) const
{
	Path.
	while (Path.has_parent_path())
	{
		if (auto MountedPath = FindMountedDir(Path))
		{
			return MountedPath;
			
		}
		
	}
	
	return {};
}

const std::filesystem::path* ResourceManager::FindMountedDir(const std::filesystem::path& Path) const
{
	auto it = _mountedDirs.find(Path);
	if(it == _mountedDirs.end())
		return nullptr;
	
	return &it->second;
}

} // namespace Inf
