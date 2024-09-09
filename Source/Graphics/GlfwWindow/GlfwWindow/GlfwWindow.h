#pragma once

#include "gl/glew.h"

#include "GLFW/glfw3.h"
#include "IWindow.h"


namespace Inf
{
class GlfwWindow: public IWindow
{
public:
	explicit GlfwWindow(const WindowParams& params = WindowParams());
	virtual ~GlfwWindow();

	void HandleEvents() override;
	void Update(const Microseconds& deltaTime) override;
	bool IsOpened() const override;
	void Open() override;
	void Close(bool forced) override;


private:
	GLFWwindow* _glfwWindow = nullptr;
};
} // namespace Inf
