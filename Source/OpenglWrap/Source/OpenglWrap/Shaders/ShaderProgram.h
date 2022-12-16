#pragma once
#include <map>
#include <memory>
#include <string>

#include "Uniform.h"


namespace Inf
{
class Shader;

class ShaderProgram
{
public:
	ShaderProgram(std::shared_ptr<Shader> vShader,  std::shared_ptr<Shader> fShader, std::shared_ptr<Shader> gShader = nullptr);
	~ShaderProgram();

	bool Compile();
	void Destroy();

	void Bind() const;
	static void Release();

	void SetUniform(const std::string& name, const UniformValue& value, bool bUnbind = false);
	
protected:
	int GetUniformLocation(const std::string& name);

private:
	struct
	{
		std::shared_ptr<Shader> vShader;
		std::shared_ptr<Shader> fShader;
		std::shared_ptr<Shader> gShader;
	} _parts;

	unsigned _glHandler = 0;

	std::map<std::string, int> _uniformCache;
};
}