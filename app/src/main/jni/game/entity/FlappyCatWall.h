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
  void setGapInterval(f32 interval);
  void setGapDisplacement(f32 displacement);
  bool collideWithCircle(const Position& center, f32 radius);

public:
  virtual void drawOn(const Window& window) const override;

public:
  void setColor(const Color& color);
  const Color& color() const;
  void activateWall();

private:
  enum class WallState {
    Normal,
    Activated
  };

private:
  virtual void syncChildren() override;

private:
  f32 mGapInterval;
  f32 mGapDisplacement;
  RectangleShape mTopBlock;
  RectangleShape mBottomBlock;
  WallState mWallState;
};



#endif //FLAPPY_CAT_FLAPPYCATWALL_H
