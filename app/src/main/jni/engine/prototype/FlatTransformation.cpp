// engine
#include "FlatTransformation.h"

FlatTransformation::FlatTransformation(const Position& position)
: Transformation()
, mPosition(position)
, mOrigin(0.f, 0.f)
, mScale(1.f, 1.f)
, mAngle(0.f)
, mOnUpdate() {
  //
}

FlatTransformation::FlatTransformation()
: FlatTransformation(Position(0.f, 0.f)) {
  //
}

FlatTransformation::OnUpdateSignal& FlatTransformation::onUpdate() {
  return mOnUpdate;
}

void FlatTransformation::setPosition(const Position& position) {

  mPosition = position;
  mOnUpdate.emit();
}

const Position& FlatTransformation::position() const {

  return mPosition;
}

void FlatTransformation::setOrigin(const Position& origin) {
  mOrigin = origin;
}

const Position& FlatTransformation::origin() const {
  return mOrigin;
}

void FlatTransformation::setScale(const Position& factor) {
  mScale = factor;
}

const Position& FlatTransformation::scale() const {
  return mScale;
}

void FlatTransformation::setRotation(Position::value_type angle) {

  mAngle = angle;
}

Position::value_type FlatTransformation::rotation() const {

  return mAngle;
}