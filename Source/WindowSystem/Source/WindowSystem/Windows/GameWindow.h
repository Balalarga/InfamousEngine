#pragma once

#include <SDL.h>
#include <string>

#include "WindowSystem/Input/InputManager.h"
#include "IWindow.h"

namespace Inf
{
class GameWindow: public IWindow
{
public:
	struct Initializer
	{
		std::string Title = "UnknownGame";
		Uint32 Subsystems = SDL_INIT_EVERYTHING;
		SDL_Point Size = {1280, 720};
		SDL_Point Pos = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};
		bool IsFullScreen = false;
		SDL_WindowFlags Flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN);

		const char* imguiGlVersion = "#version 450";
	};

	GameWindow(const Initializer& initializer = {});
	virtual ~GameWindow();

	InputManager* GetInputManager() override;

	void Open() override;
	void Render() override;

	void HandleEvents() override;

	void Resize(unsigned x, unsigned y) override;
	glm::uvec2 GetSize() const override;

	uint32_t GetWindowId() const;


protected:
	Initializer _initializer;
	InputManager _inputManager;

	SDL_Window* _sdlWindow;
	SDL_GLContext _openglContext;
};
}
