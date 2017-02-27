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
  syncChildrenSize();
}

void FlappyCatWall::setGapDisplacement(Position::value_type displacement) {

  mGapDisplacement = displacement;
  syncChildrenSize();
}

bool FlappyCatWall::collideWithCircle(const Position& center, float radius) {
  return Collide::circleRect(center, radius, mTopBlock)
         || Collide::circleRect(center, radius, mBottomBlock);
}

void FlappyCatWall::moveTo(const Position& position) {

  mPosition = position;

  Position::value_type topPosition    = mGapDisplacement + (mGapInterval / 2.f);
  Position::value_type bottomPosition = - mBottomBlock.geometry().size().y()
                                       + mGapDisplacement
                                       - (mGapInterval / 2.f);

  mTopBlock   .transformation().setPosition(mPosition + Position(0.f, topPosition));
  mBottomBlock.transformation().setPosition(mPosition + Position(0.f, bottomPosition));
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

  syncChildrenSize();
}

void FlappyCatWall::syncChildrenSize() {

  Position::value_type bothBlocksHeight = mSize.y() - mGapInterval;

  Position::value_type oneBlockHeight = bothBlocksHeight / 2.f;

  Log::i(TAG, "gap %f", mGapDisplacement);

  REQUIRE(TAG, oneBlockHeight > mGapDisplacement, "Block size must be greater then gap displace");

  Position::value_type topHeight    = bothBlocksHeight - oneBlockHeight - mGapDisplacement;
  Position::value_type bottomHeight = oneBlockHeight + mGapDisplacement;

  mTopBlock   .geometry().resize(Position(mSize.x(), topHeight));
  mBottomBlock.geometry().resize(Position(mSize.x(), bottomHeight));
}



























