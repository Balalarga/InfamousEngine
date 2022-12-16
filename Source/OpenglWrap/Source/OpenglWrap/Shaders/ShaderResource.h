#pragma once

#include <map>
#include <memory>

#include "Shader.h"

#include "ResourceManager/Resources/IResource.h"

namespace Inf
{
class ShaderResource: public IResource
{
public:
	static std::shared_ptr<ShaderResource> ResourceHandler(const std::string& path);
	const static std::map<std::string, ShaderType> sShaderExtensions;

	ShaderResource(std::string resourcePath, ShaderType type, std::string code);

	Shader& operator*() { return _shader; }

private:
	Shader _shader;
};
}
