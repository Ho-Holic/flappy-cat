// engine
#include <prototype/RectangleShape.h>
#include <prototype/TriangleShape.h>
#include <core/Log.h>

// game
#include "FlappyCatHero.h"

FlappyCatHero::FlappyCatHero(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mJumpAcceleration()
, mJumpVelocity()
, mAngle(0.f)
, mBall()
, mMascot(gameConstants)
, mResetModifier([](entity_type&){})
, mUpdateModifier([](entity_type&, const FrameDuration&){}) {
  //
}

Position::value_type FlappyCatHero::radius() const {

  return mBall.geometry().radius();
}

void FlappyCatHero::setRadius(Position::value_type radius) {

  mBall.geometry().setRadius(radius);
  syncFigure();
}

void FlappyCatHero::moveTo(const Position& position) {

  mBall.transformation().setPosition(position);
  syncFigure();
}

void FlappyCatHero::rotate(Position::value_type angle) {

  mAngle = angle;

/**
   * TODO: add rotation to mBall
   * Currently origin of ball is not in the center of the ball
   * so rotation would cause bad render, fix origin code
   * and uncomment rotation line
   */
  //mBall.transformation().setRotation(mAngle);

  syncFigure();
}

void FlappyCatHero::update(const FrameDuration& time) {

  FlappyCatEntity::update(time);
  mUpdateModifier(*this, time);
}

void FlappyCatHero::drawOn(const Window& window) const {

  window.draw(mBall);
  mMascot.drawOn(window);

}

const Position& FlappyCatHero::position() const {

  return mBall.transformation().position();
}

Position::value_type FlappyCatHero::rotation() const {

  return mAngle;
}

void FlappyCatHero::reset() {

  FlappyCatEntity::reset();
  mResetModifier(*this);
}

void FlappyCatHero::setResetModifier(const modifier_type& modifier) {

  mResetModifier = modifier;
}

void FlappyCatHero::setColor(const Color& backgroundColor,
                             const Color& bodyColor,
                             const Color& scarfColor,
                             const Color& mouthColor) {

  mBall.setColor(backgroundColor);
  mMascot.setColor(bodyColor, scarfColor, mouthColor);
}

void FlappyCatHero::setUpdateModifier(const update_modifier_type& modifier) {

  mUpdateModifier = modifier;
}

void FlappyCatHero::setJumpConstants(const Position& acceleration, const Position& velocity) {

  mJumpAcceleration = acceleration;
  mJumpVelocity = velocity;
}

void FlappyCatHero::jump() {

  setAcceleration(mJumpAcceleration);
  setVelocity(mJumpVelocity);
}

void FlappyCatHero::syncFigure() {

  Position::value_type diameter = mBall.geometry().radius() * 2.f;

  Position mascotPos = mBall.transformation().position()
                       + Position(diameter * 0.3f, diameter * 0.3f);

  mMascot.moveTo(mascotPos);
  mMascot.resize(Position(diameter, diameter));
  mMascot.rotate(mAngle);
}