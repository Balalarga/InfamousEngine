#pragma once
#include <string>
#include "glm/vec2.hpp"


struct WindowParams
{
	std::string title = "InfamousEngine Window";
	glm::uvec2 size = {800, 600};
	glm::uvec2 pos = {-1, -1};
	std::pair<short, short> openglVersion = {3, 0};
};
