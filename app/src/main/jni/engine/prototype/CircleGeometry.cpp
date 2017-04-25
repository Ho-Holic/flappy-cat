
// engine
#include "CircleGeometry.h"

// stl
#include <cmath>

CircleGeometry::CircleGeometry(Position::value_type radius, std::size_t resolution)
: Geometry()
, mRadius(radius)
, mResolution(resolution)
, mOnUpdate() {
  //
}

Geometry::size_type CircleGeometry::points() const {

  return mResolution;
}

Position CircleGeometry::pointAt(size_type index) const {

  constexpr Position::value_type pi = 3.141592654f;

  Position::value_type angle = index * 2.f * pi / mResolution - pi / 2.f;
  Position::value_type x = std::cos(angle) * mRadius;
  Position::value_type y = std::sin(angle) * mRadius;

  return Position(mRadius + x, mRadius + y);
}

CircleGeometry::OnUpdateSignal& CircleGeometry::onUpdate() {

  return mOnUpdate;
}

void CircleGeometry::setResolution(std::size_t resolution) {

  mResolution = resolution;
  mOnUpdate.emit();
}

void CircleGeometry::setRadius(Position::value_type radius) {

  mRadius = radius;
  mOnUpdate.emit();
}

Position::value_type CircleGeometry::radius() const {

  return mRadius;
}















