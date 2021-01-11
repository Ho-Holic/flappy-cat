#pragma once


// engine
#include <core/Window.hpp>

// game
#include <game/FlappyCatGameConstants.hpp>
#include <game/FlappyCatClock.hpp>

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
  virtual float rotation() const;
  virtual const Position& size() const;

  virtual void moveTo(const Position& position);
  virtual void moveBy(const Position& offset);

  virtual void resize(const Position& size);
  virtual void rotateTo(float angle);

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
  float mAngle;
  Position mGravity;
  Position mAcceleration;
  Position mVelocity;
  Position mDistance;
};



