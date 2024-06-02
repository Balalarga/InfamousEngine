#pragma once

#include <filesystem>
#include "Containers/DenseTree.h"


namespace Inf {
class ResourceManager {
public:
	ResourceManager();

	bool MountPath(const std::filesystem::path& aliasPath, const std::filesystem::path& source);

	const std::filesystem::path* GetMountedPath(const std::filesystem::path& path) const;

	std::filesystem::path Get(const std::filesystem::path& path) const;

	bool IsPathMounted(const std::filesystem::path& path) const;


private:
	SparseTree<std::filesystem::path, std::filesystem::path> _mountedDirs;
};
} // namespace Inf
