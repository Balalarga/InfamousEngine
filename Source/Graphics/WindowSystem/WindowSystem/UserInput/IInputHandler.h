#pragma once


namespace Inf::Window
{
class IInputHandler
{
public:
	virtual ~IInputHandler() = default;

	
	virtual void OnActivate(float val) = 0;
	virtual void OnDeactivate(float val) = 0;
};
}
