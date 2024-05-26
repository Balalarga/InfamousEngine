#include "Timeline.h"

namespace Inf
{

static Timeline<DefaultClock> _sGlobalTimeline;
static Timeline<HighResClock> _sGlobalHighResTimeline;

template <>
const Timeline<DefaultClock>& GlobalTimeline()
{
	return _sGlobalTimeline;
}

template <>
const Timeline<HighResClock>& GlobalTimeline()
{
	return _sGlobalHighResTimeline;
}

}
