#pragma once
#include <chrono>

#include "WindowParams.h"
#include "Time/Timeline.h"
#include "Time/Timer.h"

namespace Inf::Window
{
class IWindow
{
public:
	explicit IWindow(const WindowParams& params);
	virtual ~IWindow();

	virtual void Run();

	virtual void HandleEvents() = 0;
	virtual bool IsValid() const = 0;
	virtual void Update(const Microseconds& deltaTime) = 0;
	virtual bool IsOpened() const = 0;
	virtual void Open() = 0;
	virtual void Close(bool forced = false) = 0;

	const WindowParams& GetParams() const
	{
		return _params;
	}

	const Microseconds& GetFrameTime() const
	{
		return _lastFrameTime;
	}
	
	const Microseconds& GetTargetFrameTime() const
	{
		return _targetFrameTime;
	}


protected:
	virtual void DelayTime(const typename Timeline<>::BaseDuration& passed);


private:
	WindowParams _params;
	
	Timer<> _frameTimer;
	Timer<> _updateTimer;
	Microseconds _targetFrameTime{};
	Microseconds _lastFrameTime{};
};
} // namespace Inf
