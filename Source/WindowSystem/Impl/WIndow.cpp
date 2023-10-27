#include "Window.h"

namespace Inf
{

Window::Window(WindowParams&& params): IWindow(std::move(params))
{
	if (!glfwInit())
	{
		// Initialization failed
	}
	
	// glfwSetErrorCallback([](auto && PH1, auto && PH2)
	// {
		// OnError(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
	// });
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GetParams().openglVersion.first);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GetParams().openglVersion.second);
	_glfwWindow = glfwCreateWindow(GetParams().size.x, GetParams().size.y, "My Title", NULL, NULL);
	if (!_glfwWindow)
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
	
void Window::Run()
{
	glfwMakeContextCurrent(_glfwWindow);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
		return;
}

void Window::Close(bool forced)
{
	glfwSetWindowShouldClose(_glfwWindow, true);
}

}