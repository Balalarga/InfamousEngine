#pragma once
#include <memory>

#include "WindowSystem/GameWindow.h"

namespace Unk
{
class Engine
{
public:
	static Engine& Self();

	~Engine() = default;

	void Run();

	template<class T, class ...TArgs>
	std::enable_if_t<std::derived_from<T, GameWindow>, void> CreateWindow(TArgs&& ...args)
	{
		_window = std::make_unique<T>(std::forward<TArgs>(args)...);
	}

	void SetFramePerSecond(uint32_t fps);
	void SetUpdatePerSecond(uint32_t ups);

protected:
	Engine() = default;

	void Init();
	void Destroy();


private:
	std::unique_ptr<GameWindow> _window;

	uint32_t _fps = 60u;
	uint32_t _ups = 30u;

	uint32_t _fpsMs = 1000u / _fps;
	uint32_t _upsMs = 1000u / _ups;
};
}
