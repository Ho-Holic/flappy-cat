// self
#include "FlappyCatHero.h"

FlappyCatHero::FlappyCatHero()
: FlappyCatEntity()
, mBall() {
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

void FlappyCatHero::setColor(const Color& color) {

  mBall.setColor(color);
}













