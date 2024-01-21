#include "VRamResource.h"


namespace Inf
{
VRamResource::VRamResource() = default;
VRamResource::~VRamResource() = default;

bool VRamResource::Build()
{
	PreAllocate();
	
	_handler = Allocate();
	if (!IsValid())
	{
		Deallocate();
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

void VRamResource::Deallocate()
{
	_handler = 0;
}

bool VRamResource::IsValid()
{
	return _handler != 0;
}
}
