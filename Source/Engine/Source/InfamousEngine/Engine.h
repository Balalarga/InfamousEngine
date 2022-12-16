#pragma once
#include <cassert>
#include <memory>

#include "ResourceManager/ResourceManager.h"
#include "WindowSystem/GameWindow.h"

namespace Inf
{
class Engine
{
public:
	static Engine& Self();
	~Engine() = default;

	template<class T, class ...TArgs>
	std::enable_if_t<std::derived_from<T, GameWindow>, T*> CreateWindow(TArgs&& ...args)
	{
		assert(!_window);
		_window = std::make_unique<T>(std::forward<TArgs>(args)...);
		return _window.get();
	}

	template<class T, class ...TArgs>
	std::enable_if_t<std::derived_from<T, ResourceManager>, T*> CreateResourceManager(TArgs&& ...args)
	{
		assert(!_resourceManager);
		_resourceManager = std::make_unique<T>(std::forward<TArgs>(args)...);
		return _resourceManager.get();
	}
	static void SetResourceDir(const std::string& resourceDir);
	static const std::string& GetResourceDir();

	void Init();
	void Run();
	void Destroy();

	GameWindow& GetWindow() const;
	InputManager& GetInputManager() const;

	ResourceManager& GetResourceManager() const;

	void RequestClosing() const;

	void SetFramePerSecond(uint32_t fps);
	void SetUpdatePerSecond(uint32_t ups);


protected:
	Engine() = default;


private:
	static std::string sResourcesDir;

	std::unique_ptr<GameWindow> _window;
	std::unique_ptr<ResourceManager> _resourceManager;

	uint32_t _fps = 60u;
	uint32_t _ups = 30u;

	uint32_t _fpsMs = 1000u / _fps;
	uint32_t _upsMs = 1000u / _ups;

	uint32_t _frameTime = 0;
};
}
