#pragma once
#include "Time/Time.h"

namespace Inf
{
class IWindowUpdateLoop
{
public:
	virtual ~IWindowUpdateLoop() = default;

	virtual void BeginLoop();
	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void EndLoop();

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
	
	Milliseconds GetFrameTime() const
	{
		return _lastFrameTime;
	}


private:
	Timeline _timeline;
	Milliseconds _frameStart{};
	Milliseconds _frameEnd{};
	Milliseconds _lastFrameTime{};
};


class SimpleWindowUpdateLoop: public IWindowUpdateLoop
{
public:
	void HandleEvents() override;
	void Update() override;
	void Render() override;

	void SetFrameLimit(unsigned frames = 0);

	
private:
	unsigned _frameLimit = 0;
	
	Milliseconds _targetFrameTime{0};
	bool bRender = true;
};
} // namespace Inf
