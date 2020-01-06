// engine
#include "Position.h"

Position::Position(value_type x, value_type y)
: mX(x)
, mY(y) {
  //
}

Position::Position()
: Position(0.f, 0.f) {
  //
}

f32 Position::x() const {

  return mX;
}

f32 Position::y() const {

  return mY;
}







