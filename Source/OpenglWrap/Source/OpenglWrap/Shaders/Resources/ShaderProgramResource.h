#pragma once
#include "ResourceManager/Resources/JsonResource.h"

namespace Inf
{
class ShaderProgram;

class ShaderProgramResource: public JsonResource
{
public:
	ShaderProgramResource(std::string resourcePath, const std::string& text);

	const std::shared_ptr<ShaderProgram>& Take() const { return _program; }

private:
	std::shared_ptr<ShaderProgram> _program;
};
}