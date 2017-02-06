// self
#include <physics/Collide.h>
#include "FlappyCatWall.h"

FlappyCatWall::FlappyCatWall(const Position& position, const Position& size)
: mTopBlock(position, size)
, mBottomBlock(position + 120.f, size)
, mGapInterval(0.f)
, mGapDisplacement(0.f) {
  //
}

void FlappyCatWall::setGapInterval(Position::position_type interval) {

  mGapInterval = interval;
}

void FlappyCatWall::setGapDisplacement(Position::position_type displacement) {

  mGapDisplacement = displacement;
}

bool FlappyCatWall::collideWithCircle(const Position& center, float radius) {
  return Collide::circleRect(center, radius, mTopBlock)
         || Collide::circleRect(center, radius, mBottomBlock);
}

void FlappyCatWall::moveTo(const Position& position) {

  mTopBlock.transformation().setPosition(position);
  mBottomBlock.transformation().setPosition(position + 120.f);
}

void FlappyCatWall::setColor(const Color& color) {

  mTopBlock.setColor(color);
  mBottomBlock.setColor(color);
}

const Position& FlappyCatWall::position() const {

  return mTopBlock.transformation().position();
}

void FlappyCatWall::update(const FrameDuration& time) {

  mTopBlock.transformation().setPosition(mTopBlock.transformation().position()
                                       + Position(-10.f, 0.f));

  mBottomBlock.transformation().setPosition(mBottomBlock.transformation().position()
                                          + Position(-10.f, 0.f));

}

void FlappyCatWall::drawOn(const Window& window) const {

  window.draw(mTopBlock);
  window.draw(mBottomBlock);
}





















