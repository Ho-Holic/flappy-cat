#ifndef FLAPPY_CAT_ANDROIDCLOCK_H
#define FLAPPY_CAT_ANDROIDCLOCK_H

// stl
#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using Time = std::chrono::time_point<Clock>;
using ClockDuration = Clock::duration;
using FrameDuration = std::chrono::duration<float , std::ratio<1, 60>>; // `1/60` of second

#endif //FLAPPY_CAT_ANDROIDCLOCK_H
