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
, mBall()
, mMascot(gameConstants)
, mResetModifier([](entity_type&){})
, mUpdateModifier([](entity_type&, const FrameDuration&){})
, mIsAlive(true) {
  //
}

f32 FlappyCatHero::radius() const {

  return mBall.geometry().radius();
}

void FlappyCatHero::setRadius(f32 radius) {

  mBall.geometry().setRadius(radius);
  syncChildren();
}

void FlappyCatHero::update(const FrameDuration& time) {

  FlappyCatEntity::update(time);
  mUpdateModifier(*this, time);
}

void FlappyCatHero::drawOn(const Window& window) const {

  window.draw(mBall);
  mMascot.drawOn(window);

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

void FlappyCatHero::kill() {
  mIsAlive = false;
}

void FlappyCatHero::syncChildren() {

/**
   * TODO: add rotation to mBall
   * Currently origin of ball is not in the center of the ball
   * so rotation would cause bad render, fix origin code
   * and uncomment rotation line
   */
  //mBall.transformation().setRotation(mAngle);

  mBall.transformation().setPosition(position());

  f32 diameter = mBall.geometry().radius() * 2.f;

  Position mascotPos = mBall.transformation().position()
                       + Position(diameter * 0.25f, diameter * 0.3f);

  mMascot.moveTo(mascotPos);
  mMascot.resize(Position(diameter, diameter));
  mMascot.rotateTo(rotation());

}