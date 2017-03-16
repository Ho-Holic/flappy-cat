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
//  A4    .----.
//        |....|
//        |....|
//  A3    .----.    <----------.
//                             |
//         hero  <-            | Gap Interval
//                |            |
//  A2    .----.  | <----------.
//        |....|  |
//        |....|  | Gap Displacement
//  A1    .----. <-
//

class FlappyCatWall : public FlappyCatEntity {
public:
  /*
   * TODO: Problem with emplace_back() with no args
   * It has some bug with call to empty constructor
   * Then game show black screen. Also header files
   * shows that emplace build on top of push_back()
   * Seems this is not final version of header
   * Need to check this bug in Ndk r15
   */
  FlappyCatWall(const FlappyCatGameConstants& gameConstants);

public:
  void setGapInterval(Position::value_type interval);
  void setGapDisplacement(Position::value_type displacement);
  bool collideWithCircle(const Position& center, float radius);

public:
  virtual void drawOn(const Window& window) const override;
  virtual void moveTo(const Position& position) override;
  virtual const Position& position() const override;
  virtual void resize(const Position& size) override;

public:
  void setColor(const Color& color);

private:
  void syncChildren();

private:
  Position mPosition;
  Position mSize;
  Position::value_type mGapInterval;
  Position::value_type mGapDisplacement;
  RectangleShape mTopBlock;
  RectangleShape mBottomBlock;


};



#endif //FLAPPY_CAT_FLAPPYCATWALL_H
