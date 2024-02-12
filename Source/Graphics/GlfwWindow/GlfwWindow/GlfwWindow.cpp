#include "GlfwWindow.h"

#include <iostream>

#include "UserInput/InputManager.h"

namespace Inf
{
void Error(int error_code, const char* description)
{
	std::cout << "GLFW error(" << error_code << "): " << description << std::endl;
}

GlfwWindow::GlfwWindow(const WindowParams& params) :
	IWindow(params)
{
	if (!glfwInit())
	{
		return;
		// Initialization failed
	}

	glfwSetErrorCallback(&Error);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GetParams().openglVersion.first);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GetParams().openglVersion.second);
	_glfwWindow = glfwCreateWindow(
		GetParams().size.x,
		GetParams().size.y,
		GetParams().title.c_str(),
		nullptr,
		nullptr);
	if (!_glfwWindow)
		return;

	glfwMakeContextCurrent(_glfwWindow);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
		return;

	InputManager::AttachToWindow(_glfwWindow);
}

GlfwWindow::~GlfwWindow()
{
	glfwDestroyWindow(_glfwWindow);
	glfwTerminate();
}

void GlfwWindow::HandleEvents()
{
	glfwPollEvents();
}

bool GlfwWindow::IsValid() const
{
	return !!_glfwWindow;
}

void GlfwWindow::Update(const Microseconds& deltaTime)
{
}

bool GlfwWindow::IsOpened() const
{
	return !glfwWindowShouldClose(_glfwWindow);
}

void GlfwWindow::Open()
{
	glfwSetWindowShouldClose(_glfwWindow, false);
}

void GlfwWindow::Close(bool forced)
{
	glfwSetWindowShouldClose(_glfwWindow, true);
}

} // namespace Inf
