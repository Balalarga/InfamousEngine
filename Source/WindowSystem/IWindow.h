#pragma once
#include "WindowParams.h"

namespace Inf
{
class IWindow
{
public:
	IWindow(WindowParams&& params);
	virtual ~IWindow();

	virtual bool IsValid() const = 0;
	virtual void Run() = 0;
	virtual void Close(bool forced = false) = 0;

	const WindowParams& GetParams() const
	{
		return _params;
	}


private:
	WindowParams _params;
};
}