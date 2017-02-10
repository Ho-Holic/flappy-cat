// self
#include "FlappyCatSpike.h"

FlappyCatSpike::FlappyCatSpike(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mSpike() {
  //
}

void FlappyCatSpike::drawOn(const Window& window) const {

  window.draw(mSpike);
}

void FlappyCatSpike::moveTo(const Position& position) {

  mSpike.transformation().setPosition(position);
}

void FlappyCatSpike::resize(const Position& size) {

  mSpike.geometry().resize(size);
}

const Position& FlappyCatSpike::position() const {

  return mSpike.transformation().position();
}

void FlappyCatSpike::setColor(const Color& color) {

  mSpike.setColor(color);
}


