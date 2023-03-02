#include "RenderManager.h"

#include "Components/RenderComponent.h"

namespace Inf
{
RenderManager& RenderManager::Self()
{
	static RenderManager self;
	return self;
}

void RenderManager::Add(RenderComponent* component)
{
	if (component)
		_components.emplace(component);
}

void RenderManager::Render()
{
	for (RenderComponent* comp : _components)
		comp->Render();
}
}
