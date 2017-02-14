#ifndef FLAPPY_CAT_FLAPPYCATSPIKE_H
#define FLAPPY_CAT_FLAPPYCATSPIKE_H

// engine
#include <prototype/RectangleShape.h>

// self
#include "FlappyCatEntity.h"

class FlappyCatSpike : public FlappyCatEntity {
public:
  // TODO: Need to fix issue with empty emplace_back()
  // TODO: it has some bug with call to empty constructor
  FlappyCatSpike(const FlappyCatGameConstants& gameConstants);

public:
  virtual void drawOn(const Window& window) const override;
  virtual void moveTo(const Position& position) override;
  virtual void resize(const Position& size) override;
  virtual const Position& position() const override;

public:
  virtual void setColor(const Color& color);

private:
  RectangleShape mSpike;
};


#endif //FLAPPY_CAT_FLAPPYCATSPIKE_H
