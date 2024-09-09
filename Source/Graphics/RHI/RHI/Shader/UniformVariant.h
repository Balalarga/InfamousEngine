#pragma once

#include <variant>
#include <glm/glm.hpp>


using UniformValue = std::variant<unsigned,
								  int,
								  float,
								  double,
								  glm::ivec2,
								  glm::ivec3,
								  glm::ivec4,
								  glm::vec2,
								  glm::vec3,
								  glm::vec4,
								  glm::mat2,
								  glm::mat3,
								  glm::mat4>;