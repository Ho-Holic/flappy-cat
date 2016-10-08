// self
#include "AndroidPosition.h"

AndroidPosition::AndroidPosition(position_type x, position_type y)
: mX(x)
, mY(y) {
  //
}

AndroidPosition::position_type AndroidPosition::x() const {

  return mX;
}

AndroidPosition::position_type AndroidPosition::y() const {

  return mY;
}





