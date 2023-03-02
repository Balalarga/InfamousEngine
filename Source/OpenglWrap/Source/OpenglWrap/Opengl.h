#pragma once

#include <SDL_video.h>

#include "glm/glm.hpp"

namespace Inf
{
struct Buffer;

class Opengl
{
public:
	Opengl() = delete;

	static void SetClearColor(const SDL_Color& color);
	static void SetClearColor(const glm::vec4& color);

	static void SetAttribute(SDL_GLattr name, int val);

	static void DrawBuffer(const Buffer& buffer);
};
}