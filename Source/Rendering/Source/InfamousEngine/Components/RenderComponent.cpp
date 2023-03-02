#include "RenderComponent.h"

#include "InfamousEngine/RenderManager.h"

#include "OpenglWrap/Opengl.h"

namespace Inf
{
RenderComponent::RenderComponent()
{
	RenderManager::Self().Add(this);
}

RenderComponent::RenderComponent(Buffer buffer, std::shared_ptr<ShaderProgram> program):
	_buffer(std::move(buffer)),
	_shaderProgram(std::move(program))
{
	RenderManager::Self().Add(this);
}

void RenderComponent::SetShaderProgram(std::shared_ptr<ShaderProgram> program)
{
	_shaderProgram = std::move(program);
}

void RenderComponent::SetBuffer(const Buffer& buffer)
{
	_buffer = buffer;
}

void RenderComponent::Render()
{
	if (_shaderProgram)
		_shaderProgram->Bind();

	Opengl::DrawBuffer(_buffer);
}

void RenderComponent::Init() {}
void RenderComponent::Update(float deltaTime) {}
void RenderComponent::Destroy() {}
}
