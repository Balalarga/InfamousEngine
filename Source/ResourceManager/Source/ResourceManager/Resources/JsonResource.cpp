#include "JsonResource.h"

#include "FileSystem/FileSystem.h"

#include "rapidjson/istreamwrapper.h"

namespace Inf
{
std::shared_ptr<JsonResource> JsonResource::ResourceHandler(const std::string& path)
{
	std::optional<std::string> data = FileSystem::ReadAllFile(path);
	if (data.has_value())
	{
		auto json = std::make_shared<JsonResource>(path);

		json->_json.Parse(data.value().c_str());
		if (json->_json.IsObject())
			return json;
		return nullptr;
	}

	return nullptr;
}

JsonResource::JsonResource(std::string resourcePath):
	IResource(std::move(resourcePath))
{
}
}
