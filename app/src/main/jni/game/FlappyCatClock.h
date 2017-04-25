#ifndef FLAPPY_CAT_FLAPPYCATCLOCK_H
#define FLAPPY_CAT_FLAPPYCATCLOCK_H

// engine
#include <core/Clock.h>
#include <core/Position.h>

// '1/60' of a second
using FrameDuration = std::chrono::duration<Position::value_type,
                                            std::ratio<1, 60>>;

using GameSecond = std::chrono::duration<Position::value_type,
                                          std::ratio<1,1>>;

#endif //FLAPPY_CAT_FLAPPYCATCLOCK_H
