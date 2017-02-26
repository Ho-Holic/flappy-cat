// self
#include <physics/Collide.h>
#include "FlappyCatWall.h"

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
}

bool FlappyCatWall::collideWithCircle(const Position& center, float radius) {
  return Collide::circleRect(center, radius, mTopBlock)
         || Collide::circleRect(center, radius, mBottomBlock);
}

void FlappyCatWall::moveTo(const Position& position) {

  mPosition = position;

  mTopBlock   .transformation().setPosition(mPosition + Position(0.f, mGapInterval / 2.f));
  mBottomBlock.transformation().setPosition(mPosition
                                          - Position(0.f, mGapInterval / 2.f)
                                          - Position(0.f, mBottomBlock.geometry().size().y()));
}

const Position& FlappyCatWall::position() const {

  return mPosition;
}

void FlappyCatWall::update(const FrameDuration& time) {

  moveBy(Position(-5.f, 0.f));

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

  mTopBlock   .geometry().resize(Position(mSize.x(), bothBlocksHeight - oneBlockHeight));
  mBottomBlock.geometry().resize(Position(mSize.x(), oneBlockHeight));
}



























