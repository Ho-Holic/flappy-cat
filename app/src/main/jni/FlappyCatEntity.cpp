// self
#include "FlappyCatEntity.h"

FlappyCatEntity::FlappyCatEntity(const FlappyCatGameConstants& gameConstants)
: mGameConstants(gameConstants) {
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

void FlappyCatEntity::update(const FrameDuration& time) {
  // intentionally left blank
}

void FlappyCatEntity::initialize() {
  // intentionally left blank
}

const FlappyCatGameConstants& FlappyCatEntity::gameConstants() const {

  return mGameConstants;
}
