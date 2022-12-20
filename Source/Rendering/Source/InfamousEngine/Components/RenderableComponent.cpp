#include "RenderableComponent.h"


namespace Inf
{
void RenderableComponent::SetShaderProgram(std::shared_ptr<ShaderProgramResource> program)
{
	_shaderProgram = std::move(program);
}

void RenderableComponent::SetBuffer(const Buffer& buffer)
{
	_buffer = buffer;
}

void RenderableComponent::Render()
{
	if (_shaderProgram && !_shaderProgram->Take()->)
}
}
