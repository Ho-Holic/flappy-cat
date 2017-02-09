// self
#include "FlappyCatHero.h"

FlappyCatHero::FlappyCatHero(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mBall()
, mResetModifier([](entity_type&){}) {
  //
}

float FlappyCatHero::radius() const {

  return mBall.geometry().radius();
}

void FlappyCatHero::setRadius(float radius) {

  mBall.geometry().setRadius(radius);
}

void FlappyCatHero::moveTo(const Position& position) {

  mBall.transformation().setPosition(position);
}

void FlappyCatHero::drawOn(const Window& window) const {

  window.draw(mBall);
}

const Position& FlappyCatHero::position() const {

  return mBall.transformation().position();
}

void FlappyCatHero::reset() {

  mResetModifier(*this);
}

void FlappyCatHero::setResetModifier(const modifier_type& modifier) {

  mResetModifier = modifier;
}

void FlappyCatHero::setColor(const Color& color) {

  mBall.setColor(color);
}




