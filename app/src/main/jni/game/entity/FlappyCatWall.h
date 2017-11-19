#ifndef FLAPPY_CAT_FLAPPYCATWALL_H
#define FLAPPY_CAT_FLAPPYCATWALL_H

// engine
#include <core/Position.h>
#include <core/Window.h>
#include <prototype/RectangleShape.h>
#include <core/Clock.h>

// game
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
  bool collideWithCircle(const Position& center, Position::value_type radius);

public:
  virtual void drawOn(const Window& window) const override;

public:
  void setColor(const Color& color);
  const Color& color() const;

private:
  virtual void syncChildren() override;

private:
  Position::value_type mGapInterval;
  Position::value_type mGapDisplacement;
  RectangleShape mTopBlock;
  RectangleShape mBottomBlock;


};



#endif //FLAPPY_CAT_FLAPPYCATWALL_H
