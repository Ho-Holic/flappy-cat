#ifndef FLAPPY_CAT_FLAPPYCATENTITY_H
#define FLAPPY_CAT_FLAPPYCATENTITY_H

// engine
#include <core/Clock.h>
#include <core/Window.h>

// self
#include "FlappyCatGameConstants.h"

class FlappyCatEntity {
public:
  FlappyCatEntity(const FlappyCatGameConstants& gameConstants);
  virtual ~FlappyCatEntity();

public:
  virtual void initialize();
  virtual void reset();
  virtual void update(const FrameDuration& time);
  virtual void drawOn(const Window& window) const = 0;

  virtual const Position& position() const = 0;
  virtual void moveTo(const Position& position) = 0;
  virtual void moveBy(const Position& offset);

  virtual void resize(const Position& size);

public:
  const FlappyCatGameConstants& gameConstants() const;

private:
  const FlappyCatGameConstants& mGameConstants;
};


#endif //FLAPPY_CAT_FLAPPYCATENTITY_H
