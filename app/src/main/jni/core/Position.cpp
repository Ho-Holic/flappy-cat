// self
#include "Position.h"

Position::Position(position_type x, position_type y)
: mX(x)
, mY(y) {
  //
}

Position::Position()
: Position(0.f, 0.f) {
  //
}

Position::position_type Position::x() const {

  return mX;
}

Position::position_type Position::y() const {

  return mY;
}







