#include "InputManager.h"

#include <GLFW/glfw3.h>


namespace Inf::Window
{
InputManager& InputManager::Instance()
{
	static InputManager self;
	return self;
}

InputManager::InputManager()
{
	_keyboard.resize(static_cast<int>(KeyboardButtons::TOTAL_NUMBER));
}

void InputManager::AttachToWindow(GLFWwindow* window)
{
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Instance().GlfwKeyCallback(window, key, scancode, action, mods);
	}); 
}

InputManager::FunctionHandle InputManager::Bind(const KeyboardButtons& key, const KeyCallback& func)
{
	auto& keyFuncs = _keyboard[static_cast<int>(key)];
	keyFuncs.emplace_back(func);
	return keyFuncs.size();
}

void InputManager::Unbind(FunctionHandle handle)
{
	
}

void InputManager::GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static auto GetModifiers = [](int modifiers)
	{
		std::set<KeyboardModifiers> modSet;
		if (modifiers & GLFW_MOD_ALT)
			modSet.insert(KeyboardModifiers::Alt);
		if (modifiers & GLFW_MOD_SHIFT)
			modSet.insert(KeyboardModifiers::Shift);
		if (modifiers & GLFW_MOD_SUPER)
			modSet.insert(KeyboardModifiers::Super);
		if (modifiers & GLFW_MOD_CONTROL)
			modSet.insert(KeyboardModifiers::Control);
		if (modifiers & GLFW_MOD_NUM_LOCK)
			modSet.insert(KeyboardModifiers::NumLock);
		if (modifiers & GLFW_MOD_CAPS_LOCK)
			modSet.insert(KeyboardModifiers::CapsLock);
		
		return modSet;
	};
	
	if (action == GLFW_REPEAT)
		return;
	
	for (const KeyCallback& function : _keyboard[key])
		function(action == GLFW_PRESS ? -1.f : 1.f, GetModifiers(mods));
}
}
