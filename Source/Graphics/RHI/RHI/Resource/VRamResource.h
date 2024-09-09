#pragma once

#include <optional>


namespace Inf
{
class VRamResource
{
public:
	using THandle = int;

	VRamResource();
	virtual ~VRamResource();

	bool Build();
	// void Rebuild();
	void Destruct();

	virtual bool IsValid();

	const std::optional<THandle>& GetHandle() const;


protected:
	virtual void PreAllocate();
	virtual void PostAllocate();

	virtual std::optional<THandle> Allocate() = 0;
	virtual void Deallocate(const THandle& handle);


private:
	std::optional<THandle> _handle;
};
}