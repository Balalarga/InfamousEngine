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

void Window::HandleEvents()
{
	glfwPollEvents();
}

bool Window::IsValid() const
{
	return !!_glfwWindow;
}

void Window::Update(const Milliseconds& deltaTime)
{
	std::cout << "Frame update " << deltaTime << std::endl;
}

bool Window::IsOpened() const
{
	return !glfwWindowShouldClose(_glfwWindow);
}

void Window::Open()
{
	glfwSetWindowShouldClose(_glfwWindow, false);
}

void Window::Close(bool forced)
{
	glfwSetWindowShouldClose(_glfwWindow, true);
}

} // namespace Inf
