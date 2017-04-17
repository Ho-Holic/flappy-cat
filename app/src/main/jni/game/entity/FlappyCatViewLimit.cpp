
// game
#include "FlappyCatViewLimit.h"

FlappyCatViewLimit::FlappyCatViewLimit(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mTop()
, mTopRight()
, mRight()
, mBottomRight()
, mBottom()
, mBottomLeft()
, mLeft()
, mTopLeft() {
  //
}

void FlappyCatViewLimit::syncChildren() {

  const Position& position = this->position();
  const Position& size     = this->size();

  // move
  mTop        .transformation().setPosition(position + Position(0.f      , size.y()));
  mTopRight   .transformation().setPosition(position + Position(size.x() , size.y()));
  mRight      .transformation().setPosition(position + Position(size.x() , 0.f));
  mBottomRight.transformation().setPosition(position + Position(size.x() , -size.y()));
  mBottom     .transformation().setPosition(position + Position(0.f      , -size.y()));
  mBottomLeft .transformation().setPosition(position + Position(-size.x(), -size.y()));
  mLeft       .transformation().setPosition(position + Position(-size.x(), 0.f));
  mTopLeft    .transformation().setPosition(position + Position(-size.x(), size.y()));

  // resize
  mTop        .geometry().resize(size);
  mTopRight   .geometry().resize(size);
  mRight      .geometry().resize(size);
  mBottomRight.geometry().resize(size);
  mBottom     .geometry().resize(size);
  mBottomLeft .geometry().resize(size);
  mLeft       .geometry().resize(size);
  mTopLeft    .geometry().resize(size);
}

void FlappyCatViewLimit::drawOn(const Window& window) const {

  window.draw(mTop);
  window.draw(mTopRight);
  window.draw(mRight);
  window.draw(mBottomRight);
  window.draw(mBottom);
  window.draw(mBottomLeft);
  window.draw(mLeft);
  window.draw(mTopLeft);
}