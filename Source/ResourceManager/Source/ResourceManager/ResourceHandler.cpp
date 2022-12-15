#include "ResourceHandler.h"

#include "Resource.h"
#include "FileSystem/FileSystem.h"
#include "Logger/Logger.h"

namespace Inf
{
std::shared_ptr<Resource> DefaultResourceHandlers::HandleJson(const std::string& path)
{
	if (InputFileStream stream = FileSystem::ReadFile(path))
	{
		Logger::Log(fmt::format("Process json {}", path));
		return std::make_shared<Resource>(path);
	}

	return nullptr;
}
}
