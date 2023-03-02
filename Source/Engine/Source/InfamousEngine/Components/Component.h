#pragma once

namespace Inf
{
class IComponent
{
public:
	IComponent() = default;
	IComponent(IComponent&&) = default;
	IComponent(const IComponent&) = default;
	virtual ~IComponent() = default;

	IComponent& operator=(const IComponent&) = default;
	IComponent& operator=(IComponent&&) = default;

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Destroy() = 0;
};
}