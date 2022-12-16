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

std::shared_ptr<ShaderResource> ShaderResource::ResourceHandler(const std::string& path)
{
	const std::string type = FileSystem::GetFileExtension(path);
	const auto typeKV = sShaderExtensions.find(type);
	if (typeKV == sShaderExtensions.end())
		return nullptr;

	std::optional<std::string> code = FileSystem::ReadAllFile(path);
	if (!code.has_value())
		return nullptr;

	return std::make_shared<ShaderResource>(path, typeKV->second, code.value());
}

ShaderResource::ShaderResource(std::string resourcePath, ShaderType type, std::string code):
	IResource(std::move(resourcePath)),
	_shader(type, code)
{
}
}
