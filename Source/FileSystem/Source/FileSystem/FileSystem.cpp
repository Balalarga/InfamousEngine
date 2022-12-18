#include "FileSystem.h"
#include <filesystem>

namespace Inf
{
bool FileSystem::Exists(const std::string& path)
{
	return std::filesystem::exists(path);
}

bool FileSystem::IsFile(const std::string& path)
{
	return std::filesystem::is_regular_file(path);
}

bool FileSystem::IsDir(const std::string& path)
{
	return std::filesystem::is_directory(path);
}

bool FileSystem::CreateFile(const std::string& path, bool bCreateSubDirectories)
{
	return WriteFile(path, true, bCreateSubDirectories);
}

bool FileSystem::CreateDirectory(const std::string& path, bool bRecursive)
{
	std::filesystem::path nativePath(path);
	if (!is_directory(nativePath) && !nativePath.has_parent_path())
		return false;

	if (bRecursive)
		return create_directories(is_directory(nativePath) ? nativePath : nativePath.parent_path());

	return create_directory(is_directory(nativePath) ? nativePath : nativePath.parent_path());
}

InputFileStream FileSystem::ReadFile(const std::string& path, bool autoClose)
{
	if (Exists(path))
		return InputFileStream(path, autoClose);
	
	return {};
}

InputFileStream FileSystem::ReadFile(const std::string& path, FileStreamDataMode mode, bool autoClose)
{
	if (Exists(path))
		return InputFileStream(path, mode, autoClose);

	return {};
}

std::optional<std::string> FileSystem::ReadAllFile(const std::string& path)
{
	InputFileStream stream(path);
	if (stream)
		return stream.ReadRemaining();

	return {};
}

OutputFileStream FileSystem::WriteFile(const std::string& path, bool autoClose, bool bCreateSubDirectories)
{
	std::filesystem::path filepath(path);
	if (bCreateSubDirectories && filepath.has_parent_path())
		create_directories(filepath.parent_path());

	return OutputFileStream(path, autoClose);
}

OutputFileStream FileSystem::WriteFile(const std::string& path, FileStreamDataMode mode, bool autoClose, bool bCreateSubDirectories)
{
	std::filesystem::path filepath(path);
	if (bCreateSubDirectories && filepath.has_parent_path())
		create_directories(filepath.parent_path());

	return OutputFileStream(path, mode, autoClose);
}

std::string FileSystem::GetFileExtension(const std::string& path)
{
	const std::filesystem::path filepath(path);
	std::string fullExtension = filepath.extension().generic_string();

	// Remove dot from extension beginning
	return fullExtension.empty() ? fullExtension : fullExtension.substr(1);
}

std::string FileSystem::GetFileName(const std::string& path)
{
	return std::filesystem::path(path).filename().generic_string();
}

std::string FileSystem::JoinPaths(const std::string& p1, const std::string& p2)
{
	return (std::filesystem::path(p1)/std::filesystem::path(p2)).generic_string();
}

std::string FileSystem::JoinPaths(const std::vector<std::string> paths)
{
	if (paths.empty())
		return "";

	std::filesystem::path resPath(paths[0]);
	for (const std::string& path : paths)
		resPath /= path;
	return resPath.generic_string();
}
}
