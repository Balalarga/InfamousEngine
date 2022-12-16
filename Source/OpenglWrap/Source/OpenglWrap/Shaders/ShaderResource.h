#pragma once

#include <map>
#include <memory>

#include "ResourceManager/Resources/IResource.h"
#include "ShaderType.h"

namespace Inf
{
class ShaderResource: public IResource
{
public:
	static std::shared_ptr<ShaderResource> ResourceHandler(const std::string& path);
	const static std::map<std::string, ShaderType> sShaderExtensions;

	ShaderResource(std::string resourcePath);
};
}
