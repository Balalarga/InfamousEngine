#pragma once

#include "Types.h"


namespace Inf
{

template <class TClock = DefaultClock>
class Timeline
{
public:
	using BaseDuration = typename TimePoint<TClock>::duration;

	explicit Timeline(const TimePoint<TClock>& point = TClock::now()) : _startTime(point)
	{
	}

	template <class TDuration = BaseDuration>
		requires TIsDuration<TDuration>
	TDuration GetPassedTime() const
	{
		return std::chrono::duration_cast<TDuration>(TClock::now() - _startTime);
	}


private:
	TimePoint<TClock> _startTime;
};


template <class T>
const Timeline<T>& GlobalTimeline() = delete;

template <>
const Timeline<DefaultClock>& GlobalTimeline();

template <>
const Timeline<HighResClock>& GlobalTimeline();

}