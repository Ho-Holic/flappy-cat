// self
#include "FlappyCatEntity.h"

void FlappyCatEntity::reset() {
  // intentionally left blank
}

void FlappyCatEntity::moveBy(const Position& offset) {
  moveTo(position() + offset);
}

void FlappyCatEntity::resize(const Position &size) {
  // intentionally left blank
}

void FlappyCatEntity::update(const FrameDuration &time) {
  // intentionally left blank
}







