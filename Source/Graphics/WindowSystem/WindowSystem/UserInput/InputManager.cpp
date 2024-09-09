#include "InputManager.h"

#include <GLFW/glfw3.h>


namespace Inf
{
KeyBindHandle::~KeyBindHandle()
{
	InputManager::Instance().Unbind(button, handleId);
}

KeyBindHandle::KeyBindHandle(const KeyboardButtons& key, const OnKeyCallback& func) :
	handleId(InputManager::Instance().Bind(key, func)), button(key)
{
}

InputManager& InputManager::Instance()
{
	static InputManager self;
	return self;
}

InputManager::InputManager()
{
}

void InputManager::AttachToWindow(GLFWwindow* window)
{
	glfwSetKeyCallback(window,
					   [](GLFWwindow* window, int key, int scancode, int action, int mods)
					   { Instance().GlfwKeyCallback(window, key, scancode, action, mods); });
}

size_t InputManager::Bind(const KeyboardButtons& key, const OnKeyCallback& func)
{
	auto it = _keyboard.find(key);
	if (it == _keyboard.end())
	{
		it = _keyboard.emplace().first;
	}

	return it->second.emplace_back(it->second.size(), func).handleId;
}

void InputManager::Unbind(const KeyboardButtons& key, size_t handleId)
{
	const auto it = _keyboard.find(key);
	if (it == _keyboard.end())
	{
		return;
	}

	it->second.remove_if([&handleId](const FunctionDescriptor& item) { return item.handleId == handleId; });
}

void InputManager::GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_REPEAT)
	{
		return;
	}

	static auto GetModifiers = [](int modifiers)
	{
		std::set<KeyboardModifiers> modSet;
		if (modifiers & GLFW_MOD_ALT)
		{
			modSet.insert(KeyboardModifiers::Alt);
		}
		if (modifiers & GLFW_MOD_SHIFT)
		{
			modSet.insert(KeyboardModifiers::Shift);
		}
		if (modifiers & GLFW_MOD_SUPER)
		{
			modSet.insert(KeyboardModifiers::Super);
		}
		if (modifiers & GLFW_MOD_CONTROL)
		{
			modSet.insert(KeyboardModifiers::Control);
		}
		if (modifiers & GLFW_MOD_NUM_LOCK)
		{
			modSet.insert(KeyboardModifiers::NumLock);
		}
		if (modifiers & GLFW_MOD_CAPS_LOCK)
		{
			modSet.insert(KeyboardModifiers::CapsLock);
		}

		return modSet;
	};

	const std::set<KeyboardModifiers> modifiers = GetModifiers(mods);
	const float keyVal = action == GLFW_PRESS ? 1.f : -1.f;

	const auto it = _keyboard.find(static_cast<KeyboardButtons>(key));
	if (it == _keyboard.end())
	{
		return;
	}

	for (const auto& [idx, callback]: it->second)
	{
		callback(keyVal, modifiers);
	}
}
} // namespace Inf