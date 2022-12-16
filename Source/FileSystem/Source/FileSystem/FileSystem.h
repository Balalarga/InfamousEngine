#pragma once
#include <optional>
#include <string>
#include <vector>

#include "FileStream/InputFileStream.h"
#include "FileStream/OutputFileStream.h"

namespace Inf
{
class FileSystem
{
public:
	static bool Exists(const std::string& path);
	static bool IsFile(const std::string& path);
	static bool IsDir(const std::string& path);

	static bool CreateFile(const std::string& path, bool bCreateSubDirectories = true);
	static bool CreateDirectory(const std::string& path, bool bRecursive = true);

	static InputFileStream ReadFile(const std::string& path, bool autoClose = true);
	static InputFileStream ReadFile(const std::string& path, FileStreamDataMode mode, bool autoClose = true);
	static std::optional<std::string> ReadAllFile(const std::string& path);
	
	static OutputFileStream WriteFile(const std::string& path, bool autoClose = true, bool bCreateSubDirectories = true);
	static OutputFileStream WriteFile(const std::string& path, FileStreamDataMode mode, bool autoClose = true, bool bCreateSubDirectories = true);

	static std::string GetFileExtension(const std::string& path);

	static std::string JoinPaths(const std::string&  p1, const std::string&  p2);
	static std::string JoinPaths(const std::vector<std::string> paths);
};
}