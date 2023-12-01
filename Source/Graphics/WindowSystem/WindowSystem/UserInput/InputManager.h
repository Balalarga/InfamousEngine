#pragma once
#include <vector>


namespace Inf::Window
{

class IInputHandler;

class InputManager
{
public:
	static InputManager& Instance();

	
private:
	std::vector<IInputHandler*> _handlers;
};
}
