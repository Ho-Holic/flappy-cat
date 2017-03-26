#ifndef FLAPPY_CAT_FLAPPYCATENTITY_H
#define FLAPPY_CAT_FLAPPYCATENTITY_H

// engine
#include <core/Window.h>

// self
#include "FlappyCatGameConstants.h"
#include "FlappyCatClock.h"

class FlappyCatEntity {
public:
  FlappyCatEntity(const FlappyCatGameConstants& gameConstants);
  virtual ~FlappyCatEntity();

public:
  virtual void initialize();
  virtual void reset();
  virtual void update(const FrameDuration& frameDuration);
  virtual void drawOn(const Window& window) const = 0;

  virtual const Position& position() const = 0;
  virtual void moveTo(const Position& position) = 0;
  virtual void moveBy(const Position& offset);

  virtual void resize(const Position& size);

public:
  const FlappyCatGameConstants& gameConstants() const;
  const Position& acceleration() const;
  const Position& velocity() const;
  const Position& distance() const;
  void setAcceleration(const Position& acceleration);
  void setVelocity(const Position& velocity);

private:
  const FlappyCatGameConstants& mGameConstants;
  Position mAcceleration;
  Position mVelocity;
  Position mDistance;
};


#endif //FLAPPY_CAT_FLAPPYCATENTITY_H
