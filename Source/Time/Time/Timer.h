#pragma once

#include "Timeline.h"


namespace Inf
{
template <class TClock = DefaultClock>
class TTimer
{
public:
	explicit TTimer(const Timeline<TClock>& timeline = GlobalTimeline<TClock>(), bool autoStart = true) :
		_timeline(timeline)
	{
		if (autoStart)
		{
			_startTime = _timeline.GetPassedTime();
		}
	}

	explicit TTimer(bool autoStart) : TTimer(GlobalTimeline<TClock>(), autoStart)
	{
	}

	template <class TDuration = typename Timeline<TClock>::BaseDuration>
		requires TIsDuration<TDuration>
	TDuration Reset()
	{
		auto duration = std::chrono::duration_cast<TDuration>(_timeline.GetPassedTime() - _startTime);
		_startTime = _timeline.template GetPassedTime<TDuration>();
		return duration;
	}

	template <class TDuration = typename Timeline<TClock>::BaseDuration>
	TDuration GetNow() const
	{
		return _timeline.template GetPassedTime<TDuration>();
	}

	template <class TDuration = typename Timeline<TClock>::BaseDuration>
	TDuration GetPassedTime() const
	{
		return std::chrono::duration_cast<TDuration>(GetNow() - _startTime);
	}


private:
	const Timeline<TClock>& _timeline;
	typename Timeline<TClock>::BaseDuration _startTime{};
};

using Timer = TTimer<>;
}