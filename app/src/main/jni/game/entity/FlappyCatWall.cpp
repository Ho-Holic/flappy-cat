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
, mBottomBlock() {
  //
}

void FlappyCatWall::setGapInterval(Position::value_type interval) {

  mGapInterval = interval;
  syncChildren();
}

void FlappyCatWall::setGapDisplacement(Position::value_type displacement) {

  mGapDisplacement = displacement;
  syncChildren();
}

bool FlappyCatWall::collideWithCircle(const Position& center, Position::value_type radius) {

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

void FlappyCatWall::syncChildren() {

  Position::value_type A1 = position().y();

  Position::value_type A2 = A1 + size().y()
                            - mGapInterval / 2.f
                            - size().y() / 2.f
                            - mGapDisplacement;

  Position::value_type A3 = A2 + mGapInterval;

  Position::value_type A4 = A3 + size().y() / 2.f
                            + mGapDisplacement
                            - mGapInterval / 2.f;

  // Need to deal with situation when all values are 0.f to make assert work
  //REQUIRE(TAG, ((A1 < A2) && (A2 < A3) && (A3 < A4)), "Vectors must not overlap");

  mBottomBlock.transformation().setPosition(Position(position().x(), A1));
  mBottomBlock.geometry().resize(Position(size().x(), (A2 - A1)));

  mTopBlock.transformation().setPosition(Position(position().x(), A3));
  mTopBlock.geometry().resize(Position(size().x(), (A4 - A3)));

}
