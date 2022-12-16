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
}
