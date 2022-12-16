#pragma once

#include <map>
#include <memory>

#include "Shader.h"

#include "Logger/Logger.h"

#include "ResourceManager/Resources/IResource.h"

namespace Inf
{
class ShaderResource: public IResource
{
public:
	const static std::map<std::string, ShaderType> sShaderExtensions;

	ShaderResource(std::string resourcePath, ShaderType type, std::string code);

	Shader& operator*() { return _shader; }

private:
	Shader _shader;
};

template<>
inline std::shared_ptr<ShaderResource> ResourceHandler::LoadFrom(const std::string& path, const std::string& extension)
{
	const std::string type = FileSystem::GetFileExtension(path);
	const auto typeKV = ShaderResource::sShaderExtensions.find(type);
	if (typeKV == ShaderResource::sShaderExtensions.end())
		return nullptr;

	std::optional<std::string> code = FileSystem::ReadAllFile(path);
	if (!code.has_value())
		return nullptr;

	return std::make_shared<ShaderResource>(path, typeKV->second, code.value());
}
}
