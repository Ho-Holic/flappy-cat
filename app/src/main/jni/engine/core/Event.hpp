#ifndef FLAPPY_CAT_EVENT_H
#define FLAPPY_CAT_EVENT_H

#ifdef FLAPPYCAT_QT

#include "qt/QtEvent.h"
using Event = QtEvent;

#elif FLAPPYCAT_ANDROID

// engine
#include <android/AndroidEvent.h>

// Do not extend 'AndroidEvent: Event', this would cause bad behaviour in user code
// where user would create 'Event event; pollEvent(event);'

using Event = AndroidEvent;

#else

using Event = void;

#endif

#endif //FLAPPY_CAT_EVENT_H
