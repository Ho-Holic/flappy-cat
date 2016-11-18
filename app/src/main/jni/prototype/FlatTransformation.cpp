
// self
#include "FlatTransformation.h"

FlatTransformation::FlatTransformation(const Position& position)
: Transformation()
, mPosition(position) {
  //
}

FlatTransformation::FlatTransformation()
: FlatTransformation(Position(0.f, 0.f)) {
  //
}

void FlatTransformation::setPosition(const Position& position) {

  mPosition = position;
}

const Position& FlatTransformation::getPosition() const {

  return mPosition;
}









