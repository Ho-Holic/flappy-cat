// game
#include "FlappyCatWall.h"

// engine
#include <physics/Collide.h>
#include <core/Log.h>

// style
#include <style/Guidelines.h>

FlappyCatWall::FlappyCatWall(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mGapInterval(0.f)
, mGapDisplacement(0.f)
, mTopBlock()
, mBottomBlock()
, mWallState(WallState::Normal) {
  //
}

void FlappyCatWall::setGapInterval(f32 interval) {

  mGapInterval = interval;
  syncChildren();
}

void FlappyCatWall::setGapDisplacement(f32 displacement) {

  mGapDisplacement = displacement;
  syncChildren();
}

bool FlappyCatWall::collideWithCircle(const Position& center, f32 radius) {

  return Collide::circleRect(center, radius, mTopBlock)
      || Collide::circleRect(center, radius, mBottomBlock);
}

void FlappyCatWall::drawOn(const Window& window) const {

  window.draw(mTopBlock);
  window.draw(mBottomBlock);
}

void FlappyCatWall::setColor(const Color& color) {

  mTopBlock.setColor(color);
  mBottomBlock.setColor(color);
}


const Color& FlappyCatWall::color() const {
  return mTopBlock.color();
}

void FlappyCatWall::syncChildren() {

  f32 A1 = position().y();

  f32 A2 = A1 + size().y()
                            - mGapInterval / 2.f
                            - size().y() / 2.f
                            - mGapDisplacement;

  f32 A3 = A2 + mGapInterval;

  f32 A4 = A3 + size().y() / 2.f
                            + mGapDisplacement
                            - mGapInterval / 2.f;

  // Need to deal with situation when all values are 0.f to make assert work
  //REQUIRE(TAG, ((A1 < A2) && (A2 < A3) && (A3 < A4)), "Vectors must not overlap");

  mBottomBlock.transformation().setPosition(Position(position().x(), A1));
  mBottomBlock.geometry().resize(Position(size().x(), (A2 - A1)));

  mTopBlock.transformation().setPosition(Position(position().x(), A3));
  mTopBlock.geometry().resize(Position(size().x(), (A4 - A3)));

}

void FlappyCatWall::activateWall() {

  mWallState = WallState::Activated;
}

