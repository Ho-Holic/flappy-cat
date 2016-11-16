#ifndef FLAPPY_CAT_FLAPPYCATAPPLICATION_H
#define FLAPPY_CAT_FLAPPYCATAPPLICATION_H

// self
#include <android/AndroidApplication.h>
#include <core/Clock.h>
#include <prototype/RectangleShape.h>
#include <prototype/CircleShape.h>

class FlappyCatApplication : public AndroidApplication {
public:
  FlappyCatApplication(ANativeActivity* activity,
                       void* savedState,
                       size_t savedStateSize);

private:
  virtual void main();

private:
  void processEvents();
  void update(const FrameDuration& time);
  void render();

private:
  float mSaturation;
  float mBrightness;
  std::size_t mSizeFactor;
  RectangleShape mRect;
  CircleShape mCircle;
};


#endif //FLAPPY_CAT_FLAPPYCATAPPLICATION_H
