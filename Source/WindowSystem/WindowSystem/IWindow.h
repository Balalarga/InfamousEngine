#pragma once
#include <chrono>
#include <memory>

#include "WindowParams.h"

namespace Inf
{
class IWindow
{
public:
	explicit IWindow(WindowParams&& params);
	virtual ~IWindow();

	virtual void Run(std::unique_ptr<class IWindowUpdateLoop>&& updateLoop);
	virtual bool IsValid() const = 0;
	virtual void Close(bool forced = false) = 0;
	virtual bool IsOpened() const = 0;
	
	const WindowParams& GetParams() const
	{
		return _params;
	}


private:
	WindowParams _params;
};
} // namespace Inf
