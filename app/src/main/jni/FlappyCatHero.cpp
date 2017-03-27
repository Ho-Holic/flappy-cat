// self
#include <prototype/RectangleShape.h>
#include <prototype/TriangleShape.h>
#include "FlappyCatHero.h"

FlappyCatHero::FlappyCatHero(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mBall()
, mResetModifier([](entity_type&){})
, mUpdateModifier([](entity_type&, const FrameDuration&){}) {
  //
}

Position::value_type FlappyCatHero::radius() const {

  return mBall.geometry().radius();
}

void FlappyCatHero::setRadius(Position::value_type  radius) {

  mBall.geometry().setRadius(radius);
}

void FlappyCatHero::moveTo(const Position& position) {

  mBall.transformation().setPosition(position);
}

void FlappyCatHero::update(const FrameDuration& time) {

  FlappyCatEntity::update(time);
  mUpdateModifier(*this, time);
}

void FlappyCatHero::drawOn(const Window& window) const {

  Position::value_type diameter = mBall.geometry().radius() * 2.f;

  Position mascotPos = mBall.transformation().position()
                     + Position(diameter * 0.3f, diameter * 0.3f);

  FlappyCatMascot mascot(gameConstants());

  mascot.setColor(Color(0, 0, 0), Color(255, 255, 255), Color(64, 0, 0));
  mascot.moveTo(mascotPos);
  mascot.resize(Position(diameter, diameter));

  window.draw(mBall);
  mascot.drawOn(window);

}

const Position& FlappyCatHero::position() const {

  return mBall.transformation().position();
}

void FlappyCatHero::reset() {

  FlappyCatEntity::reset();
  mResetModifier(*this);
}

void FlappyCatHero::setResetModifier(const modifier_type& modifier) {

  mResetModifier = modifier;
}

void FlappyCatHero::setColor(const Color& color) {

  mBall.setColor(color);
}

void FlappyCatHero::setUpdateModifier(const update_modifier_type& modifier) {

  mUpdateModifier = modifier;
}
