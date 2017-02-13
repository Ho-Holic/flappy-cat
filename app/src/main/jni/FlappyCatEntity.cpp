// self
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
  // intentionally left blank
}

void FlappyCatEntity::moveBy(const Position& offset) {
  moveTo(position() + offset);
}

void FlappyCatEntity::resize(const Position& size) {
  // intentionally left blank
}

void FlappyCatEntity::update(const FrameDuration& frameDuration) {

  using FloatSecond = std::chrono::duration<Position::position_type, std::ratio<1,1>>;

  Position::position_type time = std::chrono::duration_cast<FloatSecond>(frameDuration).count();

  Log::i(TAG, "Time: %f", time);

  mAcceleration = mAcceleration - Position(0.f, mGameConstants.gravity());
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










