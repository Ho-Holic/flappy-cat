
// self
#include "FlatTransform.h"

FlatTransform::FlatTransform(const Position& position)
: Transform()
, mPosition(position) {
  //
}

void FlatTransform::setPosition(const Position& position) {

  mPosition = position;
}

const Position& FlatTransform::getPosition() const {

  return mPosition;
}





