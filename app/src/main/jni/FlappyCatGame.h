#ifndef FLAPPY_CAT_FLAPPYCATGAME_H
#define FLAPPY_CAT_FLAPPYCATGAME_H

// self
#include <core/Clock.h>
#include <android/AndroidEvent.h>
#include <android/AndroidWindow.h>
#include <prototype/RectangleShape.h>
#include <prototype/CircleShape.h>

// stl
#include <vector>

class FlappyCatGame {
public:
  FlappyCatGame();
public:
  void processEvent(const AndroidEvent& event);
  void update(const FrameDuration& time);
  void render(const AndroidWindow&);

private:
  std::vector<RectangleShape> mBlocks;
  CircleShape mCircle;
};


#endif //FLAPPY_CAT_FLAPPYCATGAME_H
