#pragma once

#include <SDL.h>
#include "glm/glm.hpp"

namespace Inf
{
class Opengl
{
public:
	Opengl() = delete;

	static inline void SetClearColor(const SDL_Color& color);
	static inline void SetClearColor(const glm::vec4& color);

	static void SetAttribute(SDL_GLattr name, int val) { SDL_GL_SetAttribute(name, val); }
};
}