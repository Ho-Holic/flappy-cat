// self
#include "FlappyCatWall.h"
#include <physics/Collide.h>
#include "style/Guidelines.h"

// engine
#include <core/Log.h>

FlappyCatWall::FlappyCatWall(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mPosition()
, mSize()
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

bool FlappyCatWall::collideWithCircle(const Position& center, float radius) {
  return Collide::circleRect(center, radius, mTopBlock)
         || Collide::circleRect(center, radius, mBottomBlock);
}

void FlappyCatWall::moveTo(const Position& position) {

  mPosition = position;
  syncChildren();
}

const Position& FlappyCatWall::position() const {

  return mPosition;
}

void FlappyCatWall::drawOn(const Window& window) const {

  window.draw(mTopBlock);
  window.draw(mBottomBlock);
}

void FlappyCatWall::setColor(const Color& color) {

  mTopBlock.setColor(color);
  mBottomBlock.setColor(color);
}

void FlappyCatWall::resize(const Position& size) {

  mSize = size;
  syncChildren();
}

void FlappyCatWall::syncChildren() {

  Position::value_type A1 = mPosition.y();

  Position::value_type A2 = A1 + mSize.y()
                            - mGapInterval / 2.f
                            - mSize.y() / 2.f
                            - mGapDisplacement;

  Position::value_type A3 = A2 + mGapInterval;

  Position::value_type A4 = A3 + mSize.y() / 2.f
                            + mGapDisplacement
                            - mGapInterval / 2.f;

  // Need to deal with situation when all values are 0.f to make assert work
  //REQUIRE(TAG, ((A1 < A2) && (A2 < A3) && (A3 < A4)), "Vectors must not overlap");

  mBottomBlock.transformation().setPosition(Position(mPosition.x(), A1));
  mBottomBlock.geometry().resize(Position(mSize.x(), (A2 - A1)));

  mTopBlock.transformation().setPosition(Position(mPosition.x(), A3));
  mTopBlock.geometry().resize(Position(mSize.x(), (A4 - A3)));

//  Log::i(TAG, "top   : pos(%f,%f), size(%f, %f)",
//         mTopBlock.transformation().position().x(),
//         mTopBlock.transformation().position().y(),
//         mTopBlock.geometry().size().x(),
//         mTopBlock.geometry().size().y());
//  Log::i(TAG, "bottom: pos(%f,%f), size(%f, %f)",
//         mBottomBlock.transformation().position().x(),
//         mBottomBlock.transformation().position().y(),
//         mBottomBlock.geometry().size().x(),
//         mBottomBlock.geometry().size().y());
//  Log::i(TAG, "gap: %f, shift: %f", mGapInterval, mGapDisplacement);
//  Log::i(TAG, "------------------------------------");
}



























