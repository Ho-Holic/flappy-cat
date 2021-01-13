#pragma once

#ifdef FLAPPYCAT_QT

#include "qt/QtEvent.hpp"
using Event = QtEvent;

#elif FLAPPYCAT_ANDROID

// engine
#include <android/AndroidEvent.hpp>

// Do not extend 'AndroidEvent: Event', this would cause bad behaviour in user code
// where user would create 'Event event; pollEvent(event);'

using Event = AndroidEvent;

#else

using Event = void;

#endif
