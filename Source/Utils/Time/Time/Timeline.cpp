#include "Timeline.h"

namespace Inf
{
Timeline::Timeline(const DefaultTimePoint& point): _startTime(point), _currentTime(point)
{
}

void Timeline::Update(const DefaultTimePoint& point)
{
	_currentTime = point;
}

}
