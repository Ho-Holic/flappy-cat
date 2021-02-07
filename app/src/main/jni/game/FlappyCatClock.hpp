#pragma once

// engine
#include <core/Clock.hpp>

// '1/60' of a second
using FrameDuration = std::chrono::duration<float,
    std::ratio<1, 60>>;

using GameSecond = std::chrono::duration<float,
    std::ratio<1, 1>>;
