#ifndef FLAPPY_CAT_FLAPPYCATENTITY_H
#define FLAPPY_CAT_FLAPPYCATENTITY_H

// self
#include <core/Clock.h>
#include <core/Window.h>

class FlappyCatEntity {
public:
  virtual void drawOn(const Window& window) const = 0;
  virtual const Position& position() const = 0;
  virtual void moveTo(const Position& position) = 0;
  virtual void setColor(const Color& color) = 0;
  virtual void update(const FrameDuration& time);
  virtual void moveBy(const Position& offset);
  virtual void resize(const Position& size);
  virtual void reset();
};


#endif //FLAPPY_CAT_FLAPPYCATENTITY_H
