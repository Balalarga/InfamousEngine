#include "Window.h"

#include <iostream>

namespace Inf
{
void Error(int error_code, const char* description)
{
	std::cout << "GLFW error(" << error_code << "): " << description << std::endl;
}

Window::Window(WindowParams&& params) : IWindow(std::move(params))
{
	if (!glfwInit())
	{
		return;
		// Initialization failed
	}

	glfwSetErrorCallback(&Error);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GetParams().openglVersion.first);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GetParams().openglVersion.second);
	_glfwWindow = glfwCreateWindow(GetParams().size.x, GetParams().size.y, "My Title", nullptr, nullptr);
	if (!_glfwWindow)
		return;
	
	glfwMakeContextCurrent(_glfwWindow);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
		return;
}

Window::~Window()
{
	glfwDestroyWindow(_glfwWindow);
	glfwTerminate();
}

bool Window::IsValid() const
{
	return !!_glfwWindow;
}

bool Window::IsOpened() const
{
	return !glfwWindowShouldClose(_glfwWindow);
}

void Window::Close(bool forced)
{
	glfwSetWindowShouldClose(_glfwWindow, true);
}

} // namespace Inf
