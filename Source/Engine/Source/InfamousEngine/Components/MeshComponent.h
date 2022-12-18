#pragma once

#include "ECS/Component.h"

namespace Inf
{
class MeshComponent: public Component
{
public:
	MeshComponent(const std::string& name);
};
}
