#pragma once

#include <SDL.h>
#include <string>

#include "Input/InputManager.h"

namespace Unk
{
class GameWindow
{
public:
	struct Initializer
	{
		std::string Title = "UnknownGame";
		Uint32 Subsystems = SDL_INIT_EVERYTHING;
		SDL_Point Size = {1280, 720};
		SDL_Point Pos = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};
		bool IsFullScreen = false;
		SDL_WindowFlags Flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	};

	GameWindow(const Initializer& initializer = {});
	virtual ~GameWindow();

	InputManager& GetInputManager() { return _inputManager; }

	bool IsClosing() const { return _bIsClosing; }
	void Close() { _bIsClosing = true; }

	virtual void Render();

	uint32_t GetWindowId() const;


protected:
	Initializer _initializer;
	InputManager _inputManager;

	SDL_Window* _sdlWindow;
	SDL_GLContext _openglContext;


	bool _bIsClosing = false;
};
}
