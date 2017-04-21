#ifndef FLAPPY_CAT_FLAPPYCATENTITY_H
#define FLAPPY_CAT_FLAPPYCATENTITY_H

// engine
#include <core/Window.h>

// game
#include <game/FlappyCatGameConstants.h>
#include <game/FlappyCatClock.h>

class FlappyCatEntity {
public:
  FlappyCatEntity(const FlappyCatGameConstants& gameConstants);
  virtual ~FlappyCatEntity();

public:
  virtual void initialize();
  virtual void reset();
  virtual void update(const FrameDuration& frameDuration);
  virtual void drawOn(const Window& window) const = 0;

  virtual const Position& position() const;
  virtual Position::value_type rotation() const;
  virtual const Position& size() const;

  virtual void moveTo(const Position& position);
  virtual void moveBy(const Position& offset);

  virtual void resize(const Position& size);
  virtual void rotateTo(Position::value_type angle);

public:
  const FlappyCatGameConstants& gameConstants() const;
  const Position& acceleration() const;
  const Position& velocity() const;
  const Position& distance() const;
  void setAcceleration(const Position& acceleration);
  void setVelocity(const Position& velocity);
  void setGravity(const Position& gravity);

private:
  virtual void syncChildren();

private:
  const FlappyCatGameConstants& mGameConstants;
  Position mPosition;
  Position mSize;
  Position::value_type mAngle;
  Position mGravity;
  Position mAcceleration;
  Position mVelocity;
  Position mDistance;
};


#endif //FLAPPY_CAT_FLAPPYCATENTITY_H
