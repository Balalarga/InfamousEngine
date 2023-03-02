#pragma once
#include "OpenglWrap/Buffers/Buffer.h"
#include "InfamousEngine/Components/Component.h"
#include "OpenglWrap/Shaders/Resources/ShaderProgramResource.h"

namespace Inf
{
class RenderComponent: public IComponent
{
public:
	RenderComponent();
	RenderComponent(Buffer buffer, std::shared_ptr<ShaderProgram> program);

	void SetShaderProgram(std::shared_ptr<ShaderProgram> program);
	std::shared_ptr<ShaderProgram> GetShaderProgram() const { return _shaderProgram; }

	void SetBuffer(const Buffer& buffer);
	const Buffer& GetBuffer() const { return _buffer; }

	virtual void Render();

	void Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;

private:
	Buffer _buffer;
	std::shared_ptr<ShaderProgram> _shaderProgram;
};
}
