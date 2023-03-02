#pragma once
#include <cassert>
#include <memory>

#include "WindowSystem/Windows/IWindow.h"

namespace Inf
{
class GameWindow;

class Engine
{
public:
	using DefaultWindowType = GameWindow;
	static Engine& Self();
	~Engine() = default;

	template<class T, class ...TArgs>
	std::enable_if_t<std::derived_from<T, IWindow>, T*> CreateWindow(TArgs&& ...args)
	{
		assert(!_window);
		_window = std::make_unique<T>(std::forward<TArgs>(args)...);
		return static_cast<T*>(_window.get());
	}

	void Init();
	void Run();
	void Destroy();

	IWindow& GetWindow() const;

	void RequestClosing() const;

	void SetFramePerSecond(uint32_t fps);
	void SetUpdatePerSecond(uint32_t ups);


protected:
	Engine() = default;


private:
	std::unique_ptr<IWindow> _window;

	uint32_t _fps = 60u;
	uint32_t _ups = 30u;

	uint32_t _fpsMs = 1000u / _fps;
	uint32_t _upsMs = 1000u / _ups;

	uint32_t _frameTime = 0;
};
}
