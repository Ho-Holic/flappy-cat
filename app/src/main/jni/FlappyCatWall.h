#ifndef FLAPPY_CAT_FLAPPYCATWALL_H
#define FLAPPY_CAT_FLAPPYCATWALL_H

// engine
#include <core/Position.h>
#include <android/AndroidWindow.h>
#include <prototype/RectangleShape.h>
#include <core/Clock.h>

// self
#include "FlappyCatEntity.h"

class FlappyCatWall : public FlappyCatEntity {
public:
  FlappyCatWall(const Position& position, const Position& size);

public:
  void setGapInterval(Position::position_type interval);
  void setGapDisplacement(Position::position_type displacement);
  bool collideWithCircle(const Position& center, float radius);

public:
  virtual void update(const FrameDuration& time) override;
  virtual void drawOn(const AndroidWindow& window) const override;
  virtual void moveTo(const Position& position) override;
  virtual const Position& position() const override;
  virtual void setColor(const Color& color) override;

private:
  Position::position_type mGapInterval;
  Position::position_type mGapDisplacement;
  RectangleShape mTopBlock;
  RectangleShape mBottomBlock;
};



#endif //FLAPPY_CAT_FLAPPYCATWALL_H
