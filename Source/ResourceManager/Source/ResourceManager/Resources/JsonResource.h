#pragma once
#include "IResource.h"
#include "rapidjson/document.h"

namespace Inf
{
class JsonResource: public IResource
{
public:
	static std::shared_ptr<JsonResource> ResourceHandler(const std::string& path);

	JsonResource(std::string resourcePath);

	rapidjson::Document& GetJson() { return _json; }

private:
	rapidjson::Document _json;
};
}
