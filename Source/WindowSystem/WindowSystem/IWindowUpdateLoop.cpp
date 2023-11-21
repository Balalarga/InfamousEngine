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
	_lastFrameTime = _frameStart - _frameEnd;
}

void SimpleWindowUpdateLoop::HandleEvents()
{
	glfwPollEvents();
}

void SimpleWindowUpdateLoop::Update()
{
	std::cout << "Frame time = " << GetFrameTime() << "ms" << std::endl;
}

void SimpleWindowUpdateLoop::Render()
{
	bRender = false;
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