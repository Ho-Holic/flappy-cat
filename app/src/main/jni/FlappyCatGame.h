#ifndef FLAPPY_CAT_FLAPPYCATGAME_H
#define FLAPPY_CAT_FLAPPYCATGAME_H

// self
#include <core/Clock.h>
#include <android/AndroidEvent.h>
#include <android/AndroidWindow.h>
#include <prototype/RectangleShape.h>
#include <prototype/CircleShape.h>

class FlappyCatGame {
public:
  FlappyCatGame();
public:
  void processEvent(const AndroidEvent& event);
  void update(const FrameDuration& time);
  void render(const AndroidWindow&);

private:
  float mSaturation;
  float mBrightness;
  std::size_t mSizeFactor;
  RectangleShape mRect;
  CircleShape mCircle;
};


#endif //FLAPPY_CAT_FLAPPYCATGAME_H
