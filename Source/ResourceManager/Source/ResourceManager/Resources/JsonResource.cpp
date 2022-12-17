#include "JsonResource.h"

#include "FileSystem/FileSystem.h"

#include "rapidjson/istreamwrapper.h"

namespace Inf
{
JsonResource::JsonResource(std::string resourcePath, const std::string& text):
	IResource(std::move(resourcePath))
{
	_json.Parse(text.c_str());
}

std::shared_ptr<JsonResource> JsonResource::LoadFrom(const FileInfo& info)
{
	std::optional<std::string> data = FileSystem::ReadAllFile(info.path);
	if (data.has_value())
	{
		auto json = std::make_shared<JsonResource>(info.path, data.value());
		if (!json->GetJson().IsObject())
			return nullptr;
		return json;
	}

	return nullptr;
}
}
