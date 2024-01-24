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
	
	_handler = Allocate();
	if (!_handler)
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

void VRamResource::Deallocate(const THandler& handler)
{
}

bool VRamResource::IsValid()
{
	return _handler.has_value();
}

void VRamResource::Destruct()
{
	if (!IsValid())
		return;

	Deallocate(_handler.value());
	_handler.reset();
}

const std::optional<VRamResource::THandler>& VRamResource::GetHandler() const
{
	return _handler;
}
}
