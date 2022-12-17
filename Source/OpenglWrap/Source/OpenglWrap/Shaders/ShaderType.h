#pragma once

#include <GL/glew.h>

namespace Inf
{
enum class ShaderType: uint32_t
{
	Vertex = GL_VERTEX_SHADER,
	Fragment = GL_FRAGMENT_SHADER,
	Geometry = GL_GEOMETRY_SHADER,
	Compute = GL_COMPUTE_SHADER
};
}
