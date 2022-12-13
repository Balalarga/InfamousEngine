#include "Engine.h"

namespace Unk
{
Engine& Engine::Self()
{
	static Engine sEngine;
	return sEngine;
}

void Engine::Init()
{

}

void Engine::Run()
{
	Init();

	assert(_window);

	uint32_t updateTimer = 0;
	uint32_t frameTime = 0;
	while (!_window->IsClosing())
	{
		uint32_t frameBegin = SDL_GetTicks(); // TODO: Remove sdl-based code
		_window->GetInputManager().HandleEvent();

		if (updateTimer >= _upsMs)
		{
			// Update
            updateTimer -= _upsMs;
		}

		_window->Render();

		frameTime = SDL_GetTicks() - frameBegin;
		if (frameTime < _fpsMs)
		{
			SDL_Delay(_fpsMs - frameTime);
			frameTime = SDL_GetTicks() - frameBegin;
		}
		updateTimer += frameTime;
	}

	Destroy();
}

void Engine::Destroy()
{
	_window.reset();
}

InputManager& Engine::GetInputManager() const
{
	assert(_window);
	return _window->GetInputManager();
}

void Engine::RequestClosing() const
{
	if (_window && !_window->IsClosing())
		_window->Close();
}

void Engine::SetFramePerSecond(uint32_t fps)
{
	_fps = fps;
	if (_fps == 0u)
		_fpsMs = 0u;
	else
		_fpsMs = 1000u / _fps;
}

void Engine::SetUpdatePerSecond(uint32_t ups)
{
	_ups = ups;
	if (_ups == 0u)
		_upsMs = 0u;
	else
		_upsMs = 1000u / _ups;
}
}
