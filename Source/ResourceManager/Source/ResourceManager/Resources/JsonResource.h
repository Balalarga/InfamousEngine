#pragma once
#include "IResource.h"

#include "FileSystem/FileSystem.h"

#include "rapidjson/document.h"

namespace Inf
{
class JsonResource: public IResource
{
public:
	JsonResource(std::string resourcePath, const std::string& text);

	rapidjson::Document& GetJson() { return _json; }

private:
	rapidjson::Document _json;
};

template<>
inline std::shared_ptr<JsonResource> ResourceHandler::LoadFrom(const std::string& path, const std::string& extension)
{
	std::optional<std::string> data = FileSystem::ReadAllFile(path);
	if (data.has_value())
	{
		auto json = std::make_shared<JsonResource>(path, data.value());
		if (!json->GetJson().IsObject())
			return nullptr;
		return json;
	}

	return nullptr;
}
}
