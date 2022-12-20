#include "MeshComponent.h"

namespace Inf
{
MeshComponent::MeshComponent(const std::string& name, const std::vector<glm::vec3>& vertices):
	Component(name),
	_vertices(vertices)
{

}
}