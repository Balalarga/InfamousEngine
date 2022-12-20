#pragma once
#include "ECS/Component.h"
#include "OpenglWrap/Buffers/Buffer.h"
#include "OpenglWrap/Shaders/Resources/ShaderProgramResource.h"

namespace Inf
{
class RenderableComponent: public Component
{
public:
	void SetShaderProgram(std::shared_ptr<ShaderProgramResource> program);
	std::shared_ptr<ShaderProgramResource> GetShaderProgram() const { return _shaderProgram; }

	void SetBuffer(const Buffer& buffer);
	const Buffer& GetBuffer() const { return _buffer; }

	void Render();

private:
	Buffer _buffer;
	std::shared_ptr<ShaderProgramResource> _shaderProgram;
};
}
