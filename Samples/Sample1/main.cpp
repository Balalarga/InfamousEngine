#include <iostream>

#include "ISerializable.h"
#include "GlfwWindow/GlfwWindow.h"
#include "Resource/VRamBuffer.h"
#include "Stream/FileStream.h"
#include "Stream/IStream.h"

using namespace Inf;


int main(int, char**)
{
	Window::WindowParams params;
	params.fps = 60;
	
	const std::unique_ptr<Window::IWindow> window = std::make_unique<Window::GlfwWindow>(params);
	
	window->Run();
	
	return 0;
}
