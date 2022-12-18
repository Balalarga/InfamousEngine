#include "Component.h"

namespace Inf
{
Component::Component(const std::string& name)
{

}

void Component::Attach(std::weak_ptr<Entity> owner)
{
	_owner = std::move(owner);
}

void Component::Detach()
{
	_owner.reset();
}

bool Component::IsOwned() const
{
	return _owner.expired();
}
}
