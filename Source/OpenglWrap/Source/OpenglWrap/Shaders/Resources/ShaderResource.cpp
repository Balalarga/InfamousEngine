#include "ShaderResource.h"

#include <utility>

#include "FileSystem/FileSystem.h"
#include "Shaders/Shader.h"

namespace Inf
{
const std::map<std::string, ShaderType> ShaderResource::sShaderExtensions =
{
	{"vsh", ShaderType::Vertex},
	{"fsh", ShaderType::Fragment},
	{"gsh", ShaderType::Geometry},
	{"csh", ShaderType::Compute},
};

std::shared_ptr<ShaderResource> ShaderResource::LoadFrom(const FileInfo& info)
{
	const std::string type = FileSystem::GetFileExtension(info.path);
	const auto typeKV = sShaderExtensions.find(type);
	if (typeKV == sShaderExtensions.end())
		return nullptr;

	std::optional<std::string> code = FileSystem::ReadAllFile(info.path);
	if (!code.has_value())
		return nullptr;

	return std::make_shared<ShaderResource>(info.path, typeKV->second, code.value());
}

ShaderResource::ShaderResource(std::string resourcePath, ShaderType type, std::string code):
	IResource(std::move(resourcePath)),
	_shader(std::make_shared<Shader>(type, code))
{
}
}
