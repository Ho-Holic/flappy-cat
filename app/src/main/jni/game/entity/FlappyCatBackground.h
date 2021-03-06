#ifndef FLAPPY_CAT_FLAPPYCATBACKGROUND_H
#define FLAPPY_CAT_FLAPPYCATBACKGROUND_H

// engine
#include <prototype/RectangleShape.h>

// game
#include "FlappyCatEntity.h"

class FlappyCatBackground : public FlappyCatEntity {
public:
  using entity_type = FlappyCatBackground;
  using modifier_type = std::function<void(entity_type&)>;

public:
  FlappyCatBackground(const FlappyCatGameConstants& gameConstants);

public:
  virtual void drawOn(const Window& window) const override;
  virtual void reset() override;

public:
  void setColor(const Color& color);
  void setResetModifier(const modifier_type& modifier);

private:
  virtual void syncChildren() override;

private:
  RectangleShape mBackground;
  modifier_type mResetModifier;
};


#endif //FLAPPY_CAT_FLAPPYCATBACKGROUND_H
