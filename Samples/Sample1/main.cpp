#include <iostream>
#include "GlfwWindow/GlfwWindow.h"
#include "UserInput/InputManager.h"
#include "nlohmann/json.hpp"

using namespace Inf;


int main(int, char**)
{
	WindowParams params;
	params.fps = 60;

	const std::unique_ptr<GlfwWindow> window = std::make_unique<GlfwWindow>(params);

	KeyBindHandle handle(
		KeyboardButtons::W,
		[](float val, const std::set<KeyboardModifiers>& mods)
		{
			if (val > 0)
				std::cout << "Pressed\n";
			else
				std::cout << "Released\n";
		});

	window->Run();


	return 0;
}
