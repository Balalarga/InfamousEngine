#pragma once
#include "IWindow.h"

namespace Inf
{
// TODOL (gui?) CLI
class ServerInvisibleWindow: public IWindow
{
public:
	struct Initializer
	{

	};
	ServerInvisibleWindow(const Initializer& initializer = {});

	void Open() override;
	void Render() override;
	void Resize(unsigned x, unsigned y) override;
	glm::uvec2 GetSize() const override;
	void HandleEvents() override;
};
}