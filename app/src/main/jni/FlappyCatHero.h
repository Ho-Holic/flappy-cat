#ifndef FLAPPY_CAT_FLAPPYCATHERO_H
#define FLAPPY_CAT_FLAPPYCATHERO_H

// engine
#include <prototype/CircleShape.h>

// self
#include "FlappyCatEntity.h"

class FlappyCatHero : public FlappyCatEntity {
public:
  FlappyCatHero(const FlappyCatGameConstants& gameConstants);

public:
  virtual void drawOn(const Window& window) const override;
  virtual const Position& position() const override ;
  virtual void moveTo(const Position& position) override ;
  virtual void setColor(const Color& color) override ;

public:
  void setRadius(float radius);
  float radius() const;

private:
  CircleShape mBall;
};


#endif //FLAPPY_CAT_FLAPPYCATHERO_H
