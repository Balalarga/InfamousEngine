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

	void HandleEvents() override;
	bool IsValid() const override;
	void Update(const Milliseconds& deltaTime) override;
	bool IsOpened() const override;
	void Open() override;
	void Close(bool forced) override;

	

private:
	GLFWwindow* _glfwWindow = nullptr;
};
} // namespace Inf
