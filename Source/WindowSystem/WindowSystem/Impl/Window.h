#pragma once
#include "gl/glew.h"

#include "GLFW/glfw3.h"
#include "IWindow.h"


namespace Inf
{
class Window: public IWindow
{
public:
	explicit Window(WindowParams&& params = WindowParams());
	~Window() override;

	bool IsValid() const override;
	bool IsOpened() const override;
	void Close(bool forced) override;


private:
	GLFWwindow* _glfwWindow = nullptr;
};
} // namespace Inf
