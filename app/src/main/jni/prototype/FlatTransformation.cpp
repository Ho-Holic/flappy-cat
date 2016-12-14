
// self
#include "FlatTransformation.h"

FlatTransformation::FlatTransformation(const Position& position)
: Transformation()
, mPosition(position)
, mOrigin(0.f, 0.f)
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

void FlatTransformation::move(const Position& position) {

  mPosition = mPosition + position;
  mOnUpdate.emit();
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



















