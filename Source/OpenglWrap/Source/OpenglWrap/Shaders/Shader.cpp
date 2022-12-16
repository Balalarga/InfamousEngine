#include "Shader.h"

#include <vector>
#include <GL/glew.h>

#include "Logger/Logger.h"

namespace Inf
{
Shader::Shader(ShaderType type, std::string code):
	_type(type),
	_code(std::move(code))
{
}

Shader::~Shader()
{
	Destroy();
}

bool Shader::Compile()
{
	if (_glHandler)
		return true;
	
	if (_code.empty())
		return false;

	const char* rawSource = _code.c_str();
	_glHandler = glCreateShader(static_cast<int>(_type));
	
	glShaderSource(_glHandler, 1, &rawSource, nullptr);
	glCompileShader(_glHandler);

	if (HasError())
	{
		Destroy();
		return false;
	}
	
	return true;
}

void Shader::Destroy()
{
	if (_glHandler)
	{
		glDeleteShader(_glHandler);
		_glHandler = 0;
	}
}

bool Shader::HasError() const
{
	if (!_glHandler)
		return false;

	GLint isCompiled;
	glGetShaderiv(_glHandler, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLchar errorLog[2048];
		GLint maxLength;
		glGetShaderiv(_glHandler, GL_INFO_LOG_LENGTH, &maxLength);
		glGetShaderInfoLog(_glHandler, maxLength, &maxLength, &errorLog[0]);
		Logger::Error(fmt::format("{}", errorLog));
		return true;
	}
	return false;
}
}
