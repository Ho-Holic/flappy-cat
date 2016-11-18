
// self
#include "FlatTransformation.h"

FlatTransformation::FlatTransformation(const Position& position)
: Transformation()
, mPosition(position)
, mOnUpdate() {
  //
}

FlatTransformation::FlatTransformation()
: FlatTransformation(Position(0.f, 0.f)) {
  //
}

void FlatTransformation::setPosition(const Position& position) {

  mPosition = position;
  mOnUpdate.emit();
}

const Position& FlatTransformation::getPosition() const {

  return mPosition;
}

FlatTransformation::OnUpdateSignal& FlatTransformation::onUpdate() {
  return mOnUpdate;
}











