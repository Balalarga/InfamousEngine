#pragma once
#include <memory>
#include <string>

namespace Inf
{
class Entity;

class Component
{
public:
	Component(const std::string& name);
	virtual ~Component() = default;

	virtual void Attach(std::weak_ptr<Entity> owner);
	virtual void Detach();

	const std::string& GetName() const { return _name; }

	bool IsOwned() const;
	std::weak_ptr<Entity> GetOwner() const { return _owner; }


private:
	const std::string _name;

	std::weak_ptr<Entity> _owner;
};
}
