#include "IWindow.h"

namespace Inf
{
	
IWindow::IWindow(WindowParams&& params): _params(std::move(params))
{
 	
}

IWindow::~IWindow() = default;
	
}