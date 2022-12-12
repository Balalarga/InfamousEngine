#pragma once

#include <SDL_video.h>

#include "glm/glm.hpp"

namespace Unk
{
class Opengl
{
public:
	Opengl() = delete;

	static inline void SetClearColor(const SDL_Color& color);
	static inline void SetClearColor(const glm::vec4& color);

	static inline void SetAttribute(SDL_GLattr name, int val);
};
}