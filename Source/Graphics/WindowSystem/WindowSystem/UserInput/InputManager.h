#pragma once
#include <array>
#include <functional>
#include <map>


namespace Inf::Window
{
class IInputManager
{
public:
	virtual ~IInputManager() = default;
	void OnKeyPressed();
	void OnKeyReleased();
	
	
};
}
