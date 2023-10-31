#pragma once
#include "gl/glew.h"

#include "GLFW/glfw3.h"
#include "IWindow.h"


namespace Inf
{
class Window: public IWindow
{
public:
	Window(WindowParams&& params = WindowParams());
	virtual ~Window();

	bool IsValid() const override;
	bool IsOpened() const override;
	void Close(bool forced) override;
	std::chrono::microseconds GetSystemTime() const override;


private:
	GLFWwindow* _glfwWindow = nullptr;
};
} // namespace Inf
