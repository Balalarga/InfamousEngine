#pragma once

#include <functional>
#include <SDL.h>

namespace Inf
{
class GameWindow;

enum class KeyState
{
	Pressed, Released, Repeated
};

class InputManager
{
	friend class AppWindow;
public:
	InputManager(GameWindow& window);

	void Add(SDL_Scancode code, const std::function<void(const KeyState&)>& callback);
	bool Remove(SDL_Scancode code, const std::function<void(const KeyState&)>& callback);

	void HandleEvent();

protected:
	void OnStateChange(SDL_Scancode code, KeyState state) const;

private:
	GameWindow& _window;
	std::vector<std::function<void(const KeyState&)>> _keyCallbacks[SDL_NUM_SCANCODES];
};
}