// game
#include "FlappyCatEntity.h"

// engine
#include <core/Log.h>

FlappyCatEntity::FlappyCatEntity(const FlappyCatGameConstants& gameConstants)
: mGameConstants(gameConstants)
, mAcceleration()
, mVelocity()
, mDistance() {
  //
}

FlappyCatEntity::~FlappyCatEntity() {
  // intentionally left blank
}

void FlappyCatEntity::reset() {

  mAcceleration = Position(0.f, 0.f);
  mVelocity = Position(0.f, 0.f);
  mDistance = Position(0.f, 0.f);
}

void FlappyCatEntity::moveBy(const Position& offset) {

  moveTo(position() + offset);
}

void FlappyCatEntity::resize(const Position& size) {
  // intentionally left blank
}

void FlappyCatEntity::rotate(Position::value_type angle) {
  // intentionally left blank
}

/**
 * TODO: Create new entity for objects with physics
 *
 * Move this to PhysicsEntity or some other fancy name
 * This would prevent from calculating physics on static objects
 * and other that don't use this params
 * Normally if you would implement 'update()' yourself, you can
 * omit call to this function, but if you don't provide default one
 * this code would be called
 */
void FlappyCatEntity::update(const FrameDuration& frameDuration) {

  Position::value_type time = std::chrono::duration_cast<FloatSecond>(frameDuration).count();

  mAcceleration = mAcceleration - Position(0.f, mGameConstants.gravity().y());
  mVelocity = mVelocity + (mAcceleration * time);

  mDistance = mVelocity * time; // distance passed by last update

}

void FlappyCatEntity::initialize() {
  // intentionally left blank
}

const FlappyCatGameConstants& FlappyCatEntity::gameConstants() const {

  return mGameConstants;
}

const Position& FlappyCatEntity::acceleration() const {

  return mAcceleration;
}

const Position& FlappyCatEntity::velocity() const {

  return mVelocity;
}

const Position& FlappyCatEntity::distance() const {

  return mDistance;
}

void FlappyCatEntity::setAcceleration(const Position& acceleration) {

  mAcceleration = acceleration;
}

void FlappyCatEntity::setVelocity(const Position& velocity) {

  mVelocity = velocity;
}

Position::value_type FlappyCatEntity::rotation() const {
  return 0.f;
}
