#include "IRenderBindable.h"


namespace Inf
{

void IRenderBindable::Release()
{
	if (_needRelease)
	{
		ReleaseImpl();
	}
}

bool IRenderBindable::NeedRelease() const
{
	return _needRelease;
}

void IRenderBindable::SetNeedRelease(bool state)
{
	_needRelease = state;
}

}