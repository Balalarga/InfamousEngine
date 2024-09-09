#pragma once

#include <functional>
#include <map>
#include <set>

#include "Keys.h"


struct GLFWwindow;


namespace Inf
{
using OnKeyCallback = std::function<void(float, const std::set<KeyboardModifiers>&)>;


class KeyBindHandle final
{
public:
	const size_t handleId;
	const KeyboardButtons button;


	KeyBindHandle(const KeyboardButtons& key, const OnKeyCallback& func);
	KeyBindHandle& operator=(const KeyBindHandle&) = delete;
	KeyBindHandle(const KeyBindHandle&) = delete;

	~KeyBindHandle();
};


class InputManager
{
	friend class KeyBindHandle;


	struct FunctionDescriptor
	{
		size_t handleId;
		OnKeyCallback callback;
	};


public:
	static InputManager& Instance();
	static void AttachToWindow(GLFWwindow* window);


	InputManager();
	virtual ~InputManager() = default;


protected:
	size_t Bind(const KeyboardButtons& key, const OnKeyCallback& func);
	void Unbind(const KeyboardButtons& key, size_t handleId);


private:
	void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


	std::map<KeyboardButtons, std::list<FunctionDescriptor>> _keyboard;
};
}