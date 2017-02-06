#ifndef FLAPPY_CAT_FLAPPYCATSPIKE_H
#define FLAPPY_CAT_FLAPPYCATSPIKE_H

// engine
#include <prototype/RectangleShape.h>

// self
#include "FlappyCatEntity.h"

class FlappyCatSpike : public FlappyCatEntity {
public:
  FlappyCatSpike(const Position& position, const Position& size);

public:
  virtual void drawOn(const Window& window) const override;
  virtual void moveTo(const Position& position) override;
  virtual void resize(const Position& size) override;
  virtual const Position& position() const override;
  virtual void setColor(const Color& color) override;

private:
  RectangleShape mSpike;
};


#endif //FLAPPY_CAT_FLAPPYCATSPIKE_H
