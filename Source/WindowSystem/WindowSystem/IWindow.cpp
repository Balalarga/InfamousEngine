#include "IWindow.h"
#include "IWindowUpdateLoop.h"

namespace Inf
{
IWindow::IWindow(WindowParams&& params) : _params(std::move(params))
{
}

IWindow::~IWindow() = default;

void IWindow::Run(std::unique_ptr<IWindowUpdateLoop>&& updateLoop)
{
	while(IsOpened())
	{
		updateLoop->BeginLoop(GetSystemTime());
		updateLoop->HandleEvents();
		updateLoop->Update();
		updateLoop->Render();
		updateLoop->EndLoop(GetSystemTime());
	}
}
} // namespace Inf
