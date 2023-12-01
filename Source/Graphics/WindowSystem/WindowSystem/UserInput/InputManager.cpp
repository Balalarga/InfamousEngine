#include "InputManager.h"

namespace Inf::Window
{

InputManager& InputManager::Instance()
{
	static InputManager _gInstance;
	return _gInstance;
}

}
