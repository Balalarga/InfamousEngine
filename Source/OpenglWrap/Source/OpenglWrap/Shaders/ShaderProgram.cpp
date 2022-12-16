#include "ShaderProgram.h"

#include <utility>
#include <vector>

#include <GL/glew.h>

#include "Shader.h"
#include "Logger/Logger.h"

namespace Inf
{
ShaderProgram::ShaderProgram(std::shared_ptr<Shader> vShader, std::shared_ptr<Shader> fShader, std::shared_ptr<Shader> gShader):
	_parts({std::move(vShader), std::move(fShader), std::move(gShader)})
{
}

ShaderProgram::~ShaderProgram()
{
	Destroy();
}

bool ShaderProgram::Compile()
{
	_glHandler = glCreateProgram();

	std::vector parts{_parts.vShader, _parts.fShader};
	if (_parts.gShader)
		parts.push_back(_parts.gShader);

	std::vector<unsigned> attachedShaders;
	for (const std::shared_ptr<Shader>& part : parts)
	{
		if (!part->IsCompiled() && !part->Compile())
			continue;

		attachedShaders.push_back(part->GetHandler());
		glAttachShader(_glHandler, part->GetHandler());
	}
	if (attachedShaders.size() == parts.size())
	{
		glLinkProgram(_glHandler);
		return true;
	}

	for (const unsigned& shader : attachedShaders)
		glDetachShader(_glHandler, shader);

	glDeleteProgram(_glHandler);
	_glHandler = 0;
	return false;
}

void ShaderProgram::Bind() const
{
	glUseProgram(_glHandler);
}

void ShaderProgram::Release()
{
	glUseProgram(0);
}

void ShaderProgram::SetUniform(const std::string& name, const UniformValue& value, bool bUnbind)
{
	Bind();
	int loc = GetUniformLocation(name);
	if (loc < 0)
		return;

	std::visit([&](auto&& arg)
		{
			using T = std::decay_t<decltype(arg)>;
			if constexpr (std::is_same_v<T, unsigned>)
				glUniform1ui(loc, arg);
			else if constexpr (std::is_same_v<T, int>)
				glUniform1i(loc, arg);
			else if constexpr (std::is_same_v<T, float>)
				glUniform1f(loc, arg);
			else if constexpr (std::is_same_v<T, glm::vec2>)
				glUniform2fv(loc, 1, &arg.x);
			else if constexpr (std::is_same_v<T, glm::vec3>)
				glUniform3fv(loc, 1, &arg.x);
			else if constexpr (std::is_same_v<T, glm::vec4>)
				glUniform4fv(loc, 1, &arg.x);
			else if constexpr (std::is_same_v<T, glm::mat2>)
				glUniformMatrix2fv(loc, 1, GL_FALSE, &arg[0][0]);
			else if constexpr (std::is_same_v<T, glm::mat3>)
				glUniformMatrix3fv(loc, 1, GL_FALSE, &arg[0][0]);
			else if constexpr (std::is_same_v<T, glm::mat4>)
				glUniformMatrix4fv(loc, 1, GL_FALSE, &arg[0][0]);
		},
		value);

	if (bUnbind)
		Release();
}

int ShaderProgram::GetUniformLocation(const std::string& name)
{
	if (!_glHandler)
		return -1;

	const auto it = _uniformCache.find(name);
	if (it != _uniformCache.end())
		return it->second;

	const int loc = glGetUniformLocation(_glHandler, name.c_str());
	if (loc >= 0)
		_uniformCache[name] = loc;

	return loc;
}

void ShaderProgram::Destroy()
{
	if (_glHandler)
	{
		Release();
		glDetachShader(_glHandler, _parts.vShader->GetHandler());
		glDetachShader(_glHandler, _parts.fShader->GetHandler());
		if (_parts.gShader)
			glDetachShader(_glHandler, _parts.gShader->GetHandler());

		glDeleteProgram(_glHandler);
		_glHandler = 0;
	}
}
}
