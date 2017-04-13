
// game
#include "FlappyCatViewLimit.h"

FlappyCatViewLimit::FlappyCatViewLimit(const FlappyCatGameConstants& gameConstants)
: FlappyCatEntity(gameConstants)
, mPosition()
, mSize()
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

void FlappyCatViewLimit::moveTo(const Position& position) {

  mPosition = position;
  syncChildren();
}

void FlappyCatViewLimit::resize(const Position& size) {

  mSize = size;
  syncChildren();
}

const Position& FlappyCatViewLimit::position() const {

  return mPosition;
}

void FlappyCatViewLimit::syncChildren() {

  // move
  mTop        .transformation().setPosition(mPosition + Position(0.f       , mSize.y()));
  mTopRight   .transformation().setPosition(mPosition + Position(mSize.x() , mSize.y()));
  mRight      .transformation().setPosition(mPosition + Position(mSize.x() , 0.f));
  mBottomRight.transformation().setPosition(mPosition + Position(mSize.x() , -mSize.y()));
  mBottom     .transformation().setPosition(mPosition + Position(0.f       , -mSize.y()));
  mBottomLeft .transformation().setPosition(mPosition + Position(-mSize.x(), -mSize.y()));
  mLeft       .transformation().setPosition(mPosition + Position(-mSize.x(), 0.f));
  mTopLeft    .transformation().setPosition(mPosition + Position(-mSize.x(), mSize.y()));

  // resize
  mTop        .geometry().resize(mSize);
  mTopRight   .geometry().resize(mSize);
  mRight      .geometry().resize(mSize);
  mBottomRight.geometry().resize(mSize);
  mBottom     .geometry().resize(mSize);
  mBottomLeft .geometry().resize(mSize);
  mLeft       .geometry().resize(mSize);
  mTopLeft    .geometry().resize(mSize);
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