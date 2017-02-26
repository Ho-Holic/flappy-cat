#ifndef FLAPPY_CAT_FLAPPYCATWALL_H
#define FLAPPY_CAT_FLAPPYCATWALL_H

// engine
#include <core/Position.h>
#include <core/Window.h>
#include <prototype/RectangleShape.h>
#include <core/Clock.h>

// self
#include "FlappyCatEntity.h"

//
//    .----.
//    |....|
//    |....|
//    .----.    <----------.
//                         |
//     hero  <-            | Gap Interval
//            |            |
//    .----.  | <----------.
//    |....|  |
//    |....|  | Gap Displacement
//    .----. <-
//

class FlappyCatWall : public FlappyCatEntity {
public:
  // TODO: Need to fix issue with emplace_back()
  // TODO: it has some bug with call to empty constructor
  FlappyCatWall(const FlappyCatGameConstants& gameConstants);

public:
  void setGapInterval(Position::value_type interval);
  void setGapDisplacement(Position::value_type displacement);
  bool collideWithCircle(const Position& center, float radius);

public:
  virtual void update(const FrameDuration& time) override;
  virtual void drawOn(const Window& window) const override;
  virtual void moveTo(const Position& position) override;
  virtual const Position& position() const override;
  virtual void resize(const Position& size) override;

public:
  void setColor(const Color& color);

private:
  void syncChildrenSize();

private:
  Position mPosition;
  Position mSize;
  Position::value_type mGapInterval;
  Position::value_type mGapDisplacement;
  RectangleShape mTopBlock;
  RectangleShape mBottomBlock;


};



#endif //FLAPPY_CAT_FLAPPYCATWALL_H
