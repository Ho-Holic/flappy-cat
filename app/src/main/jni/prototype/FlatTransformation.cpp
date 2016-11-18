
// self
#include "FlatTransformation.h"

FlatTransformation::FlatTransformation(const Position& position)
: Transformation()
, mPosition(position) {
  //
}

void FlatTransformation::setPosition(const Position& position) {

  mPosition = position;
}

const Position& FlatTransformation::getPosition() const {

  return mPosition;
}





