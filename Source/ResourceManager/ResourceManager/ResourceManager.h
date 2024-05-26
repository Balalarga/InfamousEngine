#pragma once
#include <filesystem>
#include <unordered_map>


namespace Inf
{

class ResourceManager
{
public:
	ResourceManager();
	
	bool AddMountedPath(const std::filesystem::path& Name, const std::filesystem::path& Source);
	std::filesystem::path GetMountedPath(std::filesystem::path Path) const;

	const std::filesystem::path* FindMountedDir(const std::filesystem::path& Path) const;
	

private:
	std::unordered_map<std::filesystem::path, std::filesystem::path> _mountedDirs;
};

} // namespace Inf