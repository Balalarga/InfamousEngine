#pragma once
#include <string>
#include "glm/vec2.hpp"


struct WindowParams
{
	std::string title;
	glm::uvec2 size;
	glm::uvec2 pos = {-1, -1};
};
