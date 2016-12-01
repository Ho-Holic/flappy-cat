// self
#include "View.h"

View::View()
: Transformation()
, mOrigin(0.f, 0.f)
, mSize(0.f, 0.f) {
  //
}

void View::setOrigin(const Position& origin) {
  mOrigin = origin;
}

const Position& View::origin() const {
  return mOrigin;
}

void View::setPosition(const Position& position) {
  mSize = position;
}

const Position& View::getPosition() const {
  return mSize;
}
