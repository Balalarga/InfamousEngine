#pragma once

#include <chrono>

namespace Inf
{
class IWindowUpdateLoop
{
public:
	virtual ~IWindowUpdateLoop() = default;

	virtual void BeginLoop(std::chrono::microseconds time) = 0;
	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void EndLoop(std::chrono::microseconds time) = 0;
};

class SimpleWindowUpdateLoop: public IWindowUpdateLoop
{
public:
	void BeginLoop(std::chrono::microseconds time) override;
	void HandleEvents() override;
	void Update() override;
	void Render() override;
	void EndLoop(std::chrono::microseconds time) override;

	std::chrono::milliseconds GetLastFrameTime() const;

	void SetFrameLimit(unsigned frames = 0);

	
private:
	unsigned _frameLimit = 0;
	
	std::chrono::microseconds _targetFrameTime{0};
	std::chrono::microseconds _frameStart{0};
	std::chrono::microseconds _frameEnd{0};
	bool bRender = true;
};
} // namespace Inf
