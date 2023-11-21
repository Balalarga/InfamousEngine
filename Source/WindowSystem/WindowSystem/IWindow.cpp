#include "IWindow.h"
#include "IWindowUpdateLoop.h"
#include "Time/Time.h"

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
		updateLoop->BeginLoop();
		updateLoop->HandleEvents();
		updateLoop->Update();
		updateLoop->Render();
		updateLoop->EndLoop();
	}
}
} // namespace Inf
