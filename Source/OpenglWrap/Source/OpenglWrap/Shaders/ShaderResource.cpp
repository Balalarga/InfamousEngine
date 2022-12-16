#include "ShaderResource.h"

#include <utility>

#include "FileSystem/FileSystem.h"

namespace Inf
{
const std::map<std::string, ShaderType> ShaderResource::sShaderExtensions =
{
	{"vsh", ShaderType::Vertex},
	{"fsh", ShaderType::Fragment},
	{"gsh", ShaderType::Geometry},
	{"csh", ShaderType::Compute},
};

ShaderResource::ShaderResource(std::string resourcePath, ShaderType type, std::string code):
	IResource(std::move(resourcePath)),
	_shader(type, code)
{
}
}
