#include "Opengl.h"

#include "GL/glew.h"

namespace Inf
{
inline void Opengl::SetClearColor(const SDL_Color& color)
{
	glClearColor(
		static_cast<float>(color.r) / 255.f,
		static_cast<float>(color.g) / 255.f,
		static_cast<float>(color.b) / 255.f,
		static_cast<float>(color.a) / 255.f
		);
}

inline void Opengl::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}
}
