#ifndef FLAPPY_CAT_FLAPPYCATAPPLICATION_H
#define FLAPPY_CAT_FLAPPYCATAPPLICATION_H

// engine
#include <android/AndroidApplication.hpp>
#include <prototype/RectangleShape.hpp>
#include <prototype/CircleShape.hpp>

// game
#include "FlappyCatGame.hpp"
#include "FlappyCatClock.hpp"

class FlappyCatApplication : public AndroidApplication {
public:
  FlappyCatApplication(ANativeActivity* activity,
                       void* savedState,
                       size_t savedStateSize);

private:
  virtual void main();
};


#endif //FLAPPY_CAT_FLAPPYCATAPPLICATION_H
