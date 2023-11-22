#include "IWindow.h"

#include <iostream>

#include "Time/Time.h"

namespace Inf
{
IWindow::IWindow(WindowParams&& params) :
	_params(std::move(params))
{
	if (_params.fps > 0)
		_targetFrameTime = Milliseconds(1000 / _params.fps);
}

IWindow::~IWindow() = default;

void IWindow::Run()
{
	while (IsOpened())
	{
		_frameStart = _timeline.GetPassedTime();
		
		HandleEvents();
		Milliseconds handleEventTime = _timeline.GetPassedTime() - _frameStart;
		std::cout << "handleEventTime = " << handleEventTime << std::endl;

		Update(_lastFrameTime + handleEventTime);

		if (_params.fps > 0)
			DelayTime(_timeline.GetPassedTime() - _frameStart);
		
		_frameEnd = _timeline.GetPassedTime();
		_lastFrameTime = _frameEnd - _frameStart;
	}
	Close();
}

void IWindow::DelayTime(const Milliseconds& passed)
{
	if (_targetFrameTime > passed)
	{
		std::this_thread::sleep_for(_targetFrameTime - passed);
		std::cout << "Delayed for " << _targetFrameTime - passed << std::endl;
	}
}
} // namespace Inf
