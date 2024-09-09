#include "Shader.h"


namespace Inf
{

Shader::Shader(Type type, std::string code) : _code(std::move(code)), _type(type)
{
}

std::optional<VRamResource::THandle> Shader::Allocate()
{
	return glCreateShader(static_cast<std::underlying_type_t<Type>>(_type));
}

void Shader::Deallocate(const THandle& handler)
{
	glDeleteShader(handler);
}

bool Shader::HasError() const
{
	if (!GetHandle().has_value())
	{
		return true;
	}

	const THandle handlerValue = GetHandle().value();
	GLint isCompiled;
	glGetShaderiv(handlerValue, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength;
		glGetShaderiv(handlerValue, GL_INFO_LOG_LENGTH, &maxLength);

		// std::vector<GLchar> errorLog(maxLength);
		// glGetShaderInfoLog(GetHandler(), maxLength, &maxLength, errorLog.data());
		// std::cout << errorLog.data() << std::endl;
		// Process log
		return true;
	}
	return false;
}

Shader::Type Shader::GetType() const
{
	return _type;
}

}