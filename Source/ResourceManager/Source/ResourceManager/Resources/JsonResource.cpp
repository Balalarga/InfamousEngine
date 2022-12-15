#include "JsonResource.h"

#include "FileSystem/FileSystem.h"

#include "rapidjson/istreamwrapper.h"

namespace Inf
{
std::shared_ptr<JsonResource> JsonResource::ResourceHandler(const std::string& path)
{
	if (InputFileStream stream = FileSystem::ReadFile(path))
	{
		char buffer[65536];
		rapidjson::IStreamWrapper is(*stream, buffer, sizeof buffer);

		doc.Parse(data.value().c_str());

		return doc.IsObject() ? std::make_shared<JsonResource>(path, doc) : nullptr;
	}

	return nullptr;
}

JsonResource::JsonResource(std::string resourcePath, rapidjson::Document& json):
	IResource(std::move(resourcePath))
{
	_json.CopyFrom(json, json.GetAllocator());
}
}
