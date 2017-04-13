
// game
#include "FlappyCatBackground.h"

FlappyCatBackground::FlappyCatBackground(const FlappyCatGameConstants& gameConstants)
  : FlappyCatEntity(gameConstants)
  , mBackground()
  , mResetModifier([](entity_type&){}) {
  //
}

void FlappyCatBackground::drawOn(const Window& window) const {

  window.draw(mBackground);
}

void FlappyCatBackground::setResetModifier(const FlappyCatBackground::modifier_type& modifier) {

  mResetModifier = modifier;
}

void FlappyCatBackground::reset() {

  mResetModifier(*this);
}

void FlappyCatBackground::moveTo(const Position& position) {

  mBackground.transformation().setPosition(position);
}

void FlappyCatBackground::resize(const Position& size) {

  mBackground.geometry().resize(size);
}

const Position& FlappyCatBackground::position() const {

  return mBackground.transformation().position();
}

void FlappyCatBackground::setColor(const Color& color) {

  mBackground.setColor(color);
}

