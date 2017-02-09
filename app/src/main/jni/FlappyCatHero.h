#ifndef FLAPPY_CAT_FLAPPYCATHERO_H
#define FLAPPY_CAT_FLAPPYCATHERO_H

// engine
#include <prototype/CircleShape.h>

// self
#include "FlappyCatEntity.h"

class FlappyCatHero : public FlappyCatEntity {
public:
  using entity_type = FlappyCatHero;
  using modifier_type = std::function<void(entity_type&)>;

public:
  FlappyCatHero(const FlappyCatGameConstants& gameConstants);

public:
  virtual void drawOn(const Window& window) const override;
  virtual const Position& position() const override ;
  virtual void moveTo(const Position& position) override ;
  virtual void reset() override;

public:
  void setColor(const Color& color);
  void setResetModifier(const modifier_type& modifier);
  void setRadius(float radius);
  float radius() const;

private:
  CircleShape mBall;
  modifier_type mResetModifier;
};


#endif //FLAPPY_CAT_FLAPPYCATHERO_H
