#pragma once

#include <chrono>


#ifndef INF_ENGINE_TIME_CLOCK
#define INF_ENGINE_TIME_CLOCK std::chrono::system_clock
#endif

#ifndef INF_ENGINE_TIME_HIRES_CLOCK
#define INF_ENGINE_TIME_HIRES_CLOCK std::chrono::high_resolution_clock
#endif

namespace Inf
{

template <class T>
concept TIsDuration = std::is_same_v<T, std::chrono::duration<typename T::rep, typename T::period>>;

template <class TClock, class TDuration = typename TClock::duration>
using TimePoint = std::chrono::time_point<TClock, TDuration>;

using Seconds = std::chrono::seconds;
using Milliseconds = std::chrono::milliseconds;
using Microseconds = std::chrono::microseconds;
using Nanoseconds = std::chrono::nanoseconds;

using DefaultClock = INF_ENGINE_TIME_CLOCK;
using HighResClock = INF_ENGINE_TIME_HIRES_CLOCK;

using DefaultTimePoint = TimePoint<DefaultClock>;
using HighResTimePoint = TimePoint<HighResClock>;

}