#pragma once

#include <vector>
#include <glm/vec3.hpp>

#include "InfamousEngine/Components/RenderableComponent.h"

namespace Inf
{
class MeshComponent: public RenderableComponent
{
public:
	MeshComponent(const std::string& name, const std::vector<glm::vec3>& vertices);

private:
	std::vector<glm::vec3> _vertices;
};
}
