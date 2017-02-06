#ifndef FLAPPY_CAT_FLAPPYCATHERO_H
#define FLAPPY_CAT_FLAPPYCATHERO_H

// engine
#include <prototype/CircleShape.h>

// self
#include "FlappyCatEntity.h"

class FlappyCatHero : public FlappyCatEntity {
public:
  FlappyCatHero();

public:
  virtual void drawOn(const Window& window) const;
  virtual const Position& position() const;
  virtual void moveTo(const Position& position);
  virtual void setColor(const Color& color);

public:
  void setRadius(float radius);
  float radius() const;

private:
  CircleShape mBall;
};


#endif //FLAPPY_CAT_FLAPPYCATHERO_H
