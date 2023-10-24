#pragma once
#include "IWindow.h"

namespace Inf
{

class Window: public IWindow
{
public:
	using IWindow::IWindow;

	void Open() override;
	void Close(bool forced) override;
};

}