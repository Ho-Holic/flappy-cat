// self
#include "AndroidVertex.h"

AndroidVertex::AndroidVertex(const AndroidPosition& position,
                             const AndroidColor& color)
: mPosition(position)
, mColor(color) {
  //
}

const AndroidPosition& AndroidVertex::position() const {

  return mPosition;
}

const AndroidColor& AndroidVertex::color() const {

  return mColor;
}








