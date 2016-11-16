// self
#include "RectangleGeometry.h"
#include <style/Guidelines.h>

RectangleGeometry::RectangleGeometry(const Position& size)
: Geometry()
, mSize(size)
, mOnUpdate() {
  //
}

Geometry::size_type RectangleGeometry::points() const {
  return 4;
}

Position RectangleGeometry::pointAt(size_type index) const {

  switch (index) {
    case  0: return Position(0.f, 0.f);             break;
    case  1: return Position(mSize.x(), 0.f);       break;
    case  2: return Position(mSize.x(), mSize.y()); break;
    case  3: return Position(0.f, mSize.y());       break;
    default: return Position(0.f, 0.f);
  }

  return Position(0.f, 0.f);
}

RectangleGeometry::OnUpdateSignal& RectangleGeometry::onUpdate() {
  return mOnUpdate;
}

void RectangleGeometry::resize(const Position& size) {
  mSize = size;
  mOnUpdate.emit();
}

const Position& RectangleGeometry::size() const {
  return mSize;
}











