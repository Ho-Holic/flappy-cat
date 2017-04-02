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

Position::value_type Position::x() const {

  return mX;
}

Position::value_type Position::y() const {

  return mY;
}







