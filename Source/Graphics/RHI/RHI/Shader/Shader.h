#pragma once
#include <string>
#include <gl/glew.h>

#include "Resource/VRamResource.h"


namespace Inf
{
class Shader: public VRamResource
{
public:
	enum class Type : uint32_t
	{
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		Geometry = GL_GEOMETRY_SHADER
	};

	Shader(Type type, std::string  code);

	Type GetType() const;

	bool HasError() const;


protected:
	std::optional<THandle> Allocate() override;
	void Deallocate(const THandle& handler) override;


private:
	std::string _code;
	Type _type;
};
}