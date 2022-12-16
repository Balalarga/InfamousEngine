#include "Engine.h"

#include "Logger/Logger.h"

#include "OpenglWrap/Shaders/ShaderResource.h"

#include "ResourceManager/Resources/JsonResource.h"

namespace Inf
{
std::string Engine::sResourcesDir = "Assets";

Engine& Engine::Self()
{
	static Engine sEngine;
	return sEngine;
}

void Engine::Init()
{
	Logger::Verbose("Engine initialization");

	if (!_window)
		_window = std::make_unique<GameWindow>();

	if (!_resourceManager)
		_resourceManager = std::make_unique<ResourceManager>(sResourcesDir);
	AddResourceHandlers();
}

void Engine::Run()
{
	assert(_window);

	uint32_t updateTimer = 0;

	Logger::Verbose("Start game loop");
	_window->Open();
	while (!_window->IsClosed())
	{
		const uint32_t frameBegin = SDL_GetTicks(); // TODO: Remove sdl-based code
		_window->GetInputManager().HandleEvent();

		if (updateTimer >= _upsMs)
		{
			// Update
            updateTimer -= _upsMs;
		}

		_window->Render();

		_frameTime = SDL_GetTicks() - frameBegin;
		if (_frameTime < _fpsMs)
		{
			SDL_Delay(_fpsMs - _frameTime);
			_frameTime = SDL_GetTicks() - frameBegin;
		}
		updateTimer += _frameTime;
	}

	Destroy();
}

void Engine::Destroy()
{
	Logger::Verbose("Engine destroying");
	_window.reset();
}

void Engine::SetResourceDir(const std::string& resourceDir)
{
	Logger::Verbose(fmt::format("Set resource dir {}", resourceDir));
	sResourcesDir = resourceDir;
}

const std::string& Engine::GetResourceDir()
{
	return sResourcesDir;
}

void Engine::AddResourceHandlers()
{
	_resourceManager->AddTypeHandler("json", &JsonResource::ResourceHandler);
	for (auto& [ext, type]: ShaderResource::sShaderExtensions)
		_resourceManager->AddTypeHandler(ext, &ShaderResource::ResourceHandler);
}

GameWindow& Engine::GetWindow() const
{
	assert(_window);
	return *_window;
}

InputManager& Engine::GetInputManager() const
{
	assert(_window);
	return _window->GetInputManager();
}

ResourceManager& Engine::GetResourceManager() const
{
	assert(_resourceManager);
	return *_resourceManager;
}

void Engine::RequestClosing() const
{
	if (_window && !_window->IsClosed())
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
