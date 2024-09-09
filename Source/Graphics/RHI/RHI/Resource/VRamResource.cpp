#include "VRamResource.h"


namespace Inf
{
VRamResource::VRamResource() = default;

VRamResource::~VRamResource()
{
	Destruct();
}

bool VRamResource::Build()
{
	PreAllocate();

	_handle = Allocate();
	if (!_handle)
	{
		Destruct();
		return false;
	}

	PostAllocate();

	return true;
}

void VRamResource::PreAllocate()
{
}

void VRamResource::PostAllocate()
{
}

void VRamResource::Deallocate(const THandle& handle)
{
}

bool VRamResource::IsValid()
{
	return _handle.has_value();
}

void VRamResource::Destruct()
{
	if (IsValid() && _handle.has_value())
	{
		Deallocate(_handle.value());
		_handle.reset();
	}
}

const std::optional<VRamResource::THandle>& VRamResource::GetHandle() const
{
	return _handle;
}
}