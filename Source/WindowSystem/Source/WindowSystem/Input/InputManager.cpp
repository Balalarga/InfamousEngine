#include "InputManager.h"

#include <imgui_impl_sdl.h>

#include "Windows/GameWindow.h"

namespace Inf
{
InputManager::InputManager(GameWindow& window):
	_window(window)
{
}

void InputManager::Add(SDL_Scancode code, const std::function<void(const KeyState&)>& callback)
{
	_keyCallbacks[code].push_back(callback);
}

bool InputManager::Remove(SDL_Scancode code, const std::function<void(const KeyState&)>& callback)
{
	// TODO
	// for (size_t i = 0; i < KeyCallbacks[code].size(); ++i)
	// {
	// if (KeyCallbacks[code][i].target<void(const KeyState&)>() == callback.target<void(const KeyState&)>())
	// {
	// KeyCallbacks[code].erase(KeyCallbacks[code].begin() + i);
	// return true;
	// }
	// }

	return false;
}

void InputManager::HandleEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		ImGui_ImplSDL2_ProcessEvent(&e);
		switch(e.type)
		{
			case SDL_QUIT:
			{
				_window.Close();
			}
			break;
			case SDL_WINDOWEVENT:
			{
				if (e.window.event == SDL_WINDOWEVENT_CLOSE && _window.GetWindowId() == e.window.windowID)
					_window.Close();
			}
			break;
			case SDL_KEYDOWN:
			{
				OnStateChange(e.key.keysym.scancode, e.key.repeat == 0 ? KeyState::Pressed : KeyState::Repeated);
			}
			break;
			case SDL_KEYUP:
			{
				OnStateChange(e.key.keysym.scancode, KeyState::Released);
			}
			break;
			default:
				break;
		}
	}
}

void InputManager::OnStateChange(SDL_Scancode code, KeyState state) const
{
	for (const std::function<void(const KeyState&)>& func : _keyCallbacks[code])
		func(state);
}
}
