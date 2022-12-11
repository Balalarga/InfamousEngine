#include "FileSystem.h"
#include <filesystem>

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
