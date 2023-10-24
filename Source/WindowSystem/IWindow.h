#pragma once
#include "WindowParams.h"

namespace Inf
{
class IWindow
{
public:
	IWindow(WindowParams&& params);
	virtual ~IWindow();

	virtual void Open() = 0;
	virtual void Close(bool forced = false) = 0;

	const WindowParams& GetParams() const
	{
		return _params;
	}


private:
	WindowParams _params;
};
}