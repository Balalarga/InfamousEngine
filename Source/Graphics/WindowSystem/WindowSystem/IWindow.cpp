#include "IWindow.h"

#include "Time/Time.h"
#if WIN32
#include <Windows.h>
#include <timeapi.h>
#endif

namespace Inf
{
IWindow::IWindow(const WindowParams& params) :
	_params(params),
	_frameTimer(false),
	_updateTimer(false)
{
	if (_params.fps > 0)
		_targetFrameTime = Microseconds(1'000'000 / _params.fps);
}

IWindow::~IWindow() = default;

void IWindow::Run()
{
	_frameTimer.Reset();
	_updateTimer.Reset();
	while (IsOpened())
	{
		_frameTimer.Reset();
		
		HandleEvents();
		
		Update(_updateTimer.Reset<Microseconds>());
		
		if (_params.fps > 0)
		{
			DelayTime(_frameTimer.GetPassedTime());
		}
		
		_lastFrameTime = _frameTimer.Reset<Microseconds>();
	}
	Close();
}

void IWindow::DelayTime(const Timeline<>::BaseDuration& passed)
{
#if WIN32
	// TODO: Make it for app lifetime???
	timeBeginPeriod(1);
#endif
	auto sleepTime = _targetFrameTime - passed;
	if (_targetFrameTime > passed)
	{
		// Millisecond is the lowest time, so try to minimize the fault
		if (std::chrono::duration_cast<Milliseconds>(sleepTime) < std::chrono::duration_cast<Milliseconds>(_targetFrameTime) + Milliseconds{1})
			sleepTime -= Microseconds{1500};
		std::this_thread::sleep_for(sleepTime);
	}
#if WIN32
	timeEndPeriod(1);
#endif
}
} // namespace Inf
