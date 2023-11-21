#include "IWindowUpdateLoop.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace Inf
{
void IWindowUpdateLoop::BeginLoop()
{
	_timeline.Update();
	_frameStart = _timeline.GetPassedTime();
}

void IWindowUpdateLoop::EndLoop()
{
	_frameEnd = _timeline.GetPassedTime();
}

void SimpleWindowUpdateLoop::HandleEvents()
{
	glfwPollEvents();
}

void SimpleWindowUpdateLoop::Update()
{
	std::cout << "Frame time = " << GetLastFrameTime() << "ms" << std::endl;
}

void SimpleWindowUpdateLoop::Render()
{
	bRender = false;
}

void SimpleWindowUpdateLoop::EndLoop()
{
}

Milliseconds SimpleWindowUpdateLoop::GetLastFrameTime() const
{
	return std::chrono::duration_cast<Milliseconds>(_frameStart - _frameEnd);
}

void SimpleWindowUpdateLoop::SetFrameLimit(unsigned frames)
{
	_frameLimit = frames;
	if (frames > 0)
		_targetFrameTime = Milliseconds(static_cast<long long>(1'000'000 / frames));
	else
		_targetFrameTime = Milliseconds(0);
}
}