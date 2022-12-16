#pragma once
#include <string>

#include "ShaderType.h"

#include "ResourceManager/ResourceManager.h"

namespace Inf
{

class Shader
{
public:
	Shader(ShaderType type, std::string code);
	virtual ~Shader();
	
	bool IsCompiled() const { return _glHandler != 0; }
	
	bool Compile();
	void Destroy();
	
	const ShaderType& GetType() const { return _type; }
	const std::string& GetCode() const { return _code; }
	const unsigned& GetHandler() const { return _glHandler; }


protected:
	bool HasError() const;


private:
	const ShaderType _type;
	const std::string _code;
	
	unsigned _glHandler = 0;
};
}
