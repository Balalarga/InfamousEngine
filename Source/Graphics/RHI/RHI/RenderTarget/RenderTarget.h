#pragma once

#include "IRenderBindable.h"


namespace Inf
{

class IRenderTarget: public IRenderBindable
{
public:
	IRenderTarget() = default;
	virtual ~IRenderTarget() = default;

	virtual void Clear() = 0;
	virtual void Present() = 0;
};

}