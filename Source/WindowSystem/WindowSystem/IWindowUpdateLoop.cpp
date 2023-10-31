#include "IWindowUpdateLoop.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace Inf
{
void SimpleWindowUpdateLoop::BeginLoop(std::chrono::microseconds time)
{
	if (bRender)
		_frameStart = time;
}

void SimpleWindowUpdateLoop::HandleEvents()
{
	glfwPollEvents();
}

void SimpleWindowUpdateLoop::Update()
{
	std::cout << "Frame time = " << GetLastFrameTime().count()/1000.f << "ms" << std::endl;
}

void SimpleWindowUpdateLoop::Render()
{
	bRender = false;
}

void SimpleWindowUpdateLoop::EndLoop(std::chrono::microseconds time)
{
	_frameEnd = time;
	if (_targetFrameTime.count() != 0 && _targetFrameTime.count() - GetLastFrameTime().count() <= 0)
		bRender = true;
}

std::chrono::milliseconds SimpleWindowUpdateLoop::GetLastFrameTime() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(_frameEnd - _frameStart);
}

void SimpleWindowUpdateLoop::SetFrameLimit(unsigned frames)
{
	_frameLimit = frames;
	if (frames > 0)
		_targetFrameTime = std::chrono::milliseconds(static_cast<long long>(1'000'000 / frames));
	else
		_targetFrameTime = std::chrono::milliseconds(0);
}
}