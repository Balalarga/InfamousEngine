#pragma once
#include "ResourceManager/Resources/JsonResource.h"
#include "OpenglWrap/Shaders/ShaderProgram.h"

namespace Inf
{
class ShaderProgramResource: public JsonResource
{
public:
	ShaderProgramResource(std::string resourcePath, const std::string& text);

	static std::shared_ptr<ShaderProgramResource> LoadFrom(const FileInfo& info);

	const std::shared_ptr<ShaderProgram>& Take() const { return _program; }
	const std::string& GetName() const { return _name; }


private:
	std::string _name;
	std::shared_ptr<ShaderProgram> _program;
};
}
