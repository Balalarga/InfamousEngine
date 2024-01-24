#pragma once
#include <optional>


namespace Inf
{
class VRamResource
{
public:
	using THandler = int;
	
	VRamResource();
	virtual ~VRamResource();

	bool Build();
	// void Rebuild();
	void Destruct();

	virtual bool IsValid();
	
	const std::optional<THandler>& GetHandler() const;
	
	
protected:
	virtual void PreAllocate();
	virtual void PostAllocate();
	
	virtual std::optional<THandler> Allocate() = 0;
	virtual void Deallocate(const THandler& handler);

	
private:
	std::optional<THandler> _handler;
};
}
