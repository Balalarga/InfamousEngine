#pragma once
#include <chrono>

#include "WindowParams.h"
#include "Time/Timeline.h"

namespace Inf
{
class IWindow
{
public:
	explicit IWindow(WindowParams&& params);
	virtual ~IWindow();

	virtual void Run();

	virtual void HandleEvents() = 0;
	virtual bool IsValid() const = 0;
	virtual void Update(const Milliseconds& deltaTime) = 0;
	virtual bool IsOpened() const = 0;
	virtual void Open() = 0;
	virtual void Close(bool forced = false) = 0;

	const WindowParams& GetParams() const
	{
		return _params;
	}

	const Timeline& GetTimeline() const
	{
		return _timeline;
	}

	const Milliseconds& GetFrameStart() const
	{
		return _frameStart;
	}

	const Milliseconds& GetFrameEnd() const
	{
		return _frameEnd;
	}

	const Milliseconds& GetFrameTime() const
	{
		return _lastFrameTime;
	}
	
	const Milliseconds& GetTargetFrameTime() const
	{
		return _targetFrameTime;
	}


protected:
	virtual void DelayTime(const Milliseconds& passed);


private:
	WindowParams _params;

	Timeline _timeline;
	Milliseconds _targetFrameTime{};
	Milliseconds _frameStart{};
	Milliseconds _frameEnd{};
	Milliseconds _lastFrameTime{};
};
} // namespace Inf
