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

	static std::shared_ptr<JsonResource> LoadFrom(const FileInfo& info);

private:
	rapidjson::Document _json;
};
}
