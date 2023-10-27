#pragma once
#include "IWindow.h"
#include "gl/glew.h"
#include "GLFW/glfw3.h"


namespace Inf
{

class Window: public IWindow
{
public:
	Window(WindowParams&& params);
	~Window();

	bool IsValid() const override;
	void Run() override;
	void Close(bool forced) override;

private:
	struct GLFWwindow*_glfwWindow = nullptr;
};

}