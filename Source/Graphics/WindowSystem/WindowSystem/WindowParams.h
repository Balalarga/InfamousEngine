#pragma once
#include <string>
#include "glm/vec2.hpp"


namespace Inf::Window
{
struct WindowParams
{
	std::string title = "InfamousEngine";
	glm::ivec2 size = {1280, 720};
	glm::ivec2 pos = {-1, -1};
	std::pair<short, short> openglVersion = {3, 0};
	short fps = 0;
};
}