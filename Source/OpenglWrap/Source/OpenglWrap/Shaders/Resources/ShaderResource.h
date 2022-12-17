#pragma once

#include <map>
#include <memory>

#include "Logger/Logger.h"

#include "ResourceManager/Resources/IResource.h"

namespace Inf
{
enum class ShaderType : uint32_t;
class Shader;

class ShaderResource: public IResource
{
public:
	const static std::map<std::string, ShaderType> sShaderExtensions;
	static std::shared_ptr<ShaderResource> LoadFrom(const FileInfo& info);

	ShaderResource(std::string resourcePath, ShaderType type, std::string code);

	const std::shared_ptr<Shader>& Take() const { return _shader; }


private:
	std::shared_ptr<Shader> _shader;
};
}
