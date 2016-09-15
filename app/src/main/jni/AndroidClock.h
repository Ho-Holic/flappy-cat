#ifndef FLAPPY_CAT_ANDROIDCLOCK_H
#define FLAPPY_CAT_ANDROIDCLOCK_H

// stl
#include <chrono>

using AndroidClock = std::chrono::high_resolution_clock;
using AndroidTime = std::chrono::time_point<AndroidClock>;
using AndroidClockDuration = AndroidClock::duration;
using AndroidFrameTime = std::chrono::duration<int64_t , std::ratio<1, 60>>; // `1/60` of second

#endif //FLAPPY_CAT_ANDROIDCLOCK_H
