#include "ShaderProgram.h"


namespace Inf
{
ShaderProgram::ShaderProgram() = default;


bool ShaderProgram::AttachShader(const std::shared_ptr<Shader>& newShader)
{
	if (IsValid())
	{
		return false;
	}

	const bool shaderExists = _shaders.end() == std::ranges::find_if(_shaders,
							 [&newShader](const std::shared_ptr<Shader>& shader)
							 { return shader->GetType() == newShader->GetType(); });

	if (!shaderExists)
	{
		_shaders.emplace_back(newShader);
	}

	return true;
}

void ShaderProgram::PostAllocate()
{
	const THandle handler = GetHandle().value();
	for (const std::shared_ptr<Shader>& shader: _shaders)
	{
		if (shader && shader->Build())
			glAttachShader(handler, shader->GetHandle().value());
	}

	glLinkProgram(handler);
}

std::optional<VRamResource::THandle> ShaderProgram::Allocate()
{
	return glCreateProgram();
}

void ShaderProgram::Deallocate(const THandle& handler)
{
	for (const std::shared_ptr<Shader>& shader: _shaders)
	{
		if (shader && shader->IsValid())
			glDetachShader(handler, shader->GetHandle().value());
	}
	glDeleteProgram(handler);
	_shaders.clear();
}

void ShaderProgram::Bind()
{
	glUseProgram(GetHandle().value());
}

void ShaderProgram::ReleaseImpl()
{
	glUseProgram(0);
}
}