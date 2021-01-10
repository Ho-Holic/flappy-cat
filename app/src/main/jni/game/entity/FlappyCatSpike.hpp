#ifndef FLAPPY_CAT_FLAPPYCATSPIKE_H
#define FLAPPY_CAT_FLAPPYCATSPIKE_H

// engine
#include <prototype/RectangleShape.hpp>

// game
#include "FlappyCatEntity.hpp"

class FlappyCatSpike : public FlappyCatEntity {
public:
  /*
   * TODO: Problem with emplace_back() with no args
   *
   * It has some bug with call to empty constructor
   * Then game show black screen. Also header files
   * shows that emplace build on top of push_back()
   * Seems this is not final version of header
   * Need to check this bug in Ndk r15
   */
  FlappyCatSpike(const FlappyCatGameConstants& gameConstants);

public:
  virtual void drawOn(const Window& window) const override;

public:
  void setColor(const Color& color);

private:
  virtual void syncChildren() override;

private:
  RectangleShape mSpike;
};


#endif //FLAPPY_CAT_FLAPPYCATSPIKE_H
