#ifndef FLAPPY_CAT_EVENT_H
#define FLAPPY_CAT_EVENT_H

#ifdef FLAPPYCAT_QT

#include "QtEvent.h"
using Event = QtEvent;

#else

// engine
#include <android/AndroidEvent.h>

// Do not extend 'AndroidEvent: Event', this would cause bad behaviour in user code
// where user would create 'Event event; pollEvent(event);'

using Event = AndroidEvent;

#endif

#endif //FLAPPY_CAT_EVENT_H
