#include "Entity.h"

namespace Inf
{
Entity::~Entity()
{
	for (auto& [info, comp]: _components)
		comp->Detach();
}
}
