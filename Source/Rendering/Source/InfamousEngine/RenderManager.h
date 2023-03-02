#pragma once
#include <set>

namespace Inf
{
class RenderComponent;

class RenderManager
{
public:
	static RenderManager& Self();

	void Add(RenderComponent* component);

	void Render();

private:
	RenderManager() = default;

	std::set<RenderComponent*> _components;
};
}
