#include "ResourceManager.h"


namespace Inf {
ResourceManager::ResourceManager() = default;

bool ResourceManager::MountPath(const std::filesystem::path& aliasPath, const std::filesystem::path& source) {
	return _mountedDirs.Add(std::vector(aliasPath.begin(), aliasPath.end()),
							std::filesystem::path(source).make_preferred());
}

const std::filesystem::path* ResourceManager::GetMountedPath(const std::filesystem::path& path) const {
	const std::filesystem::path* foundedPath = _mountedDirs.Find(std::vector(path.begin(), path.end()));
	return foundedPath && !foundedPath->empty() ? foundedPath : nullptr;
}

bool ResourceManager::IsPathMounted(const std::filesystem::path& path) const {
	auto foundedPath = GetMountedPath(path);
	return foundedPath != nullptr && foundedPath->empty();
}

std::filesystem::path ResourceManager::Get(const std::filesystem::path& path) const {
	std::vector<std::filesystem::path> pathVector(path.begin(), path.end());
	std::span pathSpan(pathVector);

	const std::filesystem::path* mountedPath = nullptr;
	while ((!mountedPath || mountedPath->empty()) && !pathSpan.empty()) {
		mountedPath = _mountedDirs.Find(pathSpan);
		pathSpan = pathSpan.subspan(0, pathSpan.size() - 1);
	}

	if (!mountedPath || mountedPath->empty()) {
		return path;
	}

	std::filesystem::path filePath(*mountedPath);
	for (int i = pathSpan.size() + 1; i < pathVector.size(); ++i) {
		filePath /= pathVector[i];
	}

	return filePath;
}
} // namespace Inf