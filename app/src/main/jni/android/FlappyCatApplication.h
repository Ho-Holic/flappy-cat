#ifndef FLAPPY_CAT_FLAPPYCATAPPLICATION_H
#define FLAPPY_CAT_FLAPPYCATAPPLICATION_H

// engine
#include <android/AndroidApplication.h>
#include <prototype/RectangleShape.h>
#include <prototype/CircleShape.h>

// game
#include "FlappyCatGame.h"
#include "FlappyCatClock.h"

class FlappyCatApplication : public AndroidApplication {
public:
  FlappyCatApplication(ANativeActivity* activity,
                       void* savedState,
                       size_t savedStateSize);

private:
  virtual void main();
};


#endif //FLAPPY_CAT_FLAPPYCATAPPLICATION_H
