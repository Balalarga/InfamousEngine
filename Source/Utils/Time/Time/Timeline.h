#pragma once
#include "Types.h"


namespace Inf
{

class Timeline
{
public:
	explicit Timeline(const DefaultTimePoint& point = DefaultClock::now());
	
	template<class TDuration = Milliseconds>
	requires IsADuration<TDuration>
	TDuration GetPassedTime() const
	{
		return std::chrono::duration_cast<TDuration>(DefaultClock::now() - _startTime);
	}


private:
	DefaultTimePoint _startTime;
};

}
