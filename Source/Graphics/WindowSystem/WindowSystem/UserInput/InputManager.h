#pragma once
#include <functional>
#include <map>
#include <set>

#include "Keys.h"


struct GLFWwindow;


namespace Inf::Window
{
class InputManager
{
public:
	using FunctionHandle = size_t;
	using KeyCallback = std::function<void(float, const std::set<KeyboardModifiers>&)>;

	static InputManager& Instance();

	InputManager();
	virtual ~InputManager() = default;

	void AttachToWindow(GLFWwindow* window);

	FunctionHandle Bind(const KeyboardButtons& key, const KeyCallback& func);
	void Unbind(FunctionHandle handle);


protected:
	void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


private:
	std::vector<std::vector<KeyCallback>> _keyboard;
};
}
