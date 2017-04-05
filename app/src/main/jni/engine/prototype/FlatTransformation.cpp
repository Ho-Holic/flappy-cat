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

const Position& FlatTransformation::position() const {

  return mPosition;
}

const Position& FlatTransformation::origin() const {

  return mOrigin;
}

const Position& FlatTransformation::scale() const {

  return mScale;
}

Position::value_type FlatTransformation::rotation() const {

  return mAngle;
}

void FlatTransformation::setPosition(const Position& position) {

  mPosition = position;
  mOnUpdate.emit();
}



void FlatTransformation::setOrigin(const Position& origin) {

  mOrigin = origin;
  mOnUpdate.emit();
}


void FlatTransformation::setScale(const Position& factor) {

  mScale = factor;
  mOnUpdate.emit();
}


void FlatTransformation::setRotation(Position::value_type angle) {

  mAngle = angle;
  mOnUpdate.emit();
}
