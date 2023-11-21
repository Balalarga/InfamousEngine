#pragma once

#include <chrono>

namespace Inf
{

#ifndef INF_TIME_CUSTOM_TYPES_DEFINITION
template <class TClock, class TDuration = typename TClock::duration>
using TimePoint = std::chrono::time_point<TClock, TDuration>;

using Seconds = std::chrono::seconds;
using Milliseconds = std::chrono::milliseconds;
using Microseconds = std::chrono::microseconds;
using Nanoseconds = std::chrono::nanoseconds;

using DefaultClock = std::chrono::steady_clock;
using HighResClock = std::chrono::high_resolution_clock;

using DefaultTimePoint = TimePoint<DefaultClock>;
using HighResTimePoint = TimePoint<HighResClock>;
#endif

template <class T>
concept IsADuration = std::is_same_v<T, std::chrono::duration<typename T::rep, typename T::period>>;
}
