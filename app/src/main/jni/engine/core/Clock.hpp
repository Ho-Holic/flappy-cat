#pragma once

// stl
#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using Time = std::chrono::time_point<Clock>;
using ClockDuration = Clock::duration;
