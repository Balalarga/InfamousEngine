#pragma once
#include <glm/vec2.hpp>

namespace Inf
{
class InputManager;

class IWindow
{
public:
	bool IsClosed() const { return _bIsClosed; }
	virtual void Close() { _bIsClosed = true; }

	virtual void Open() = 0;
	virtual void Render() = 0;

	virtual void Resize(unsigned x, unsigned y) = 0;
	virtual glm::uvec2 GetSize() const = 0;

	virtual void HandleEvents() = 0;
	virtual InputManager* GetInputManager() { return nullptr; }

protected:
	bool _bIsClosed = true;
};
}
