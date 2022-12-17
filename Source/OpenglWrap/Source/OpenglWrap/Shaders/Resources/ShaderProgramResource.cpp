#include "ShaderProgramResource.h"

#include <utility>

namespace Inf
{
ShaderProgramResource::ShaderProgramResource(std::string resourcePath, const std::string& text):
	JsonResource(std::move(resourcePath), text)
{
}
}
