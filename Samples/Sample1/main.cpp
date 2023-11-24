#include "GlfwWindow/GlfwWindow.h"

using namespace Inf;

int main(int, char**)
{
	WindowParams params;
	params.fps = 60;
	
	const std::unique_ptr<IWindow> window = std::make_unique<GlfwWindow>(params);
	
	window->Run();
	
	return 0;
}
