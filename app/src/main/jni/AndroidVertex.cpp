// self
#include "AndroidVertex.h"

AndroidVertex::AndroidVertex(const Position& position,
                             const AndroidColor& color)
: mPosition(position)
, mColor(color) {
  //
}

const Position& AndroidVertex::position() const {

  return mPosition;
}

const AndroidColor& AndroidVertex::color() const {

  return mColor;
}








