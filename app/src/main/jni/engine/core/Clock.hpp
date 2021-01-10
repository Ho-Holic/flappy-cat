#ifndef FLAPPY_CAT_ANDROIDCLOCK_H
#define FLAPPY_CAT_ANDROIDCLOCK_H

// stl
#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using Time = std::chrono::time_point<Clock>;
using ClockDuration = Clock::duration;

#endif //FLAPPY_CAT_ANDROIDCLOCK_H
