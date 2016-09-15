#ifndef FLAPPY_CAT_FLAPPYCATAPPLICATION_H
#define FLAPPY_CAT_FLAPPYCATAPPLICATION_H

// self
#include "AndroidApplication.h"

class FlappyCatApplication : public AndroidApplication {
public:
  FlappyCatApplication(ANativeActivity* activity,
                       void* savedState,
                       size_t savedStateSize);

private:
  virtual void main();

private:
  void processEvents();
  void render();

private:
  float mSaturation;
  float mBrightness;
};


#endif //FLAPPY_CAT_FLAPPYCATAPPLICATION_H
