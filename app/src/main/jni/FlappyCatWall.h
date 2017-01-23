#ifndef FLAPPY_CAT_FLAPPYCATWALL_H
#define FLAPPY_CAT_FLAPPYCATWALL_H

// self
#include <core/Position.h>
#include <android/AndroidWindow.h>
#include <prototype/RectangleShape.h>
#include <core/Clock.h>

class FlappyCatWall {
public:
  FlappyCatWall(const Position& position, const Position& size);

public:
  void setGapInterval(Position::position_type interval);
  void setGapDisplacement(Position::position_type displacement);
  void setPosition(const Position& position);
  void setColor(const Color& color);
  const Position& position() const;

public:
  void update(const FrameDuration& time);
  bool collideWithCircle(const Position& center, float radius);
  void drawOn(const AndroidWindow& window) const;

private:
  Position::position_type mGapInterval;
  Position::position_type mGapDisplacement;
  RectangleShape mTopBlock;
  RectangleShape mBottomBlock;
};


#endif //FLAPPY_CAT_FLAPPYCATWALL_H
