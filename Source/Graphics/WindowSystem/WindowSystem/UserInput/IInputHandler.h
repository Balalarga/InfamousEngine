#pragma once


namespace Inf::Window
{
class IInputHandler
{
public:
	virtual ~IInputHandler() = default;
	
	
	
	virtual void InputActivate(float val) = 0;
	virtual void InputDeactivate(float val) = 0;
};
}
