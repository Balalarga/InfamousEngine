#pragma once


namespace Inf
{
class VRamResource
{
public:
	using THandler = int;
	
	VRamResource();
	virtual ~VRamResource();

	bool Build();
	virtual bool IsValid();

	
protected:
	virtual void PreAllocate();
	virtual void PostAllocate();
	
	virtual THandler Allocate() = 0;
	virtual void Deallocate();

	
private:
	THandler _handler = 0;
};
}
